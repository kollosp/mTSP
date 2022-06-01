#include "NearestNeighbor.h"

#include <Helpers/VectorInteger.h>


NearestNeighbor::NearestNeighbor(CPPGraph &graph, DisplayArgument &displayArgument) :
    Algorithm(graph, displayArgument, "NearestNeighbor")
{

}

void NearestNeighbor::run()
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
        if(iterator.isIncreasing() && iterator.hasAllDigitsUsed() && iterator.hasEqualCountOfDigites(1)){
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
    std::cout<<"NN RESULT"<<std::endl;
    std::cout<<"Destinations: "<<destinations<<", trucks: "<<truckNo<<std::endl;
    std::cout<<"tsp sololution = "<<bestSolution()<<", found in "<<inc<<" possible solutions."<<std::endl;
    std::cout<<"Trucks paths: "<<std::endl;
    std::cout<<solution<<std::endl;*/

    displayArgument().paths = solution;

    notify(Observer::EVENT_RELOAD);
}

std::vector<unsigned int> NearestNeighbor::solveTSP(unsigned int start, std::vector<unsigned int> destinations, CPPWeight &shortestDistance)
{
    //odd vertices is an ordered list of vertices so it is the first permutation
    std::vector<unsigned int> ret;
    //CPPGraph origin = graph();

    shortestDistance = std::numeric_limits<CPPWeight>::max();
    unsigned int destinationsCount = destinations.size();
    unsigned int currentStart = start;
    for(unsigned int i=0;i<destinationsCount;++i){
        unsigned int nn;
        unsigned int index;
        CPPWeight currentDistance = std::numeric_limits<CPPWeight>::max();

        //find nearest neighbour
        for(unsigned int j=0;j<destinations.size();++j){
            CPPWeight d = graph().edge(currentStart, destinations[j]).value();
            //std::cout<<i<<". "<<currentStart<<" -> "<<destinations[j]<<" = "<<d<<std::endl;
            if(d < currentDistance){
                nn = destinations[j];
                currentDistance = d;
                index = j;
            }
        }
        destinations.erase(destinations.begin()+index);

        ret.push_back(nn);
        currentStart = nn;
        //std::cout<<i<<". best at: "<<index<<" v left: "<<destinations<<" path: "<<ret<<std::endl;
    }

    return graph().computeShortestComplexPath(start, ret, &shortestDistance);;
}

void NearestNeighbor::applyParams() noexcept
{

}
