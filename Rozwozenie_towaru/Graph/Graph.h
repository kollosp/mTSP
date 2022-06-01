#ifndef GRAPH_H
#define GRAPH_H

#include "Operators.h"
#include "Vertex.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <functional>
#include <queue>
#include <algorithm>

template <class T>
std::ostream& operator<<(std::ostream& str, const std::vector<std::vector<T> >& vect){

    for(unsigned int i=0;i<vect.size();++i){
        str<<i<<". "<<vect.at(i);
        if(i!=vect.size()-1) str<<std::endl;
    }

    return str;
}


class Graph
{
    //nazwa grafu z pliku
    std::string _name;
    std::string _path;

    //lista krawedzi
    std::vector<std::vector<double>> edges;
    //lista wierzcholkow
    std::vector<Vertex> vertices;


    Graph(const Graph &g);
    Graph& operator=(const Graph& g);
public:

    /**
     * @brief Graph default constructor. Sets Graph configuration
     * @param bidirectional
     * @param selfRelated
     */
    Graph(){}
    ~Graph(){}

    void setSize (unsigned int vertices);

    /**
     * @brief pushbackVertex function adds new vertex to vector and to edges list
     */
    void pushbackVertex(const Vertex& v = Vertex());

    /**
     * @brief edge
     * @param begin
     * @param end
     * @return
     */
    const double& edge(unsigned int begin, unsigned int end) const;

    double& edge(unsigned int begin, unsigned int end);

    /**
     * @brief vertex function returns vertex at position index in the vector
     * @param index
     * @return
     */
    Vertex &vertex(unsigned int index);

    const Vertex& vertex(unsigned int index) const;


    void random(unsigned int n);


    /**
     * @brief size function returns size of the graph
     * @return
     */
    unsigned int size() const;

    std::string& name();

    const std::string& name() const;

    std::string& path();

    const std::string& path() const;

    void writeToFile(const std::string& path) const ;

    void readFromFile(const std::string& path);

    /**
     * @brief toString Function returns a string representation of a graph.
     * @return graph as string
     */
    std::string toString() const ;

    /**
     * @brief computeShortestComputePath function calculate TSP length. Vertices in vertices vector are allowed to not be neighbours. If so,
     * then algorithm will use findShortestPathBetweenVertices function.
     * @param vertices
     */
    double computeShortestComplexPath(unsigned int begin, std::vector<unsigned int> vertices, double*shortestPathVal = nullptr) const;


    /**
     * Friend to allow skipping flag checking when get access to the edge
     */
    friend std::istream& operator>>(std::istream& str, Graph& graph);
};

inline std::ostream& operator<<(std::ostream& str, const Graph& graph){
    //print configuration
    if(graph.name() == ""){
        str << "###" << std::endl;
    }else{
        str<<graph.name()<<std::endl;
    }
    str<<graph.size()<< " " <<std::endl;

    for(unsigned int i=0;i<graph.size();++i){
        str<<graph.vertex(i)<< " ";
    }
    str<<std::endl;

    //headers
    str<<"    ";
    for(unsigned int i=0;i<graph.size();++i){
        str<<" " << std::setw(4) <<i;
    }
    str<<std::endl;

    //print graph
    for(unsigned int i=0;i<graph.size();++i){
        str<< std::setw(4) <<i;
        for(unsigned int j=0;j<graph.size();++j){
            str<<" "<<std::setw(4)<<graph.edge(i,j);
        }
        str<<std::endl;
    }

    //return stream for pipelining
    return str;
}

inline std::istream& operator>>(std::istream& str, Graph& graph){

    //load config size and flags
    str>>graph.name();
    if(graph.name() == "###") graph.name() = "";
    unsigned int size;
    str>>size;
    graph.setSize(size);

    for(unsigned int i=0;i<graph.size();++i){
        str>>graph.vertex(i);
    }

    double buf;
    //skip header
    for(unsigned int i=0;i<size;++i){
        str >> buf;
    }

    for(unsigned int i=0;i<size;++i){
        //skip vertex label
        str >> buf;
        //load vertex edges
        for(unsigned int j=0;j<size;++j){
            str >> buf;
            //this is available via friendship
            graph.edges[j][i] = buf;
        }
    }


    return str;
}


#endif // GRAPH_H
