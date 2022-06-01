#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <Monitor/Observable.h>
#include <Graph/GraphTypes.h>
#include "../Helpers/DisplayArguments.h"



/*
 *
 * *
 *
0. [ 0 5 2 30 8 7 20 19 6 30 2 5 0]
1. [ 0 4 1 9 18 9 1 4 0]
2. [ 0 28 29 15 0]
 */

/**
 * @brief The Algorytm class Basic class of algorytms, Provide the simplest and most common algorytm processing functions and i
 */
class Algorithm : public Observable
{
public:
    /**
     * @brief The ConfigParam class def name and value of parameter
     */
    class ConfigParam {
    public:
        enum Type {
            NUMBER = 1,
            STRING = 2
        };
    private:
        std::string _name;
        std::string _value;
        Type _type;

    public:
        ConfigParam(const std::string& name, const Type& type, const std::string &value="");
        const std::string& name() const noexcept;
        std::string &name() noexcept;
        const std::string &value() const noexcept;
        std::string& value() noexcept;
        const Type& type() const noexcept;
        Type& type() noexcept;
    };

    CPPGraph& _graph;
    CPPGraph _bestGraph;
    CPPWeight _bestSolution;
    CPPWeight _currentSolution;

    CPPWeight _bestTimeSolution;
    CPPWeight _currentTimeSolution;

    CPPWeight _bestDistanceSolution;
    CPPWeight _currentDistanceSolution;

    DisplayArgument& _displayArgument;

    /**
     * @brief _timeFactor defines which travel parameter is more important. Time or distance.
     * _timeFactor is a value in range of 0..1. 1 means that evaluation of solution will be based only on
     * time. On the other hand 0 means only on distance.
     */
    float _timeFactor = 0.5;

    std::vector<unsigned int> destinations = {1,4,7,8,19,6,30,5,15};

    unsigned int _startVertex = 0;
    unsigned int _truckNo = 3;

private:

    /**
     * @brief _name name of the algorytm used in gui
     */
    std::string _name;
    std::vector<ConfigParam> _params;

public:
    Algorithm(CPPGraph& graph, DisplayArgument& DisplayArgument, const std::string&name);
    virtual ~Algorithm();

    float timeFactor() const;
    float& timeFactor();
    float distanceFactor();
    void initGraph();

    const std::string& name() const noexcept;

    const std::vector<ConfigParam>& params() const noexcept;
    std::vector<ConfigParam>& params() noexcept;

    const std::vector<unsigned int>& getDestinations() const;
    std::vector<unsigned int>& getDestinations();

    unsigned int startVertex() const noexcept;
    unsigned int& startVertex()  noexcept;
    unsigned int truckNo() const noexcept;
    unsigned int& truckNo()  noexcept;

    void setDestinations(const std::vector<unsigned int>& dest);

    /**
     * @brief removeFromVector Function removes content of modifier from output vector. It works only for distinct values!
     * @param output
     * @param modifier
     */
    template< class T>
    void removeFromVector(std::vector<T>& output, const std::vector<T>& modifier) {
        for(unsigned int i=0;i<modifier.size();++i){
            for(unsigned int j=0;j<output.size();++j){
                if(output[j] == modifier[i]){
                    output.erase(output.begin()+j);
                }
            }
        }
    }

    /**
     * @brief applyParams Funcion transform values form configuration into useful paraemeters stored as class members.
     */
    virtual void applyParams() noexcept = 0;

    /**
     * @brief run run algorithm
     */
    virtual void run() = 0;

    /**
     * @brief getCurrentGraph. If algorythm is observered by gui then it sends notification when each loop has been finished. When
     *  oberveris notificated then it checks state of the current best graph path/graph.
     * @return
     */
    const CPPGraph& getCurrentGraph() const noexcept;
    const CPPGraph& getBestGraph() const noexcept;

protected:
    void addParam(const ConfigParam& param);

    CPPGraph &graph() noexcept;
    CPPGraph &bestGraph() noexcept;

    DisplayArgument& displayArgument() noexcept;

public:
    CPPWeight &bestSolution() noexcept;
    CPPWeight &currentSolution() noexcept;

    CPPWeight &bestTimeSolution() noexcept;
    CPPWeight &currentTimeSolution() noexcept;

    CPPWeight &bestDistanceSolution() noexcept;
    CPPWeight &currentDistanceSolution() noexcept;

    template< class T>
    bool nextSet(const std::vector<std::vector<T> >& possibility, std::vector<unsigned int>& controlVector, unsigned int currentIndex = 0);

    template<class T>
    void perm(std::vector<std::vector<T>>& permutations,std::vector<T>& vector, unsigned int position = 0);
};



template<class T>
bool Algorithm::nextSet(const std::vector<std::vector<T> > &possibility, std::vector<unsigned int> &controlVector, unsigned int currentIndex)
{
    bool returnValue = true;
    if(currentIndex == possibility.size()-1){
        controlVector.at(currentIndex) ++;
    }else{
        nextSet(possibility, controlVector, currentIndex+1);
    }

    if(controlVector.at(currentIndex) >= possibility.at(currentIndex).size()){
        controlVector.at(currentIndex) = 0;

        if(currentIndex != 0){
            controlVector.at(currentIndex - 1) ++;
            returnValue = true;
        }else{
            //all permutaiotns done, we are again in the first (0,0,0,....,0)
            returnValue = false;
        }
    }

    return returnValue;
}

template<class T>
void Algorithm::perm(std::vector<std::vector<T>>& permutations,std::vector<T>& vector, unsigned int position) {
    if (position == vector.size()) {

        bool correctInPairs = true;
        bool correctInVectors = true;
        T last = vector[0];
        for(unsigned int i=0;i<vector.size();i+=2){
            if(vector[i] > vector[i+1]){
                correctInPairs = false;
            }

            if(last > vector[i]){
                correctInVectors = false;
            }

            last = vector[i];
        }

        if(correctInPairs && correctInVectors){
            permutations.push_back(vector);
        }

        return;
    } else {
        for (unsigned int i = position; i < vector.size(); i++) {
            std::swap(vector[i], vector[position]);
            perm(permutations, vector, position + 1);
            std::swap(vector[i], vector[position]);
        }
    }
}

#endif // ALGORITHM_H
