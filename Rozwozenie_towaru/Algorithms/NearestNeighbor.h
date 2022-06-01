#ifndef NEARESTNEIGHBOR_H
#define NEARESTNEIGHBOR_H


#include "Algorithm.h"

class NearestNeighbor : public Algorithm
{
public:
    NearestNeighbor(CPPGraph &graph, DisplayArgument& displayArgument);

    void run() override;

    std::vector<unsigned int> solveTSP(unsigned int start, std::vector<unsigned int> destinations, CPPWeight &shortestDistance);

    virtual void applyParams() noexcept override;
};

#endif // NEARESTNEIGHBOR_H
