#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Simulator.h"
#include "About.h"
#include "Graphgenerator.h"

#include <QFileDialog>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graph.readFromFile("../graph.txt");

    graphWatcher = new GraphWatcher(graph);

    container = new QStackedWidget(this);
    ((QVBoxLayout*)this->ui->centralwidget->layout())->addWidget(container);


    container->addWidget(new About());

    //attach screen to the graph watcher object. All attached object will be notify when
    //graph watcher detects graph changed event.
    Simulator* simulator = new Simulator(graph);
    graphWatcher->attach(simulator);
    container->addWidget(simulator);
    GraphGenerator* generator = new GraphGenerator(graph);
    graphWatcher->attach(generator);
    container->addWidget(generator);

    switchScreen(SIMULATOR_SCREEN);
}

MainWindow::~MainWindow()
{
    delete graphWatcher;
    delete container;
    delete ui;
}


void MainWindow::switchScreen(unsigned int index)
{
    container->setCurrentIndex(index);
}

void MainWindow::on_GoToSimulatorScreen_clicked()
{
    switchScreen(SIMULATOR_SCREEN);
}

void MainWindow::on_GoToGraphGeneratorScreen_clicked()
{
    switchScreen(GRAPH_GENERATOR_SCREEN);
}

void MainWindow::on_GoToAboutScreen_clicked()
{
    switchScreen(ABOUT_SCREEN);
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load File"),
                               "", tr("Graph (*.txt)"));
    graph.readFromFile(fileName.toStdString());
    graphWatcher->requestUpdate(Observer::EventTypes::EVENT_RELOAD);
}

void MainWindow::on_actionSave_triggered()
{
    if(graph.path() == ""){
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "", tr("Graph (*.txt)"));
        graph.writeToFile(fileName.toStdString());
    }else{
        graph.writeToFile(graph.path());
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               QString::fromStdString(graph.path()), tr("Graph (*.txt)"));
    graph.path();
    graph.writeToFile(fileName.toStdString());
}
