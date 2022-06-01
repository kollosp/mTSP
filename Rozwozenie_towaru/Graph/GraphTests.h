#ifndef GRAPHTESTS_H
#define GRAPHTESTS_H

#include "Graph.h"
#include <cmath>

class GraphTests
{
public:
    GraphTests();

    static void run();
    /**
     * @brief test1 Tests basic functions like creation, adding vertices and modifing edges
     */
    static void test1();

    /**
     * @brief test2 Tests more complex functionalitites like bidirectional and selfretation
     */
    static void test2();

    static void vertexTest();


    static void writeToFileTest();
    static void displayTest();

    template<class T>
    static void testEqualValue(const std::string& title, const T& value, const T& expected){
        if(value == expected)
            std::cout<<"[OK] "<<title<<" "<<value<<std::endl;
        else{
            std::cerr<<"[ERROR] "<<title<<std::endl;
            std::cerr<<"Expected value is: "<<expected<<", but got "<<value<<std::endl;
            std::cerr<<"Aborting... "<<title<<std::endl;
            std::abort();
        }
    }


    static void test5();

};

#endif // GRAPHTESTS_H
