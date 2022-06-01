#include "Algorithm.h"

Algorithm::Algorithm(CPPGraph &graph, DisplayArgument& displayArgument, const std::string &name) :
    _graph(graph), _displayArgument(displayArgument), _name(name)
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
    _bestSolution = CPPWeight();
    _currentSolution = CPPWeight();
}

const std::string &Algorithm::name() const noexcept
{
    return _name;
}

const std::vector<Algorithm::ConfigParam> &Algorithm::params() const noexcept
{
    return _params;
}

std::vector<Algorithm::ConfigParam> &Algorithm::params() noexcept
{
    return _params;
}

const std::vector<unsigned int> &Algorithm::getDestinations() const
{
    return destinations;
}

std::vector<unsigned int> &Algorithm::getDestinations()
{
    return destinations;
}

unsigned int Algorithm::startVertex() const noexcept
{
    return _startVertex;
}

unsigned int &Algorithm::startVertex() noexcept
{
    return _startVertex;
}

unsigned int Algorithm::truckNo() const noexcept
{
    return _truckNo;
}

unsigned int &Algorithm::truckNo() noexcept
{
    return _truckNo;
}

void Algorithm::setDestinations(const std::vector<unsigned int> &dest)
{
    destinations = dest;
}

const CPPGraph &Algorithm::getCurrentGraph() const noexcept
{
    return _graph;
}

const CPPGraph &Algorithm::getBestGraph() const noexcept
{
    return _bestGraph;
}

void Algorithm::addParam(const Algorithm::ConfigParam &param)
{
    _params.push_back(param);
}

CPPGraph& Algorithm::graph() noexcept
{
    return _graph;
}

CPPGraph &Algorithm::bestGraph() noexcept
{
    return _bestGraph;
}

DisplayArgument &Algorithm::displayArgument() noexcept
{
    return _displayArgument;
}

CPPWeight &Algorithm::bestSolution() noexcept
{
    return _bestSolution;
}

CPPWeight &Algorithm::currentSolution() noexcept
{
    return _currentSolution;
}

CPPWeight &Algorithm::bestTimeSolution() noexcept
{
    return _bestTimeSolution;
}

CPPWeight &Algorithm::currentTimeSolution() noexcept
{
    return _currentTimeSolution;
}

CPPWeight &Algorithm::bestDistanceSolution() noexcept
{
    return _bestDistanceSolution;
}

CPPWeight &Algorithm::currentDistanceSolution() noexcept
{
    return _currentDistanceSolution;
}

Algorithm::ConfigParam::ConfigParam(const std::string &name, const Algorithm::ConfigParam::Type &type, const std::string& value)
    : _name(name), _value(value), _type(type)
{

}

const std::string &Algorithm::ConfigParam::name() const noexcept
{
    return _name;
}

std::string &Algorithm::ConfigParam::name() noexcept
{
    return _name;
}

const std::string &Algorithm::ConfigParam::value() const noexcept
{
    return  _value;
}

std::string &Algorithm::ConfigParam::value() noexcept
{
    return _value;
}

const Algorithm::ConfigParam::Type &Algorithm::ConfigParam::type() const noexcept
{
    return _type;
}

Algorithm::ConfigParam::Type &Algorithm::ConfigParam::type() noexcept
{
    return _type;
}
