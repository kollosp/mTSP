#ifndef BRUTEFORCEALGORITHM_H
#define BRUTEFORCEALGORITHM_H
#include "Algorithm.h"

class BruteforceAlgorithm : public Algorithm
{
public:
    BruteforceAlgorithm(Graph &graph);

    std::vector<std::vector<unsigned int> >  run() override;

    std::vector<unsigned int> solveTSP(unsigned int start, std::vector<unsigned int> destinations, double &shortestDistance);

    std::vector<std::vector<unsigned int> > buildPairsMatches(const std::vector<unsigned int>& vertices);
    std::vector<std::vector<unsigned int> > buildPairsPermutations(const std::vector<unsigned int>& vertices);
};



#endif // BRUTEFORCEALGORITHM_H
