#ifndef GRAPHPROCESSING_H
#define GRAPHPROCESSING_H

#include "Graph.h"

class GraphProcessing
{
public:
    GraphProcessing();

    template<class T>
    static std::vector<unsigned int> shortestNeighbour(const Graph<T>& graph, unsigned int begin, unsigned int end);

};



/*
template<class T>
std::vector<unsigned int> GraphProcessing::shortestNeighbour(const Graph<T> &graph, unsigned int begin, unsigned int end)
{

}
*/
#endif // GRAPHPROCESSING_H
