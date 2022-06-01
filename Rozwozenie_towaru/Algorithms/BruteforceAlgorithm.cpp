#include "BruteforceAlgorithm.h"
#include <QThread>
#include <algorithm>
#include "../Helpers/VectorInteger.h"

#include <iostream>
#include <limits>

BruteforceAlgorithm::BruteforceAlgorithm(CPPGraph &graph, DisplayArgument& displayArgument):
    Algorithm(graph, displayArgument, "Bruteforce")
{
    addParam(ConfigParam("Start v.", Algorithm::ConfigParam::NUMBER, "0"));
    addParam(ConfigParam("Dest.", Algorithm::ConfigParam::STRING, "1,2,3,4"));
}



void BruteforceAlgorithm::run()
{
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
    VectorInteger iterator (destinations.size(), truckNo);

    unsigned int inc=0,dec=0;

    while(iterator.overflow() == false){
        if(iterator.isIncreasing() && iterator.hasAllDigitsUsed()){
            //calculate tsp!
            currentDistanceSolution() = 0;
            currentTimeSolution() = 0;
            std::vector<std::vector<unsigned int> > currentSolutionPath;

            //std::cout<<iterator<<std::endl;
            for(unsigned int i=0;i<truckNo;++i){

                //only when set is not empty
                if(iterator.getDigists(i) > 0){
                    CPPWeight TPSWeight;
                    //take destination vertices from all destinations
                    std::vector<unsigned int> dests = iterator.split(destinations, i);
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

            //std::cout<<"checking solution "<<bestSolution<<", "<<iterationSolution<<std::endl;
            //check if current solution is better then the best
            if(bestSolution() > currentSolution()){
                bestTimeSolution() = currentTimeSolution();
                bestDistanceSolution() = currentDistanceSolution();
                bestSolution() = currentSolution();
                //save best solution paths
                solution = currentSolutionPath;
            }

            //display progress
            displayArgument().paths = currentSolutionPath;
            notify();

            inc ++;
        }else{
            dec ++;
        }

        ++iterator;
    }
    currentSolution() = bestSolution();
    currentTimeSolution() = bestTimeSolution();
    currentDistanceSolution() = bestDistanceSolution();

    /*std::cout<<"inc = "<<inc<<", dec = "<<dec<<std::endl;
    std::cout<<"BRUTFORCE RESULT"<<std::endl;
    std::cout<<"Destinations: "<<destinations<<", trucks: "<<truckNo<<std::endl;
    std::cout<<"tsp sololution = "<<bestSolution()<<", found in "<<inc<<" possible solutions."<<std::endl;
    std::cout<<"Trucks paths: "<<std::endl;
    std::cout<<solution<<std::endl;*/

    displayArgument().paths = solution;

    notify(Observer::EVENT_RELOAD);
}

std::vector<unsigned int> BruteforceAlgorithm::solveTSP(unsigned int start, std::vector<unsigned int> destinations, CPPWeight& shortestDistance)
{


    std::vector<unsigned int> shortestPath = destinations;


    //remove begining vertices from destinations vector. It will be added later
    if(destinations.size() == 0) return shortestPath;
    //if(destinations[0] == start) destinations.erase(destinations.begin());
    //if(destinations[destinations.size()-1] != start) destinations.pop_back();

    //sort to deal greate with next_permutation
    std::sort(destinations.begin(), destinations.end());

    shortestDistance = std::numeric_limits<CPPWeight>::max();

    unsigned int index = 1;
    do{
        CPPWeight currentDistance;
        std::vector<unsigned int> currentPath = graph().computeShortestComplexPath(start, destinations, &currentDistance);
        //std::cout<<"destinations"<<destinations<<"achived by route: "<<currentPath<<std::endl;
        if(currentDistance < shortestDistance){
            shortestPath = currentPath;
            shortestDistance = currentDistance;
        }
        //std::cout<<index<<". "<<currentDistance<<", "<<currentPath<<", "<<destinations<<std::endl;
        index ++;

    }while(std::next_permutation(destinations.begin(), destinations.end()));

    //std::cout<<"solving TSP: "<<start<<" "<<destinations<<" result = "<<shortestDistance<<std::endl;
    return shortestPath;
}

std::vector<std::vector<unsigned int> > BruteforceAlgorithm::buildPairsPermutations(const std::vector<unsigned int> &vertices)
{

    std::vector<unsigned int> indexes;
    for(unsigned int i=0;i<vertices.size();++i){
        indexes.push_back(vertices.at(i));
    }

    std::vector<std::vector<unsigned int> > permutations;
    perm(permutations,indexes);

    //std::cout<<permutations<<std::endl;
    return permutations;
}

void BruteforceAlgorithm::applyParams() noexcept
{

}
