#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <QWidget>
#include "Graph/GraphTypes.h"
#include "GraphGenerator/MapGraphGenerator.h"

#include "Monitor/Observer.h"
#include <cmath>

namespace Ui {
class GraphGenerator;
}

class GraphGenerator : public QWidget, public Observer
{
    Q_OBJECT

    bool enableSelfRelationFlag = false;
    bool enableBidirectionalRelationFlag = true;

    MapGraphGenerator* gen;
    CPPGraph& graph;

public:
    explicit GraphGenerator(CPPGraph &graph, QWidget *parent = nullptr);
    ~GraphGenerator();

    void updateView();
    void updateStatistics();

    void updatedObservable(Observer::EventTypes eventNb) override;

private slots:
    void on_addVertice_clicked();
    void on_table_cellChanged(int row, int column);
    void on_selfRelation_stateChanged(int arg1);
    void on_bidirectional_stateChanged(int arg1);

    void on_switchEditMode_clicked();

    void on_loadBg_clicked();

    void on_genCompleteGraph_clicked();

    void on_disableBg_clicked();

private:
    Ui::GraphGenerator *ui;
};

#endif // GRAPHGENERATOR_H
