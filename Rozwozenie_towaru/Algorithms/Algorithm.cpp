#include "Algorithm.h"

Algorithm::Algorithm(Graph &graph) :
    _graph(graph)
{

}

Algorithm::~Algorithm()
{

}

float &Algorithm::timeFactor()
{
    return _timeFactor;

}

float Algorithm::timeFactor() const
{
    return _timeFactor;
}

float Algorithm::distanceFactor()
{
    return 1-_timeFactor;
}

void Algorithm::initGraph()
{
    _bestSolution = 0;
    _currentSolution = 0;
}

const std::vector<unsigned int> &Algorithm::getDestinations() const
{
    return destinations;
}

std::vector<unsigned int> &Algorithm::getDestinations()
{
    return destinations;
}

unsigned int Algorithm::startVertex() const
{
    return _startVertex;
}

unsigned int &Algorithm::startVertex()
{
    return _startVertex;
}

unsigned int Algorithm::truckNo() const
{
    return _truckNo;
}

unsigned int &Algorithm::truckNo()
{
    return _truckNo;
}

void Algorithm::setDestinations(const std::vector<unsigned int> &dest)
{
    destinations = dest;
}

const Graph &Algorithm::getCurrentGraph() const
{
    return _graph;
}

Graph &Algorithm::graph()
{
    return _graph;
}

double &Algorithm::bestSolution()
{
    return _bestSolution;
}

double &Algorithm::currentSolution()
{
    return _currentSolution;
}

double &Algorithm::bestTimeSolution()
{
    return _bestTimeSolution;
}

double &Algorithm::currentTimeSolution()
{
    return _currentTimeSolution;
}

double &Algorithm::bestDistanceSolution()
{
    return _bestDistanceSolution;
}

double &Algorithm::currentDistanceSolution()
{
    return _currentDistanceSolution;
}
