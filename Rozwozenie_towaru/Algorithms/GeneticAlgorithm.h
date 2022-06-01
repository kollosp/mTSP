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
    GeneticAlgorithm(CPPGraph& graph, DisplayArgument &displayArgument);

    std::vector<unsigned int> solveTSP(unsigned int start, std::vector<unsigned int> destinations, CPPWeight& shortestDistance);
    void run() override;

    unsigned int getGenerations() const;
    unsigned int& getGenerations();

    unsigned int getPopulation() const;
    unsigned int& getPopulation();


    /**
     * @brief calculateRequiredGenCount function is required because if destinations count is low then algorithm do much more iteration then
     * possibilities exist.
     * @return
     */
    unsigned int calculateRequiredGenCount(unsigned int destinationsCount);


    virtual void applyParams() noexcept override;
    std::vector<unsigned int> mutate(const std::vector<unsigned int> &parent, const std::vector<unsigned int> &splitter);
    std::vector<std::vector<unsigned int> > createGeneration(const std::vector<unsigned int> &parent, const std::vector<unsigned int> &splitter);
};

#endif // GENETICALGORITHM_H
