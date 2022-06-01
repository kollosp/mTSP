#include <chrono>
#include "Algorithms/GeneticAlgorithm.h"
#include "Data/Data.h"

int main(int argc, char *argv[])
{

    Data address("../adresy.csv");
    std::cout<<address<<std::endl;
    std::cout<<"Lista adresatow przesylek"<<std::endl;

    //inicjalizacja grafu
    Graph graph;
    graph.random(20);
    std::cout<<"Ladowanie grafu..."<<std::endl;
    std::cout<<graph<<std::endl;
    std::cout<<"Zaladowanio."<<std::endl;

    //inicjalizacja algorytmu przetwarzania
    GeneticAlgorithm algorithm(graph);

    algorithm.timeFactor() = 1; //wartosc z przedzialu <0..1>
    algorithm.startVertex() = 0; //wierzhcolek startu dla kazdej ciezarowki
    algorithm.truckNo() = 3; //liczba ciezarowek brana pod uwage

    std::vector<unsigned int> v(graph.size());
    for(unsigned int i=0;i<graph.size();++i){
        v.at(i) = i;
    }
    //usuniecie wierzcholka startu z wektora wierzcholkow docelowych
    v.erase(v.begin()+algorithm.startVertex());

    algorithm.setDestinations(v); //ustawienie wszystkich pozostalych wierzcholkow jako docelowe

    std::cout<<"Uruchamiam algorytm..."<<std::endl;
    std::cout<<"Wierzcholek poczatkowy: "<<algorithm.startVertex()<<std::endl;
    std::cout<<"L. Ciezarowek: "<<algorithm.truckNo()<<std::endl;
    std::cout<<"Punkty docelowe: "<<Data::formatAsAddress(address.at(algorithm.getDestinations()))<<std::endl;
    std::cout<<"Wsp. wagi czasu: "<<algorithm.timeFactor()<<std::endl;
    std::cout<<"======================="<<std::endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::vector<std::vector<unsigned int> > solution = algorithm.run();
    std::cout<<"==== Trasy ===="<<std::endl;
    for(unsigned int truckNo=0;truckNo<solution.size();++truckNo){
        std::cout<<"Trasa dla ciezarowki nr "<<truckNo+1<<":"<<std::endl;
        print(std::cout, Data::formatAsAddress(address.at(solution[truckNo])), " -> ");
        std::cout<<std::endl;
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Obliczono w czasie = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << " ms" << std::endl;

    return 0;
}
