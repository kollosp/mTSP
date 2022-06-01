#include "GeneticAlgorithm.h"
#include "Helpers/VectorInteger.h"

std::vector<unsigned int> GeneticAlgorithm::mutate(const std::vector<unsigned int> &parent)
{
    unsigned int first = rand() % parent.size();
    unsigned int second;

    //be sure that first and second are different
    int iterator=5;
    do{
        second = rand() % parent.size();
        iterator--;
    }while (first == second && iterator);

    //swap elements
    std::vector<unsigned int> ret = parent;
    std::swap(ret.at(first), ret.at(second));
    return ret;
}

std::vector<unsigned int> GeneticAlgorithm::mutate(const std::vector<unsigned int> &parent, const std::vector<unsigned int> & splitter)
{
    unsigned int first = rand() % parent.size();
    unsigned int firstGroup;
    for(unsigned int i=1;i<splitter.size();++i){
        if(first >= splitter[i-1] && first< splitter[i]){
            firstGroup = i;
        }
    }
    unsigned int second;

    //be sure that first and second are different
    bool correct = false;
    do{
        second = rand() % parent.size();

        for(unsigned int i=1;i<splitter.size();++i){
            if(second >= splitter[i-1] && second< splitter[i]){
                if(i != firstGroup) correct = true;
            }
        }

    }while (!correct);

    //swap elements
    std::vector<unsigned int> ret = parent;
    std::swap(ret.at(first), ret.at(second));
    return ret;
}

GeneticAlgorithm::GeneticAlgorithm(Graph &graph):
    Algorithm(graph)
{
}

std::vector<std::vector<unsigned int> >  GeneticAlgorithm::run()
{
    std::vector<unsigned int> destinations = getDestinations();

    unsigned int truckNo = this->truckNo();
    unsigned int start = startVertex();
    std::vector<std::vector<unsigned int> > solution;
    bestSolution() = std::numeric_limits<double>::max();

    std::vector<unsigned int> splitters;
    splitters.push_back(0);
    for(unsigned int i=1;i<truckNo;++i){
        float step = 1.0*destinations.size()/truckNo;
        splitters.push_back(step*i);
    }
    splitters.push_back(destinations.size());

    std::vector<unsigned int> parent=destinations;

    for(unsigned int generationCount=0; generationCount < 10000; generationCount++){

        //calculate tsp!
        currentDistanceSolution() = 0;
        currentTimeSolution() = 0;
        std::vector<std::vector<unsigned int> > currentSolutionPath;
        std::vector<std::vector<unsigned int> > population = createGeneration(parent, splitters);


        double bestPopulation = std::numeric_limits<double>::max();
        for(unsigned int k=0;k<population.size();++k){
            for(unsigned int i=0;i<truckNo;++i){

                //only when set is not empty
                double TPSWeight;
                //take destination vertices from all destinations
                std::vector<unsigned int> dests(population[k].begin()+splitters[i], population[k].begin()+splitters[i+1]);
                //remove already visited vertices
                for(unsigned int k=0;k<currentSolutionPath.size();++k){
                    removeFromVector(dests,currentSolutionPath[k]);
                }

                if(dests.size() > 0){
                    //solve tsp
                    std::vector<unsigned int> truckPath = solveTSP(start, dests, TPSWeight);


                    currentSolutionPath.push_back(truckPath);
                    //add trock tsp solution to sum
                    currentDistanceSolution() += TPSWeight;

                    if(currentTimeSolution() < TPSWeight){
                        currentTimeSolution() = TPSWeight;

                    }

                    currentSolution() = currentTimeSolution() * timeFactor() + currentDistanceSolution() * distanceFactor();
                }
            }

            //find best in population
            if(currentSolution() < bestPopulation){
                bestPopulation = currentSolution();
                parent = population[k];
            }

        }

        //check if current solution is better then the best
        if(bestSolution() > currentSolution()){
            bestTimeSolution() = currentTimeSolution();
            bestDistanceSolution() = currentDistanceSolution();
            bestSolution() = currentSolution();
            //save best solution paths
            solution = currentSolutionPath;

            std::cout<<"Znaleziono nowe minium. Pokolenie: "<<generationCount<<std::endl;
            std::cout<<"Waga biezacego rozwiazania = "<<bestSolution()<<std::endl;
            std::cout<<"Trasy ciezarowek: "<<std::endl;
            std::cout<<solution<<std::endl;
        }
    }

    currentSolution() = bestSolution();
    currentTimeSolution() = bestTimeSolution();
    currentDistanceSolution() = bestDistanceSolution();

    std::cout<<"=== ROZWIAZANIE === "<<std::endl;
    std::cout<<"ALGORYTM GENETYCZNY"<<std::endl;
    std::cout<<"Wierzcholki docelowe: "<<destinations<<", liczba ciezarowek: "<<truckNo<<std::endl;
    std::cout<<"Waga najlepszego rozwiazania = "<<bestSolution()<<std::endl;
    std::cout<<"Trasy ciezarowek: "<<std::endl;
    std::cout<<solution<<std::endl;
    return solution;
}

unsigned int GeneticAlgorithm::calculateRequiredGenCount(unsigned int destinationsCount)
{
    unsigned int allPossibilieties = 1;
    for(unsigned int i=2;i<destinationsCount;++i){
        allPossibilieties*=i;

        //if there is more possible
        if(allPossibilieties > generations)
            return generations;
    }
    return allPossibilieties;
}

std::vector<std::vector<unsigned int> > GeneticAlgorithm::createGeneration(const std::vector<unsigned int>& parent)
{
    std::vector<std::vector<unsigned int> > generation;

    for(unsigned int i=0;i<population;++i){
        generation.push_back(mutate(parent));
    }

    return generation;
}

std::vector<std::vector<unsigned int> > GeneticAlgorithm::createGeneration(const std::vector<unsigned int>& parent,const std::vector<unsigned int> & splitter)
{
    std::vector<std::vector<unsigned int> > generation;

    for(unsigned int i=0;i<population;++i){
        generation.push_back(mutate(parent, splitter));
    }

    return generation;
}




std::vector<unsigned int> GeneticAlgorithm::solveTSP(unsigned int start, std::vector<unsigned int> destinations, double &shortestDistance){
    //odd vertices is an ordered list of vertices so it is the first permutation
    std::vector<unsigned int> lastGenerationBest = destinations;
    std::vector<unsigned int> ret;
    //CPPGraph origin = graph();

    shortestDistance = std::numeric_limits<double>::max();

    unsigned int genCalculated = calculateRequiredGenCount(destinations.size());

    for(unsigned int i=0;i<genCalculated;++i){

        unsigned int bestSolutionIndex = 0;
        //create generation base on the best solution from last generation
        std::vector<std::vector<unsigned int> > population = createGeneration(lastGenerationBest);

        //always use best of current population
        double currentSolution = std::numeric_limits<double>::max();

        //calculate value of each individual
        for(unsigned int j=0;j<population.size();++j){

            //itereate throught all pairs in selected permutation.
            //find every possible roads between vertices in pair.
            double individualSolution = graph().computeShortestComplexPath(start, population[j]);

            //best of current population
            if(individualSolution < currentSolution){
                currentSolution = individualSolution;
                bestSolutionIndex = j;
            }

            //std::cout<<"destinations"<<destinations<<"achived by route: "<<currentPath<<" length: "<<currentSolution<<std::endl;
            //check if current is better then known best solution
            if(currentSolution < shortestDistance){
                shortestDistance = currentSolution;
                ret = population[j];
                //save best solution individual index, to use it to build new generation
                bestSolutionIndex = j;
            }
        }

        //set last generation best
        if(bestSolutionIndex > population.size())
            lastGenerationBest = population.at(bestSolutionIndex);
    }

    return ret;
}
