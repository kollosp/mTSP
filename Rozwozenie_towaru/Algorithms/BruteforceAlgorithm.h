#ifndef BRUTEFORCEALGORITHM_H
#define BRUTEFORCEALGORITHM_H
#include "Algorithm.h"

class BruteforceAlgorithm : public Algorithm
{
public:
    BruteforceAlgorithm(CPPGraph &graph, DisplayArgument& displayArgument);

    void run() override;

    std::vector<unsigned int> solveTSP(unsigned int start, std::vector<unsigned int> destinations, CPPWeight &shortestDistance);

    std::vector<std::vector<unsigned int> > buildPairsMatches(const std::vector<unsigned int>& vertices);
    std::vector<std::vector<unsigned int> > buildPairsPermutations(const std::vector<unsigned int>& vertices);

    virtual void applyParams() noexcept override;
};



#endif // BRUTEFORCEALGORITHM_H
