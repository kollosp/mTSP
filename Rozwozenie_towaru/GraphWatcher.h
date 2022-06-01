#ifndef GRAPHWATCHER_H
#define GRAPHWATCHER_H

#include "Monitor/Observable.h"
#include "Graph/GraphTypes.h"
#include "GraphGenerator/MapGraphGenerator.h"

class GraphWatcher : public Observable
{
    CPPGraph& _graph;

public:
    GraphWatcher(CPPGraph& _graph);

    CPPGraph &graph();
    const CPPGraph& graph() const;

    /**
     * @brief requestUpdate request update all observers. Execute when graph changed
     */
    void requestUpdate(Observer::EventTypes eventNb);
};

#endif // GRAPHWATCHER_H
