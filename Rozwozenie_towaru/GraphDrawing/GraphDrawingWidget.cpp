#include "GraphDrawingWidget.h"

#include <QPainter>
#include <QtDebug>
#include <algorithm>
#include <cmath>

GraphDrawingWidget::GraphDrawingWidget(CPPGraph &graph, QWidget *parent) : QWidget(parent), graph(graph)
{
    artificialVertexPen = QPen(Qt::red, pointSize, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    vertexPen = QPen(Qt::black, pointSize, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    vertexLabelPen = QPen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    edgePen = QPen(Qt::black, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    artificialVertexBrush = Qt::red;
    vertexBrush = Qt::black;

    margin = QPoint(pointSize/2, pointSize/2);
}

void GraphDrawingWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen(Qt::black, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setBrush(Qt::black);
    painter.setPen(pen);

    //drawCompleteGraph(painter, 20);
    drawGraph(painter);
    drawDisplayArguments(painter);
}

void GraphDrawingWidget::drawGraph(QPainter &painter)
{

    //center the graph
    CPPVertex lt = graph.leftTop();
    p0 = QPoint(-lt.x(), -lt.y());
    painter.translate(p0 + margin);

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
        CPPVertex& v = graph.vertex(i);
        if(v.artificialFlag()){
            printArtificialVertex(painter, v, i);
        }else{
            printVertex(painter, v, i);
        }
    }

}

void GraphDrawingWidget::printVertex(QPainter& painter, const CPPVertex& v, unsigned int index){

    QString text = QString::number(index);
    painter.setBrush(vertexBrush);
    painter.setPen(vertexPen);
    painter.drawPoint(QPoint(v.x(), v.y()));
    painter.setPen(vertexLabelPen);
    //default font is 10px. centering is done by moving signs down and left
    painter.drawText( v.x() -5, v.y() +5, text);

}

void GraphDrawingWidget::printArtificialVertex(QPainter& painter, const CPPVertex &v, unsigned int index){
    QString text = QString::number(index);

    painter.setBrush(artificialVertexBrush);
    painter.setPen(artificialVertexPen);
    painter.drawPoint(QPoint(v.x(), v.y()));
    painter.setPen(vertexLabelPen);
    painter.drawText( v.x() -5, v.y() +5, text);
}

void GraphDrawingWidget::setDisplayArguments(const DisplayArgument& ds)
{
    displayArgument = ds;
}

void GraphDrawingWidget::printEdge(QPainter& painter, const CPPVertex &v1, const CPPVertex &v2, int value){
    painter.drawLine(v1.x(), v1.y(), v2.x(), v2.y());

    QPointF directionVector = QPointF(1.0*v2.x()-v1.x(), 1.0*v2.y()-v1.y());
    //float lenght = sqrt(pow(directionVector.x(), 2) + pow(directionVector.y(), 2));

    painter.drawText(abs(v1.x() + directionVector.x()/2.0) - 5 ,abs(v1.y() + directionVector.y()/2.0) - 5, QString::number(value));
}

void GraphDrawingWidget::printShiftedEdge(QPainter &painter, const CPPVertex &v1, const CPPVertex &v2, int xShift, int yShift)
{
    painter.drawLine(v1.x()+xShift, v1.y()+yShift, v2.x()+xShift, v2.y()+yShift);
}

void GraphDrawingWidget::drawCompleteGraph(QPainter& painter, unsigned int vertices)
{

    unsigned int ox = this->width()/2.0;
    unsigned int oy = this->height()/2.0;
    unsigned int r = std::min(ox, oy) - 5;
    float pointR = 5; //2.0*M_PI*r / vertices;

    float angle = 2*M_PI/vertices;

    for(unsigned int i=0;i<vertices;++i){
        QPointF p1 = QPointF(sin(i*angle)*r + ox, -cos(i*angle)*r + oy);
        painter.drawEllipse(p1,pointR,pointR);

        for(unsigned int j=0;j<vertices;++j){
            if(j!=i){
                QPointF p2 = QPointF(sin(j*angle)*r + ox, -cos(j*angle)*r + oy);
                painter.drawLine(p1,p2);
            }
        }
    }
}

void GraphDrawingWidget::drawDisplayArguments(QPainter &painter)
{

    //std::cout<<"void GraphDrawingWidget::drawDisplayArguments(QPainter &painter)"<<std::endl;


    QPen pathPen = edgePen;
    pathPen.setWidth(pathPen.width()*4);


    for(unsigned int i=0;i<displayArgument.paths.size();++i){
        if(displayArgument.paths.at(i).size() > 1){

            pathPen.setColor(colors.at(i%colors.size()));
            painter.setPen(pathPen);

            for(unsigned int j=0;j<displayArgument.paths.at(i).size()-1;++j){
                printShiftedEdge(painter, graph.vertex(displayArgument.paths.at(i).at(j)), graph.vertex(displayArgument.paths.at(i).at(j+1)), 0,pathPen.width()*i);
            }
        }
    }
}

