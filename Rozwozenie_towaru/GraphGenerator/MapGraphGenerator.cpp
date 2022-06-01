#include "MapGraphGenerator.h"

#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

#include <QMenu>
#include <QModelIndex>
#include <QtDebug>
#include <stdlib.h>
#include <cmath>

MapGraphGenerator::MapGraphGenerator(CPPGraph& graph, QWidget *parent) :
    QWidget(parent), graph(graph)
{
    disableBackground();

    if(graph.name() != ""){
        loadImage(QString::fromStdString(graph.name()));
    }
}

void MapGraphGenerator::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    //painter.begin(this);
    if(bgLoaded && enableBg)
        painter.drawImage(anchor, bg);

    painter.setBrush(Qt::black);
    painter.setPen(edgePen);
    for(unsigned int i=0;i<graph.size();++i){
        for(unsigned int j=0;j<graph.size();++j){

            if(i!=j ){
                int value = graph.edge(i,j).directValue();
                if(value > 0){
                    printEdge(painter, graph.vertex(i), graph.vertex(j), value);
                }
            }
        }
    }

    painter.setPen(vertexPen);
    for(unsigned int i=0;i<graph.size();++i){
        printVertex(painter, graph.vertex(i), i);
    }


    painter.end();
}

void MapGraphGenerator::printVertex(QPainter& painter, const CPPVertex& v, unsigned int index){

    painter.setPen(vertexPen);
    painter.drawPoint(QPoint(v.x(), v.y()) + anchor);

    painter.setPen(vertexLabelPen);
    QString text = QString::number(index+1);

    //default font is 10px. centering is done by moving signs down and left
    painter.drawText( v.x() -5 + anchor.x(), v.y() +5 + anchor.y(), text);
}

void MapGraphGenerator::printEdge(QPainter& painter, const CPPVertex& v1, const CPPVertex& v2, int value){
    painter.drawLine(v1.x() + anchor.x(), v1.y()+ anchor.y(), v2.x()+ anchor.x(), v2.y()+ anchor.y());

    QPointF directionVector = QPointF(1.0*v2.x()-v1.x(), 1.0*v2.y()-v1.y());
    float lenght = sqrt(pow(directionVector.x(), 2) + pow(directionVector.y(), 2));

    QPointF directionVectorOne = directionVector / lenght;

    painter.drawText(abs(v1.x() + directionVector.x()/2.0) - 5 + anchor.x(),abs(v1.y() + directionVector.y()/2.0) - 5 + anchor.y(), QString::number(value));
    int arrowSize = 10;
    painter.drawEllipse(v2.x()- pointSize * directionVectorOne.x() - arrowSize/2 + anchor.x(), v2.y() - pointSize * directionVectorOne.y() - arrowSize/2 + anchor.y(), arrowSize,arrowSize);
    if(graph.bidirectionalFlag() == true){
        painter.drawEllipse(v1.x() + pointSize * directionVectorOne.x() - arrowSize/2 + anchor.x(), v1.y() + pointSize * directionVectorOne.y() - arrowSize/2 + anchor.y(), arrowSize,arrowSize);
    }
}

void MapGraphGenerator::loadImage(QString fileName)
{
    if(fileName == ""){
        fileName = QFileDialog::getOpenFileName(this,"Open File",QString(),"PNG File(*.png)");
        graph.name() = fileName.toStdString();
    }

    bg = QImage(fileName);
    bgLoaded = true;

    vertexPen = QPen(Qt::white, pointSize, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    vertexLabelPen = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    edgePen = QPen(Qt::white, 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    this->updateAll();
}

void MapGraphGenerator::updateAll()
{
    this->notify();
    this->update();
}

bool &MapGraphGenerator::enableBackground() noexcept
{
    return enableBg;
}

bool MapGraphGenerator::enableBackground() const noexcept
{
    return enableBg;
}

void MapGraphGenerator::disableBackground()
{
    vertexPen = QPen(Qt::black, pointSize, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    vertexLabelPen = QPen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    edgePen = QPen(Qt::black, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    bgLoaded = false;
    repaint();
}


void MapGraphGenerator::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // handle left mouse button here
        QPoint mouse = event->pos();

        if(edgeAdding == true){
            int hover = hoverVertex(event->pos());
            if(hover != -1){
                if(contextVertex != hover || (contextVertex == hover && graph.selfRelationFlag())){
                    graph.edge(contextVertex, hover) = 1;
                }
            }
            contextVertex = -1;
            edgeAdding = false;
        }
        else{
            //check if mouse hover element
            int hover = hoverVertex(mouse);
            if(hover > -1){
                activeVertex = hover;
            }
        }

    } else if(event->button() == Qt::RightButton) {

        // pass on other buttons to base class
        mousePositionWhenClick = event->pos();
        onBGContextRequested(event->pos());

    } else if (event->button() == Qt::MiddleButton){
        //move anchor
        mousePositionWhenClick = event->pos();
        mouseMoveAnchor = true;
        anchorMouseMove = anchor;
    } else {
        QWidget::mousePressEvent(event);
    }
    this->updateAll();
}

void MapGraphGenerator::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton )
    {

        for(unsigned int i=0;i<graph.size();++i){
            for(unsigned int j=0;j<graph.size();++j){
                int value = graph.edge(i,j).directValue();
                if(i!=j && value > 0){
                    const CPPVertex v1 = graph.vertex(i);
                    const CPPVertex v2 = graph.vertex(j);
                    const float x1minusx2 = v2.x() - v1.x();
                    const float y1minus2 = v2.y() - v1.y();
                    const float A = y1minus2 / x1minusx2;
                    const float B = -1;
                    const float C = v2.y()-v2.x()*A;


                    float d = abs(A*(event->pos().x() - anchor.x()) + B*(event->pos().y() -anchor.y())+ C) / sqrt(A*A + B*B);
                    //qDebug() << A << B << C << d << ":" << event->pos();

                    if(d < 10 && hoverRect(event->pos(), QPoint(v1.x(), v1.y()),QPoint(v2.x(), v2.y()))){
                        bool ok;
                        int value = QInputDialog::getInt(this, tr("Enter edge value for edge"),tr("Edge ") +
                                                         QString::number(i+1) + tr(" -> ") + QString::number(j+1),graph.edge(i,j).directValue(),-9999,9999,1,&ok);
                        if(ok)
                            graph.edge(i,j).value() = value;

                        i = graph.size();
                        j = graph.size();
                        this->updateAll();
                        break;
                    }
                }
            }
        }
    }

    // You may have to call the parent's method for other cases
    QWidget::mouseDoubleClickEvent( event );
}


void MapGraphGenerator::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        //stop processing
        if(activeVertex >= 0){
            //graph.vertex(activeVertex).x() = event->pos().x();
            //graph.vertex(activeVertex).y() = event->pos().y();
            activeVertex = -1;
            //this->updateAll();
        }

    } else if(event->button() == Qt::RightButton) {

    } else if(event->button() == Qt::MiddleButton) {
        mouseMoveAnchor = false;
    } else {
        QWidget::mouseReleaseEvent(event);
    }
    this->updateAll();
}

void MapGraphGenerator::mouseMoveEvent(QMouseEvent *event)
{
    if(activeVertex >= 0){
        graph.vertex(activeVertex).x() = event->pos().x() - anchor.x();
        graph.vertex(activeVertex).y() = event->pos().y() - anchor.y();
        //activeVertex = -1;
    }else if(mouseMoveAnchor){
        anchor = event->pos() - mousePositionWhenClick + anchorMouseMove;
        //move anchor
    }

    QWidget::mouseMoveEvent(event);
    this->updateAll();
}

void MapGraphGenerator::customMenuRequested(QPoint pos){
    //QModelIndex index=table->indexAt(pos);

    QMenu *menu=new QMenu(this);
    menu->addAction(new QAction("Action 1", this));
    menu->addAction(new QAction("Action 2", this));
    menu->addAction(new QAction("Action 3", this));
    menu->exec(this->mapToGlobal(pos));//popup(this->viewport()->mapToGlobal(pos));
}

int MapGraphGenerator::hoverVertex(QPoint point)
{
    int ret = -1;
    for(unsigned int i=0;i<graph.size();++i){
        CPPVertex v = graph.vertex(i);
        if(point.x() - anchor.x() > v.x() - pointSize/2.0 && point.x() - anchor.x() < v.x() + pointSize/2.0 &&
                point.y() - anchor.y() > v.y() - pointSize/2.0 && point.y() - anchor.y() < v.y() + pointSize/2.0){
            ret = i;
            break;
        }
    }

    return ret;
}

int MapGraphGenerator::hoverRect(QPoint point, QPoint p1, QPoint p2)
{
    point -= anchor;
    QPoint lt(std::min(p1.x(), p2.x()), std::min(p1.y(), p2.y()));
    QPoint rb(std::max(p1.x(), p2.x()), std::max(p1.y(), p2.y()));

    if(point.x() > lt.x() - pointSize/2.0 && point.x() < rb.x() + pointSize/2.0 &&
            point.y()> lt.y() - pointSize/2.0 && point.y() < rb.y() + pointSize/2.0){
        return  true;
    }


    return false;
}

void MapGraphGenerator::onBGContextRequested(QPoint pos)
{
    QMenu *menu=new QMenu(this);

    int hover = hoverVertex(pos);
    if(hover == -1){
        menu->addAction(tr("Add vertex"), this, SLOT(onAddVertexClicked()));
    }else{
        contextVertex = hover;
        menu->addAction(tr("Remove vertex"), this, SLOT(onRemoveVertexClicked()));
        menu->addAction(tr("Add edge"), this, SLOT(onAddEdgeClicked()));
    }

    menu->exec(this->mapToGlobal(pos));
}

void MapGraphGenerator::onAddVertexClicked()
{
    graph.pushbackVertex(CPPVertex(graph.size(),
                                     mousePositionWhenClick.x() - anchor.x(),
                                     mousePositionWhenClick.y() - anchor.y()));
    this->updateAll();
}

void MapGraphGenerator::onRemoveVertexClicked()
{
    graph.removeVertex(contextVertex);
    contextVertex = -1;
    this->updateAll();
}

void MapGraphGenerator::onAddEdgeClicked()
{
    edgeAdding = true;
    this->updateAll();
}
