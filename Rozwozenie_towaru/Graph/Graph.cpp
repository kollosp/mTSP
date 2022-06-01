#include "Graph.h"

void Graph::setSize(unsigned int vertices)  {
    this->vertices = std::vector<Vertex>();
    edges = std::vector<std::vector<double> >();

    for(unsigned int i=0;i<vertices;++i){
        pushbackVertex(Vertex());
    }
}

void Graph::pushbackVertex(const Vertex &v)  {


    //increate each vertex edge lengthGraph
    for(unsigned int i=0;i<size();++i){
        edges.at(i).push_back(0);
    }

    //create new vertex edge list
    std::vector<double> vec;
    for(unsigned int i=0;i<size()+1;++i){
        vec.push_back(0);
    }
    //add new vertex edge list to the edges vector
    edges.push_back(vec);
    vertices.push_back(v);
}

const double &Graph::edge(unsigned int begin, unsigned int end) const {

    unsigned int b = std::min(begin, end);
    end = std::max(begin, end);
    begin = b;

    return edges.at(begin).at(end);
}

double &Graph::edge(unsigned int begin, unsigned int end){

    unsigned int b = std::min(begin, end);
    end = std::max(begin, end);
    begin = b;
    return edges.at(begin).at(end);
}

Vertex &Graph::vertex(unsigned int index) {
    return vertices.at(index);
}

const Vertex &Graph::vertex(unsigned int index) const {
    return vertices.at(index);
}

void Graph::random(unsigned int n)
{
    setSize(n);
    for(unsigned int i=0;i<n;++i){
        for(unsigned int j=i;j<n;++j){
            //wypelniamy tylko polowe grafu (mamy graf nieskierowany)
            if(i!=j){
                edges.at(i).at(j) = (rand()%100)+1;
            }
        }
    }
}

unsigned int Graph::size() const {
    return vertices.size();
}

std::string &Graph::name()  {
    return _name;
}

const std::string &Graph::name() const  {
    return _name;
}

std::string &Graph::path()  {
    return _path;
}

const std::string &Graph::path() const  {
    return _path;
}

void Graph::writeToFile(const std::string &path) const  {
    //open file
    std::ofstream stream;
    stream.open(path);
    //write graph to file
    stream<<(*this);
    //close file
    stream.close();
}

void Graph::readFromFile(const std::string &path) {
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
}

std::string Graph::toString() const  {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
}

double Graph::computeShortestComplexPath(unsigned int begin, std::vector<unsigned int> vertices, double *shortestPathVal) const {
    vertices.insert(vertices.begin(), begin);
    vertices.push_back(begin);

    double value= 0;

    for(unsigned int i=0;i<vertices.size()-1;++i){
        value += edge(vertices.at(i), vertices.at(i+1));
    }

    if(shortestPathVal){
        *shortestPathVal = value;
    }
    //std::cout<<std::endl;

    return value;
}
