#include "GraphWatcher.h"

GraphWatcher::GraphWatcher(CPPGraph &graph):
    _graph(graph)
{

}

CPPGraph& GraphWatcher::graph() {
    return _graph;
}

const CPPGraph &GraphWatcher::graph() const {
    return _graph;
}

void GraphWatcher::requestUpdate(Observer::EventTypes eventNb)
{
    this->notify(eventNb);
}
