#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
#include "Algorithm.h"

class GeneticAlgorithm : public Algorithm
{
    unsigned int generations = 10000;
    unsigned int population = 10;


    std::vector<std::vector< unsigned int > > createGeneration(const std::vector<unsigned int>& parent);
    std::vector< unsigned int > mutate(const std::vector<unsigned int>& parent);

public:
    GeneticAlgorithm(Graph& graph);

    std::vector<unsigned int> solveTSP(unsigned int start, std::vector<unsigned int> destinations, double& shortestDistance);
    std::vector<std::vector<unsigned int> > run() override;

    /**
     * @brief calculateRequiredGenCount function is required because if destinations count is low then algorithm do much more iteration then
     * possibilities exist.
     * @return
     */
    unsigned int calculateRequiredGenCount(unsigned int destinationsCount);

    std::vector<unsigned int> mutate(const std::vector<unsigned int> &parent, const std::vector<unsigned int> &splitter);
    std::vector<std::vector<unsigned int> > createGeneration(const std::vector<unsigned int> &parent, const std::vector<unsigned int> &splitter);
};

#endif // GENETICALGORITHM_H
