#include "mainwindow.h"

#include <QApplication>
#include "Graph/GraphTests.h"
#include "Graph/Tree.h"


#include "Algorithms/BruteforceAlgorithm.h"
#include "Algorithms/NearestNeighbor.h"
#include "Algorithms/GeneticAlgorithm.h"

int gui(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}



int testsAccurancy(int argc, char *argv[]){
    CPPGraph graph;

    DisplayArgument arg;


    BruteforceAlgorithm ba(graph,arg);
    GeneticAlgorithm ga(graph,arg);

    ga.timeFactor() = 1;
    ba.timeFactor() = 1;

    std::vector<unsigned int> graphSize = {7,8,9,10,11};
    std::vector<float> generations = {2000,4000,6000,8000,10000,15000,20000};
    std::vector<float> population = {2,4,8,10,12,14,16};
    std::vector<unsigned int> truckno = {2,3,4};
    unsigned int startVertex = 0;


    std::cout<<"graph size, truck no, time factor, best in currant graph found by bruteforce, generations, population, solution by genetic, execution time"<<std::endl;


    for(unsigned int j=0;j<graphSize.size();++j){

        graph.random(graphSize[j]);
        std::vector<unsigned int> v(graph.size());
        for(unsigned int i=0;i<graph.size();++i){
            v.at(i) = i;
        }
        //usuniecie wierzcholka startu z wektora wierzcholkow docelowych
        v.erase(v.begin()+startVertex);

        ba.startVertex() = startVertex;
        ba.setDestinations(v); //ustawienie wszystkich pozostalych wierzcholkow jako docelowe

        ga.startVertex() = startVertex;
        ga.setDestinations(v); //ustawienie wszystkich pozostalych wierzcholkow jako docelowe

        for(unsigned int z=0;z<truckno.size();++z){

            ba.run();
            unsigned int best = ba.bestSolution();

            ga.truckNo() = truckno[z];

            for(unsigned int k=0;k<generations.size();++k){
                ga.getGenerations() = generations[k];

                for(unsigned int i=0;i<population.size();++i){
                    ga.getPopulation() = population[i];


                    //std::cout<<"Starting "<<algorithm->name()<<std::endl;
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    ga.run();
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    double time = std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();

                    std::cout<<graphSize[j]<<", "<<truckno[z]<<", "<<1<<", "<<best<<", "<<generations[k]<<", "<<population[i]<<", "<<ga.bestSolution()<<", "<<time<<std::endl;
                }
            }
        }

    }


}


int tests(int argc, char *argv[]){

    CPPGraph graph;

    DisplayArgument arg;

    std::vector<Algorithm*> algorithms = {
        new BruteforceAlgorithm(graph,arg),
        new NearestNeighbor(graph,arg),
        new GeneticAlgorithm(graph,arg),
    };

    std::vector<unsigned int> graphSize = {7,8,9,10,11};
    std::vector<float> timeFactor = {0,0.5,1};
    std::vector<unsigned int> truckno = {2,3,4,5};
    unsigned int startVertex = 0;
    //CPPGraph::print(std::cout, graph)<<std::endl;


    std::cout<<"Algorithm name, graph size, truck no, time factor, execution time [ms]"<<std::endl;

    for(unsigned int j=0;j<graphSize.size();++j){

        graph.random(graphSize[j]);
        std::vector<unsigned int> v(graph.size());
        for(unsigned int i=0;i<graph.size();++i){
            v.at(i) = i;
        }
        //usuniecie wierzcholka startu z wektora wierzcholkow docelowych
        v.erase(v.begin()+startVertex);

        for(unsigned int a=0;a<algorithms.size();++a){
            Algorithm* algorithm = algorithms[a];

            algorithm->startVertex() = startVertex;
            algorithm->setDestinations(v); //ustawienie wszystkich pozostalych wierzcholkow jako docelowe

            for(unsigned int k=0;k<truckno.size();++k){
                algorithm->truckNo() = truckno[k];

                for(unsigned int i=0;i<timeFactor.size();++i){
                    algorithm->timeFactor() = timeFactor[i];


                    //std::cout<<"Starting "<<algorithm->name()<<std::endl;
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    algorithm->run();
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    double time = std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();


                    std::cout<<std::setw(30)<<algorithm->name()<<","<<" "<<graphSize[j]<<", "<<truckno[k]<<", "<<timeFactor[i]<<", "<<time<<std::endl;
                }
            }
        }
    }

    for(unsigned int i=0;i<algorithms.size();++i){
        delete algorithms[i];
    }

    return 0;
}

int main(int argc, char *argv[])
{
    return gui(argc, argv);

}
