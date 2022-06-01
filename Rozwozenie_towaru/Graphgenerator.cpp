#include "Graphgenerator.h"
#include "ui_Graphgenerator.h"
#include <algorithm>

#include <Qt>


GraphGenerator::GraphGenerator(CPPGraph &graph, QWidget *parent) :
    QWidget(parent), graph(graph),
    ui(new Ui::GraphGenerator)
{
    ui->setupUi(this);
    graph.bidirectionalFlag() = true;
    this->ui->bidirectional->setChecked(graph.bidirectionalFlag());
    this->ui->selfRelation->setChecked(graph.selfRelationFlag());

    gen = new MapGraphGenerator(graph, this);
    //attach to get all notifications about graph changes
    gen->attach(this);
    this->ui->container->addWidget(gen);

    updateView();
}

GraphGenerator::~GraphGenerator()
{
    delete ui;
}

void GraphGenerator::updateView()
{
    //std::cout<<"void GraphGenerator::updateView()"<<std::endl;

    //reset view
    ui->table->setRowCount(0);
    ui->table->setColumnCount(0);

    //insert rows and cols
    unsigned int size = std::min(ui->table->rowCount(), ui->table->columnCount());
    while (size < graph.size()) {
        ui->table->insertRow(ui->table->rowCount());
        ui->table->insertColumn(ui->table->columnCount());
        size = std::min(ui->table->rowCount(), ui->table->columnCount());
    }

    for(unsigned int i=0;i<size;++i){
        if(!graph.selfRelationFlag()){

            QTableWidgetItem* itm = ui->table->item(i, i);
            if(itm == nullptr){
                ui->table->setItem(i, i, new QTableWidgetItem("0"));
                itm = ui->table->item(i, i);
            }
            itm->setFlags(itm->flags() & ~Qt::ItemIsEditable);

        }else{
            QTableWidgetItem* itm = ui->table->item(i, i);
            if(itm == nullptr){
                ui->table->setItem(i, i, new QTableWidgetItem(""));
                itm = ui->table->item(i, i);
            }
            itm->setFlags(itm->flags() | Qt::ItemIsEditable);
        }
    }

    //update edges
    for(unsigned int i=0;i<size;++i){
        for(unsigned int j=0;j<size;++j){
            if(i!=j){
                CPPEdge& e = graph.edge(i,j);
                QString str;

                if(e.isDirect()){
                    //std::cout<<"direct!"<<e<<std::endl;
                    //std::cout<<graph.edge(i,j)<<" ";
                    str = QString::number(graph.edge(i,j).value());
                }else{
                    //std::cout<<"not direct!"<<e<<std::endl;
                    std::stringstream ss;
                    ss<<graph.edge(i,j).value()<<" ";
                    ss<<graph.edgeRoute(i,j);
                    std::cout<<graph.edgeRoute(i,j)<<std::endl;
                    str = QString::fromStdString(ss.str());
                }

                if(ui->table->item(i,j) == nullptr){
                    ui->table->setItem(i, j, new QTableWidgetItem(str));
                }else{
                    ui->table->item(i,j)->setText(str);
                }
            }
        }
    }
    //std::cout<<std::endl;
}

void GraphGenerator::updateStatistics()
{
    //vertices
    ui->verticesLabel->setText(QString::number(graph.size()));
    ui->edgesLabel->setText(QString::number(graph.edgesCount()));
    ui->shortestEdgeLabel->setText(QString::number(graph.shortestEdge()));
    ui->longestEdgeLabel->setText(QString::number(graph.longestEdge()));
    ui->oddVerticesLabel->setText(QString::number(graph.listOddVertices().size()));
    ui->evenVerticesLabel->setText(QString::number(graph.listEvenVertices().size()));
}

void GraphGenerator::updatedObservable(EventTypes eventNb)
{
    //pre defined event - graph reload
    if(eventNb == Observer::EVENT_RELOAD){
        //push notification to the generator
        gen->repaint();
    }

    updateView();
    updateStatistics();
}

void GraphGenerator::on_addVertice_clicked()
{
    ui->table->insertRow(ui->table->rowCount());
    ui->table->insertColumn(ui->table->columnCount());
    graph.pushbackVertex(0);
    updateView();
    updateStatistics();
}

void GraphGenerator::on_table_cellChanged(int row, int column)
{
    //ui->table->item(row, column)->setText
    QString text = ui->table->item(row, column)->text();

    if(row == column){
        if(graph.selfRelationFlag()){
            graph.edge(row,column).fromString(text.toStdString());
        }
    }else if(graph.bidirectionalFlag()){
        if(ui->table->item(column, row) == nullptr){
            ui->table->setItem(column, row, new QTableWidgetItem(text));
        }else{
            ui->table->item(column, row)->setText(text);
        }
        //graph.edge(row,column).value() = text.toInt();
    }else{
        //graph.edge(row,column).value() = text.toInt();
    }



    updateStatistics();
}

void GraphGenerator::on_selfRelation_stateChanged(int arg1)
{
    graph.selfRelationFlag() = arg1;
    updateView();
}

void GraphGenerator::on_bidirectional_stateChanged(int arg1)
{
    graph.bidirectionalFlag() = arg1;
    updateView();
}

void GraphGenerator::on_switchEditMode_clicked()
{
    int index = this->ui->container->currentIndex();
    index ++;
    if(index >= this->ui->container->count()){
        index = 0;
    }
    this->ui->container->setCurrentIndex(index);
    updateView();

}

void GraphGenerator::on_loadBg_clicked()
{
    gen->loadImage();
}

void GraphGenerator::on_genCompleteGraph_clicked()
{
    graph = CPPGraph();
    graph.bidirectionalFlag() = true;
    graph.selfRelationFlag() = false;
    int vertices = this->ui->completeGraphVertices->value();

    unsigned int ox = 600/2.0;
    unsigned int oy = 600/2.0;
    unsigned int r = std::min(ox, oy);

    float angle = 2*M_PI/vertices;

    int edgecounter = 1;
    for(int i=0;i<vertices;++i){
        //create vertice
        CPPVertex vertex;
        vertex.x() = sin(i*angle)*r + ox;
        vertex.y() = -cos(i*angle)*r + oy;
        graph.pushbackVertex(vertex);

        //create connections with all existing vertices
        for(int j=0;j<i;++j){
            graph.edge(i, j) = edgecounter;
            edgecounter ++;
        }
    }

    updateView();
}

void GraphGenerator::on_disableBg_clicked()
{
    gen->disableBackground();
}
