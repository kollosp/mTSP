#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Vertex.h"
#include "Tree.h"

#include <QtDebug>

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include<bits/stdc++.h>
#include <functional>
#include <queue>
#include <algorithm>

/*
template <class T>
std::ostream& operator<<(std::ostream& str, const std::vector<T>& vect){

    for(unsigned int i=0;i<vect.size();++i){
        str<<vect.at(i);
        if(i!=vect.size()-1) str<<" ";
    }

    return str;
}*/


template <class T>
std::ostream& operator<<(std::ostream& str, const std::vector<std::vector<T> >& vect){

    for(unsigned int i=0;i<vect.size();++i){
        str<<i<<". "<<vect.at(i);
        if(i!=vect.size()-1) str<<std::endl;
    }

    return str;
}


template<class T>
class Graph
{
    /**
     * @brief name of the graph, it could be also used as path or sth.
     */
    std::string _name;
    std::string _path;

    /**
     * @brief map two dimentional array that contains all Edges.
     */
    std::vector<std::vector<Edge<T>*> > edges;

    /**
     * @brief bidirectional. Flag affected at edge function. If it is set edge function return same value for
     * edge(x1,x2) and edge(x2,x1). Value is loaded from edges[min(x1,x2][max(x1,x2)]. If the flag is not set then
     * edge(x1,x2) is loaded from edges[x1][x2], and the graph has one directional edges.
     * Weight of the edge is stored in the edges two dimentional array.
     */
    bool bidirectional;

    /**
     * @brief selfRelated. Flag allows to create self related vertex. It the flag is set to 1 then function edge(x1,x1) will return
     * real value stored in edges array otherwise it will throw an exception.
     */
    bool selfRelated;

    /**
     * @brief vertices A list of vertices. It is used only for drawing
     */
    std::vector<Vertex<T> > vertices;

public:

    Graph(const Graph &g){
        _name = g._name;
        _path = g._path;
        vertices = std::vector<Vertex<T> >();
        edges = std::vector<std::vector<Edge<T>*> >();

        //copy vertices
        for(unsigned int i=0;i<g.size();++i){
            pushbackVertex(g.vertex(i));
        }

        //copy edges
        for(unsigned int i=0;i<edges.size();++i){
            for(unsigned int j=0;j<edges[i].size();++j){
                edges[i][j] = new Edge<T>(*g.edges[i][j]);
            }
        }
    }

    Graph& operator=(const Graph& g){
        _name = g._name;
        _path = g._path;
        vertices = std::vector<Vertex<T> >();
        edges = std::vector<std::vector<Edge<T>*> >();

        //copy vertices
        for(unsigned int i=0;i<g.size();++i){
            pushbackVertex(g.vertex(i));
        }

        //copy edges
        for(unsigned int i=0;i<edges.size();++i){
            for(unsigned int j=0;j<edges[i].size();++j){
                edges[i][j] = new Edge<T>(*g.edges[i][j]);
            }
        }
        return *this;
    }

    void random(unsigned int n)
    {
        setSize(n);
        for(unsigned int i=0;i<n;++i){
            for(unsigned int j=i;j<n;++j){
                //wypelniamy tylko polowe grafu (mamy graf nieskierowany)
                if(i!=j){
                    if(rand()%3 == 0){
                        edges[j][i]->value() = 0;
                        edges[i][j]->value() = 0;
                    }else{
                        T val = (rand()%100)+1;
                        edges[j][i]->value() = val;
                        edges[i][j]->value() = val;
                    }
                }
            }
        }
        fillComplexPaths();
    }

    /**
     * @brief Graph default constructor. Sets Graph configuration
     * @param bidirectional
     * @param selfRelated
     */
    Graph(bool bidirectional = false, bool selfRelated = false):
        bidirectional(bidirectional), selfRelated(selfRelated){}


    ~Graph(){
        //std::cout<<"desctructor"<<std::endl;
        for(unsigned int i=0;i<edges.size();++i){
            for(unsigned int j=0;j<edges[i].size();++j){
                delete edges[i][j];
            }
        }
    }

    void clear(){
        for(unsigned int i=0;i<edges.size();++i){
            for(unsigned int j=0;j<edges[i].size();++j){
                delete edges[i][j];
            }
        }
    }

    void setSize (unsigned int vertices) noexcept {
        clear();

        this->vertices = std::vector<Vertex<T> >();
        edges = std::vector<std::vector<Edge<T>*> >();

        for(unsigned int i=0;i<vertices;++i){
            pushbackVertex(Vertex<T>());
        }
    }

    /**
     * @brief pushbackVertex function adds new vertex to vector and to edges list
     */
    void pushbackVertex(const Vertex<T>& v = Vertex<T>()) noexcept {


        //increate each vertex edge lengthGraph
        for(unsigned int i=0;i<size();++i){
            edges.at(i).push_back(new Edge<T>(T()));
        }

        //create new vertex edge list
        std::vector<Edge<T>*> vec;
        for(unsigned int i=0;i<size()+1;++i){
            vec.push_back(new Edge<T>(T()));
        }
        //add new vertex edge list to the edges vector
        edges.push_back(vec);
        vertices.push_back(v);
    }

    /**
     * @brief pushbackArtificialVertex function adds artificial vertex between vertices n1 and n2
     * @param n1
     * @param n2
     */
    void pushbackArtificialVertex(unsigned int n1, unsigned int n2) noexcept {
        Vertex<T> vertex;
        vertex.setArtificialFlag(true);


        Vertex<T> begin = vertices.at(n1);
        Vertex<T> end = vertices.at(n2);

        //direction vector
        float dx = end.x() - begin.x();
        float dy = end.y() - begin.y();

        //normal vector
        float ndx =      dx / 10;
        float ndy = -1 * dy / 10;

        //set vector position
        vertex.x() = begin.x() + dx / 2 + ndx;
        vertex.y() = begin.y() + dy / 2 + ndy;

        pushbackVertex(vertex);
        T edgeW = edge(n1, n2).directValue();
        unsigned int newVertex = size()-1;
        edge(newVertex, n2).value() = edgeW;
        edge(n1, newVertex).value() = edgeW;
    }

    /**
     * @brief removeVertice removes vertex at position position
     * @param position
     */
    void removeVertex(unsigned int position){
        vertices.erase(vertices.begin() + position);
        edges.erase(edges.begin() + position);
        for(unsigned int i=0;i<edges.size();++i){
            edges[i].erase(edges[i].begin() + position);
        }
    }

    /**
     * @brief edge
     * @param begin
     * @param end
     * @return
     */
    const Edge<T>& edge(unsigned int begin, unsigned int end) const {
        //const function disallow manipulate data so this condition is not necessary
        /*if(selfRelated == false && begin == end){
            throw(std::range_error("Forbidden relationship"));
        }*/

        if(bidirectional) {
            unsigned int b = std::min(begin, end);
            end = std::max(begin, end);
            begin = b;
        }

        return *edges.at(begin).at(end);
    }

    Edge<T>& edge(unsigned int begin, unsigned int end){

        if(selfRelated == false && begin == end){
            std::stringstream ss;
            ss<<"Forbidden relationship (" << begin << ", "<< end << ")";
            throw(std::range_error(ss.str()));
        }

        if(bidirectional) {
            unsigned int b = std::min(begin, end);
            end = std::max(begin, end);
            begin = b;
        }

        return *edges.at(begin).at(end);
    }

    std::vector<unsigned int> edgeRoute(unsigned int begin, unsigned int end) const{
        /*if(bidirectional) {
            //if djiksta was used then paths are set correctly in paths from grater to lower verterx
            if(begin > end){
                //std::cout<<"bidirectional begin > end "<<begin <<" " << end<<" br: ";
                std::vector<unsigned int> r = edges.at(begin).at(end)->getRoute();
                //std::cout<<r<<" reverse: ";
                std::reverse(r.begin(),r.end());
                //std::cout<<r<<std::endl;
                return r;
            }else{
                std::vector<unsigned int> r = edges.at(begin).at(end)->getRoute();
                std::reverse(r.begin(),r.end());
                //std::cout<<r<<std::endl;
                return r;
            }
        }
        else{
            return edges.at(begin).at(end)->getRoute();
        }*/

        return edges.at(begin).at(end)->getPlainRoute();
    }

    /**
     * @brief vertex function returns vertex at position index in the vector
     * @param index
     * @return
     */
    Vertex<T>& vertex(unsigned int index) {
        return vertices.at(index);
    }

    const Vertex<T>& vertex(unsigned int index) const {
        return vertices.at(index);
    }


    /**
     * @brief size function returns size of the graph
     * @return
     */
    unsigned int size() const noexcept{
        return vertices.size();
    }

    /**
     * @brief bidirectionalFlag function returns true if the graph has bidirectional edges
     * @return bidirectional flag
     */
    bool& bidirectionalFlag () noexcept {
        return bidirectional;
    }

    /**
     * @brief bidirectionalFlag function returns true if the graph has bidirectional edges
     * @return bidirectional flag
     */
    const bool& bidirectionalFlag () const noexcept {
        return bidirectional;
    }

    /**
     * @brief selfRelationFlag function returns true if the graph could has self related vertices.
     * @return selfRelated flag
     */
    bool& selfRelationFlag () noexcept {
        return selfRelated;
    }

    /**
     * @brief selfRelationFlag function returns true if the graph could has self related vertices.
     * @return selfRelated flag
     */
    const bool& selfRelationFlag () const noexcept {
        return selfRelated;
    }

    std::string& name() noexcept {
        return _name;
    }

    const std::string& name() const noexcept {
        return _name;
    }

    std::string& path() noexcept {
        return _path;
    }

    const std::string& path() const noexcept {
        return _path;
    }

    void writeToFile(const std::string& path) const noexcept {
        //open file
        std::ofstream stream;
        stream.open(path);
        //write graph to file
        stream<<(*this);
        //close file
        stream.close();
    }

    void readFromFile(const std::string& path) {
        //open file
        std::ifstream stream;
        stream.open(path);

        //guard if file does not exists skip reading
        if(!stream.fail()) {
            //read graph from file
            stream>>(*this);
        }

        //close file
        stream.close();
        _path = path;
        this->fillComplexPaths();
    }

    /**
     * @brief toString Function returns a string representation of a graph.
     * @return graph as string
     */
    std::string toString() const noexcept {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    /**
     * @brief edges count edges
     * @return
     */
    unsigned int edgesCount() const {
        unsigned int ret = 0;
        for(unsigned int i=0;i<this->size();++i){
            for(unsigned int k=0;k<this->size();++k){

                if(edges[i][k]->isDirect() > 0){
                    if(selfRelationFlag() && i==k){
                        ret ++;
                    }else if(k != i){
                        ret ++;
                    }
                }

            }
        }

        if(bidirectionalFlag()) ret /= 2;

        return ret;
    }

    /**
     * @brief shortestEdge
     * @return
     */
    T shortestEdge() const {
        T min = T();
        bool undef = true;
        for(unsigned int i=0;i<size();++i){
            for(unsigned int j=0;j<size();++j){
                if(edges[i][j]->isDirect()){
                    if(undef){
                        min = edges[i][j]->value();
                        undef = false;
                    } else if(edges[i][j]->value() < min){
                        min = edges[i][j]->value();
                    }
                }
            }
        }
        return min;
    }

    /**
     * @brief longestEdge
     * @return
     */
    T longestEdge() const {
        T max = T();
        bool undef = true;
        for(unsigned int i=0;i<size();++i){
            for(unsigned int j=0;j<size();++j){
                if(edges[i][j]->isDirect()){
                    T buf = edge(i,j).directValue();
                    if(undef){
                        max = buf;
                        undef = false;
                    } else if(buf > max){
                        max = buf;
                    }
                }
            }
        }
        return max;
    }

    const std::vector<unsigned int> listOddVertices() const noexcept {
        std::vector<unsigned int> oddV;
        for(unsigned int i=0;i<size();++i){
            int count = 0;
            for(unsigned int j=0;j<size();++j){
                if(edge(i,j).directValue() > 0){
                    count++;
                }
            }
            if(count % 2 == 1){
                oddV.push_back(i);
            }
        }
        return oddV;
    }

    std::vector<unsigned int> listEvenVertices() const noexcept {
        std::vector<unsigned int> oddV;
        for(unsigned int i=0;i<size();++i){
            int count = 0;
            for(unsigned int j=0;j<size();++j){
                if(edge(i,j).directValue() > 0){
                    count++;
                }
            }
            if(count % 2 == 0){
                oddV.push_back(i);
            }
        }
        return oddV;
    }

    /**
     * @brief weightCenter function calculate the center of mass of the graph
     * @return
     */
    Vertex<T> weightCenter() const noexcept {
        Vertex<T> ret;

        if(size() == 0)
            return ret;

        for(unsigned int i=0;i<size();++i){
            ret.x()+=vertices.at(i).x();
            ret.y()+=vertices.at(i).y();
        }

        ret.x() /= size();
        ret.y() /= size();
        return ret;
    }

    Vertex<T> leftTop() const noexcept {
        Vertex<T> ret;

        if(size() == 0)
            return ret;

        ret.x() = vertices.at(0).x();
        ret.y() = vertices.at(0).y();

        for(unsigned int i=1;i<size();++i){
            if(vertices.at(i).x() < ret.x()) ret.x() = vertices.at(i).x();
            if(vertices.at(i).y() < ret.y()) ret.y() = vertices.at(i).y();
        }

        return ret;
    }

    Vertex<T> rightBottom() const noexcept {
        Vertex<T> ret;

        if(size() == 0)
            return ret;

        ret.x() = vertices.at(0).x();
        ret.y() = vertices.at(0).y();

        for(unsigned int i=1;i<size();++i){
            if(vertices.at(i).x() > ret.x()) ret.x() = vertices.at(i).x();
            if(vertices.at(i).y() > ret.y()) ret.y() = vertices.at(i).y();
        }

        return ret;
    }

    std::vector<unsigned int> findNeighbours(unsigned int vertex) const {
        std::vector<unsigned int> ret;
        for(unsigned int i=0;i<size();++i){
            T edgeW = edge(vertex, i).directValue();
            if(edgeW > 0){
                ret.push_back(i);
            }
        }

        return ret;
    }

    bool findAllPossiblePaths(unsigned int begin, unsigned int end, Tree<unsigned int>& ret) const {
        ret.value() = begin;

        //std::cout<<begin<<" end: "<<end<<" path: "<<ret.paths()<<std::endl;

        if(begin == end) return true;

        std::vector<unsigned int> neighbours = findNeighbours(begin);
        bool hasNewNeighbours = false;

        for(unsigned int i=0;i<neighbours.size();++i){
            if(ret.existsInUpTree(neighbours[i]) == false){

                Tree<unsigned int>* node= new Tree<unsigned int>();
                ret.pushChild(node);

                //std::cout<<"next step:"<<neighbours[i]<<" end: "<<end<<" path: "<<ret.root().paths()<<std::endl;
                bool expanded = findAllPossiblePaths(neighbours[i], end, *node);

                if(expanded == false) {
                    delete node;
                }else{
                    hasNewNeighbours = true;
                }
            }
        }

        return hasNewNeighbours;
    }

    /**
     * @brief findShortestPathBetweenVertices Find the shortest possible path connecting the given vertices
     * @param begin
     * @param end
     * @return
     */
    std::vector<unsigned int> findShortestPathBetweenVertices(unsigned int begin, unsigned int end, T*shortestPathVal = nullptr) const {
        std::vector<unsigned int> ret;
        if(begin == end) return ret;

        Tree<unsigned int> tree;
        findAllPossiblePaths(begin, end, tree);
        std::vector<std::vector<unsigned int> > paths = tree.paths();

        std::cout<<paths<<std::endl;

        unsigned int shortestPathIndex = 0;
        T shortestPathValue = std::numeric_limits<T>::max();
        for(unsigned int i=0;i<paths.size();++i){
            T currentPathValue = computePathWeight(paths.at(i));

            if(currentPathValue < shortestPathValue){
                shortestPathValue = currentPathValue;
                shortestPathIndex = i;
            }
        }

        if(shortestPathVal){
            *shortestPathVal = shortestPathValue;
        }

        return paths.at(shortestPathIndex);
    }

    void createArtificialPath(const std::vector<unsigned int>& path){
        for(unsigned int i=0;i<path.size()-1;++i){
            pushbackArtificialVertex(path.at(i), path.at(i+1));
        }
    }

    /**
     * @brief computePathWeight Compute weight of path defined as list of vertices
     * @param vertices
     * @return
     */
    T computePathWeight(const std::vector<unsigned int> & vertices) const {
        T sum = T();
        for(unsigned int i=0;i<vertices.size()-1;++i){
            sum += edge(vertices.at(i), vertices.at(i+1)).directValue();
        }

        return sum;
    }

    /**
     * @brief computeShortestComputePath function calculate TSP length. Vertices in vertices vector are allowed to not be neighbours. If so,
     * then algorithm will use findShortestPathBetweenVertices function.
     * @param vertices
     */
    std::vector<unsigned int>computeShortestComplexPath(unsigned int begin, std::vector<unsigned int> vertices, T*shortestPathVal = nullptr) const {
        vertices.insert(vertices.begin(), begin);
        vertices.push_back(begin);

        T shortestPathValue = T();
        std::vector<unsigned int> ret;
        ret.push_back(begin);
        for(unsigned int i=0;i<vertices.size()-1;++i){
            Edge<T> e =edge(vertices.at(i), vertices.at(i+1));
            T spv = e.value();

            std::vector<unsigned int> route = edgeRoute(vertices.at(i), vertices.at(i+1));
            for(unsigned int j=0;j<route.size();++j){
                ret.push_back(route.at(j));
            }
            ret.push_back(vertices.at(i+1));


            shortestPathValue += spv;
        }

        if(shortestPathVal){
            *shortestPathVal = shortestPathValue;
        }
        //std::cout<<std::endl;

        return ret;
    }

    void fillComplexPaths(){
        for(unsigned int i=0;i<edges.size();++i){
            djikstra(i);
        }
    }

    void djikstra(unsigned int begin){

        std::priority_queue< std::pair<T, unsigned int>, std::vector<std::pair<T, unsigned int>> , std::greater<std::pair<T, unsigned int>>> pq;
        std::vector<T> dist(edges.size(), std::numeric_limits<T>::max());

        pq.push(std::make_pair(T(), begin));
        dist.at(begin) = 0;

        while (!pq.empty()){
            // The first vertex in pair is the minimum distance
            // vertex, extract it from priority queue.
            // vertex label is stored in second of pair (it
            // has to be done this way to keep the vertices
            // sorted distance (distance must be first item
            // in pair)
            unsigned int u = pq.top().second;
            pq.pop();

            std::vector<unsigned int> uRoute = {};
            if(begin != u)
                uRoute = edges.at(begin).at(u)->getPlainRoute();

            std::vector<unsigned int> neigbours = findNeighbours(u);

            for(unsigned int i=0;i<neigbours.size();++i){
                Edge<T>& e = edge(u, neigbours.at(i));

                // If there is shorter path to neigbour through u.
                if(dist[neigbours.at(i)] > dist[u] + e.directValue()){
                    dist[neigbours.at(i)] = dist[u] + e.directValue();

                    //direct path
                    if(begin != u){
                        //set new route. Route by u
                        edges.at(begin).at(neigbours.at(i))->setRoute(uRoute);
                        edges.at(begin).at(neigbours.at(i))->pushRouteVertex(u);
                    }

                    pq.push(std::make_pair(dist[neigbours.at(i)], neigbours.at(i)));
                    //std::cout<<"shorter path "<<begin<<" -> "<<neigbours.at(i)<<" via "<<u<<" fount. New route"<<edges.at(begin).at(neigbours.at(i))->getPlainRoute()<<std::endl;
                }
            }
        }

        //set in graph
        for(unsigned int i=0;i<edges.size();++i){
            if(begin != i){
                Edge<T>& e =edge(begin, i);
                if(e.directValue() == 0 || e.isDirect() == false){
                    e.setDirectFlag(false);
                    e.value() = dist[i];
                    //std::cout<<begin<<" -> "<<i<<" = "<<dist[i]<<" | "<<e.getRoute()<<std::endl;
                }
            }
        }
    }

    /**
     * @brief edgesWeightSum calculates total sum of all edges
     * @return
     */
    T edgesWeightSum() const {
        T sum = T();
        for(unsigned int i=0;i<this->size();++i){

            //skip if i is artificial, avoid adding artificial edges twice
            if(vertices.at(i).artificialFlag() == false) {

                unsigned int k=0;
                if(bidirectionalFlag() == true){
                    k=i;
                }

                for(;k<this->size();++k){
                    if(vertices.at(k).artificialFlag()){
                        continue;
                    }

                    T edge = edges[i][k]->value();
                    if(edge > 0){
                        if((selfRelationFlag() && i==k) || k != i){
                            sum += edge;
                        }
                    }
                }
            }
            //artificial processing
            else{
                //artificla has always two edges, so use only the first one
                unsigned int k=0;
                T edge = 0;
                while(k < this->size() && edge == 0){
                    edge = ((const Graph<T>)(*this)).edge(i,k).directValue();
                    k++;
                }
                sum += edge;
            }
        }
        return sum;
    }


    static
    std::ostream& print(std::ostream& str, const Graph<T>& graph){
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
                str<<" "<<std::setw(4)<<graph.edge(i,j).directValue();
                if(graph.edge(i,j).isDirect() == false)
                    str<<graph.edge(i,j).getRoute();
            }
            str<<std::endl;
        }

        //return stream for pipelining
        return str;
    }

    /**
     * Friend to allow skipping flag checking when get access to the edge
     */
    template <class TT> friend
    std::istream& operator>>(std::istream& str, Graph<TT>& graph);
};

template <class T>
std::ostream& operator<<(std::ostream& str, const Graph<T>& graph){
    //print configuration
    if(graph.name() == ""){
        str << "###" << std::endl;
    }else{
        str<<graph.name()<<std::endl;
    }
    str<<graph.size()<< " " << graph.bidirectionalFlag() <<" " <<graph.selfRelationFlag()<<std::endl;

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
            str<<" "<<std::setw(4)<<graph.edge(i,j).directValue();
        }
        str<<std::endl;
    }

    //return stream for pipelining
    return str;
}

template <class T>
std::istream& operator>>(std::istream& str, Graph<T>& graph){

    //load config size and flags
    str>>graph.name();
    if(graph.name() == "###") graph.name() = "";
    unsigned int size;
    str>>size;
    graph.setSize(size);
    str>>graph.bidirectionalFlag();
    str>>graph.selfRelationFlag();

    for(unsigned int i=0;i<graph.size();++i){
        str>>graph.vertex(i);
    }

    T buf;
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
            graph.edges[j][i]->value() = buf;
        }
    }


    return str;
}


#endif // GRAPH_H
