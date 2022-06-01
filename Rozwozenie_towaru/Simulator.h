#ifndef SIMULATION_H
#define SIMULATION_H

#include "GraphDrawing/GraphDrawingWidget.h"

#include <QStackedWidget>
#include <QWidget>

#include "Graph/GraphTypes.h"
#include "Algorithms/TestAlgorithm.h"
#include "Algorithms/NearestNeighbor.h"
#include "Helpers/DisplayArguments.h"

#include <QElapsedTimer>



namespace Ui {
class Simulation;
}

class Simulator : public QWidget, public Observer
{
    Q_OBJECT

    QStackedWidget* configContainer;
    GraphDrawingWidget* graphDrawer;
    CPPGraph &graph;
    CPPGraph displayedGraph;

    Algorithm *currnetAlgorithm;
    QElapsedTimer timer;

    DisplayArgument displayArguments;

    /**
     * @brief displayMode define how offent simulation view should be updated (reprinted) during graph processing.
     * 0 - full animated mode - update after each iteration of the algorithm
     * 1 - semi animated mode - update in the interval of semianimatedInterval
     * 2 - quiet mode - updating is disabled
     */
    int displayMode = 1;
    unsigned int semiAnimatedInterval = 25;
    unsigned int semiAnimatedFrameCounted;
public:
    explicit Simulator(CPPGraph &graph, QWidget *parent = nullptr);
    ~Simulator();

    void updateView();
    void updateGraphView();
    void clearView();
    void updatedObservable(Observer::EventTypes eventNb) override;

    void createAlgorithm(int algorithmIndex);

private slots:

    void on_runAlgorithm_clicked();
    void on_displayModeComboBox_activated(int index);
    void on_semiAnimationIntervalSpinBox_valueChanged(int arg1);

    void on_clear_clicked();
    void on_algorythmComboBox_activated(int index);
    void on_startVertex_valueChanged(int arg1);

    void on_timeFactor_valueChanged(double arg1);

    void on_destinations_textChanged(const QString &arg1);

private:
    Ui::Simulation *ui;
};

#endif // SIMULATION_H
