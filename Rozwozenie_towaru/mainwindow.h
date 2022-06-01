#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "Graph/GraphTypes.h"
#include "GraphWatcher.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QStackedWidget* container;

    const unsigned int SIMULATOR_SCREEN = 1;
    const unsigned int ABOUT_SCREEN = 0;
    const unsigned int GRAPH_GENERATOR_SCREEN = 2;

    //the main instalace of the graph
    CPPGraph graph;
    GraphWatcher *graphWatcher;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void switchScreen(unsigned int index);

private slots:

    void on_GoToSimulatorScreen_clicked();
    void on_GoToGraphGeneratorScreen_clicked();
    void on_GoToAboutScreen_clicked();

    void on_actionLoad_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
