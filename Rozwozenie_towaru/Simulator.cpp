#include "Simulator.h"
#include "ui_Simulator.h"

#include "Algorithms/GeneticAlgorithm.h"
#include "Algorithms/BruteforceAlgorithm.h"

Simulator::Simulator(CPPGraph &graph, QWidget *parent) :
    QWidget(parent), graph(graph),
    ui(new Ui::Simulation)
{
    ui->setupUi(this);
    this->ui->displayModeComboBox->setCurrentIndex(displayMode);
    this->ui->semiAnimationIntervalSpinBox->setValue(semiAnimatedInterval);





    displayedGraph = graph;
    graphDrawer = new GraphDrawingWidget(displayedGraph, this->ui->simulationView);
    ((QVBoxLayout*)this->ui->simulationView->layout())->addWidget(graphDrawer);

    //set default algorithm
    currnetAlgorithm = new TestAlgorithm(graph, displayArguments);
    clearView();
    updateGraphView();
    this->repaint();
}

Simulator::~Simulator()
{
    delete ui;
}

void Simulator::on_algorythmComboBox_activated(int index)
{
    //remove last algorithm
    if(currnetAlgorithm != nullptr){
        delete currnetAlgorithm;
        currnetAlgorithm = nullptr;
    }

    //init algoritm
    switch (this->ui->algorythmComboBox->currentIndex()) {
    case 0:
        currnetAlgorithm = new TestAlgorithm(graph, displayArguments);
        break;
    case 1:
        currnetAlgorithm = new GeneticAlgorithm(graph, displayArguments);
        break;
    case 2:
        currnetAlgorithm = new BruteforceAlgorithm(graph, displayArguments);
        break;
    case 3:
        currnetAlgorithm = new NearestNeighbor(graph, displayArguments);
        break;
    }
}


void Simulator::on_runAlgorithm_clicked()
{
    this->ui->statusLabel->setText("Running");
    this->ui->executionTimeLabel->setText("");
    this->repaint();

    //time of execution

    timer.start();

    semiAnimatedFrameCounted = 0;

    //run only when correctly inited
    if(currnetAlgorithm){
        currnetAlgorithm->timeFactor() = ui->timeFactor->value();
        currnetAlgorithm->startVertex() = ui->startVertex->value();
        currnetAlgorithm->truckNo() = ui->truckNo->value();

        std::vector<unsigned int> destinations;


        std::string s = ui->destinations->text().toStdString();

        std::cout<<"ss: '"<<s<<"' "<<(s == "*")<<std::endl;
        if(s != "*"){
            std::stringstream ss;
            ss<<s;
            unsigned int size = 0;
            ss>>size;
            for(unsigned int i=0;i<size;++i){
                unsigned int k;
                ss>>k;
                destinations.push_back(k);
            }

            std::cout<<"Starting for destinations: "<<destinations<<std::endl;

            if(destinations.size() == 0){
                std::cerr<<"No destinations entered!"<<destinations<<std::endl;
                this->ui->statusLabel->setText("Error");
                return;
            }
        }else{
            std::cout<<"Starting for all"<<std::endl;

            for(unsigned int i=0;i<graph.size();++i){
                if(i != currnetAlgorithm->startVertex()){
                    destinations.push_back(i);
                }
            }
        }

        //set destinations from text input
        semiAnimatedFrameCounted = 0;
        currnetAlgorithm->setDestinations(destinations);
        currnetAlgorithm->initGraph();
        currnetAlgorithm->attach(this);
        currnetAlgorithm->run();

        //this->ui->executionTimeLabel->setText(QString::number(timer.elapsed()) + " ms");
        updateView();
        updateGraphView();
        this->ui->statusLabel->setText("Done");
    }
    else{
        this->ui->statusLabel->setText("Error");
    }
}


void Simulator::updatedObservable(EventTypes eventNb)
{
    //pre defined event - graph reload
    if(eventNb == EVENT_RELOAD){
        //BE CAREFUL THERE IS SOME MEMORY LEACK. PROBALY ON REPAINTING OR COPYING ARGS.
        //repaint graph
        //displayedGraph = graph;
        graphDrawer->setDisplayArguments(displayArguments);
        graphDrawer->repaint();
        return;
    }

    //semi animated
    semiAnimatedFrameCounted++;
    //full animation skip next switch
    switch (displayMode) {
    //quiet mode - no graph displaing
    case 2:

        /*if(semiAnimatedFrameCounted % 10 != 0){
            return;
        }*/

        //updateView();
        return ;

    //semi animated
    case 1:
        if(semiAnimatedFrameCounted % semiAnimatedInterval != 0){
            return;
        }
        break;
    }

    //animate if there is no return before
    //BE CAREFUL THERE IS SOME MEMORY LEACK. PROBALY ON REPAINTING OR COPYING ARGS.
    graphDrawer->setDisplayArguments(displayArguments);
    updateGraphView();
    updateView();
    this->repaint();
}

void Simulator::createAlgorithm(int algorithmIndex)
{

}

void Simulator::updateView()
{
    this->ui->executionTimeLabel->setText(QString::number(timer.elapsed()) + " ms");
    this->ui->bestSolutionLabel->setText(QString::number(currnetAlgorithm->bestSolution()));
    this->ui->currentSolutionLabel->setText(QString::number(currnetAlgorithm->currentSolution()));
    this->ui->bestSolutionLabel->setText(QString::number(currnetAlgorithm->bestSolution()));
    this->ui->currentSolutionLabel->setText(QString::number(currnetAlgorithm->currentSolution()));
    this->ui->bestTimeSolutionLabel->setText(QString::number(currnetAlgorithm->bestTimeSolution()));
    this->ui->currentTimeSolutionLabel->setText(QString::number(currnetAlgorithm->currentTimeSolution()));
    this->ui->bestDistanceSolutionLabel->setText(QString::number(currnetAlgorithm->bestDistanceSolution()));
    this->ui->currentDistanceSolutionLabel->setText(QString::number(currnetAlgorithm->currentDistanceSolution()));
    this->ui->loopsLabel->setText(QString::number(semiAnimatedFrameCounted));
    //update has to be executed seperately
}

void Simulator::updateGraphView()
{
    displayedGraph = currnetAlgorithm->getCurrentGraph();
    //update has to be executed seperately
}
void Simulator::clearView()
{
    if(currnetAlgorithm){
        currnetAlgorithm->initGraph();
    }
    timer.restart();
    semiAnimatedFrameCounted = 0;
    updateView();
    updateGraphView();
    this->repaint();
}

void Simulator::on_displayModeComboBox_activated(int index)
{
    this->displayMode = index;
}

void Simulator::on_semiAnimationIntervalSpinBox_valueChanged(int arg1)
{
    semiAnimatedInterval = arg1;
}

void Simulator::on_clear_clicked()
{
    clearView();
}

void Simulator::on_startVertex_valueChanged(int arg1)
{

}

void Simulator::on_timeFactor_valueChanged(double arg1)
{

}

void Simulator::on_destinations_textChanged(const QString &arg1)
{

}
