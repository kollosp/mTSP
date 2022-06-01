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

GeneticAlgorithm::GeneticAlgorithm(CPPGraph &graph, DisplayArgument& displayArgument):
    Algorithm(graph, displayArgument, "Genetic")
{
}

void GeneticAlgorithm::run()
{
    //std::cout<<"void GeneticAlgorithm::run()"<<std::endl;;
    std::vector<unsigned int> destinations = getDestinations();

    for(unsigned int i=0;i<graph().size();++i){
        graph().vertex(i).setArtificialFlag(0);
    }
    for(unsigned int i=0;i<destinations.size();++i){
        graph().vertex(destinations[i]).setArtificialFlag(1);
    }


    unsigned int truckNo = this->truckNo();
    unsigned int start = startVertex();
    std::vector<std::vector<unsigned int> > solution;
    bestSolution() = std::numeric_limits<CPPWeight>::max();

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
        //std::cout<<"void GeneticAlgorithm::run() "<<generationCount<<std::endl;;

        std::vector<std::vector<unsigned int> > population = createGeneration(parent, splitters);


        CPPWeight bestPopulation = std::numeric_limits<CPPWeight>::max();
        for(unsigned int k=0;k<population.size();++k){
            //std::cout<<"void GeneticAlgorithm::run() "<<generationCount<<" "<<k<<std::endl;;

            for(unsigned int i=0;i<truckNo;++i){

                //only when set is not empty
                CPPWeight TPSWeight;
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
            //std::cout<<"New best found"<<std::endl;
        }

        //display progress
        displayArgument().paths = currentSolutionPath;
        notify();
    }

    currentSolution() = bestSolution();
    currentTimeSolution() = bestTimeSolution();
    currentDistanceSolution() = bestDistanceSolution();

    /*std::cout<<"GENETIC RESULT"<<std::endl;
    std::cout<<"Destinations: "<<destinations<<", trucks: "<<truckNo<<std::endl;
    std::cout<<"tsp sololution = "<<bestSolution()<<std::endl;
    std::cout<<"Trucks paths: "<<std::endl;
    std::cout<<solution<<std::endl;*/

    displayArgument().paths = solution;

    notify(Observer::EVENT_RELOAD);
}

unsigned int GeneticAlgorithm::getGenerations() const
{

    return generations;
}

unsigned int &GeneticAlgorithm::getGenerations()
{
    return generations;
}

unsigned int GeneticAlgorithm::getPopulation() const
{
    return  population;
}

unsigned int &GeneticAlgorithm::getPopulation()
{
    return  population;
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




std::vector<unsigned int> GeneticAlgorithm::solveTSP(unsigned int start, std::vector<unsigned int> destinations, CPPWeight& shortestDistance){
    //odd vertices is an ordered list of vertices so it is the first permutation
    std::vector<unsigned int> lastGenerationBest = destinations;
    std::vector<unsigned int> ret;
    //CPPGraph origin = graph();

    shortestDistance = std::numeric_limits<CPPWeight>::max();

    unsigned int genCalculated = calculateRequiredGenCount(destinations.size());

    for(unsigned int i=0;i<genCalculated;++i){

        unsigned int bestSolutionIndex = 0;
        //create generation base on the best solution from last generation
        std::vector<std::vector<unsigned int> > population = createGeneration(lastGenerationBest);

        //always use best of current population
        CPPWeight currentSolution = std::numeric_limits<CPPWeight>::max();

        //calculate value of each individual
        for(unsigned int j=0;j<population.size();++j){

            //itereate throught all pairs in selected permutation.
            //find every possible roads between vertices in pair.
            CPPWeight individualSolution;
            std::vector<unsigned int> currentPath = graph().computeShortestComplexPath(start, population[j], &individualSolution);

            //best of current population
            if(individualSolution < currentSolution){
                currentSolution = individualSolution;
                bestSolutionIndex = j;
            }

            //std::cout<<"destinations"<<destinations<<"achived by route: "<<currentPath<<" length: "<<currentSolution<<std::endl;
            //check if current is better then known best solution
            if(currentSolution < shortestDistance){
                shortestDistance = currentSolution;
                ret = currentPath;
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

void GeneticAlgorithm::applyParams() noexcept
{

}
