#ifndef GRAPHTYPES_H
#define GRAPHTYPES_H

#include "Graph.h"

typedef Graph<unsigned int> GraphInt;
typedef Graph<float> GraphFloat;
typedef Graph<double> GraphDouble;

typedef Vertex<unsigned int> VertexInt;
typedef Vertex<float> VertexFloat;
typedef Vertex<double> VertexDouble;


typedef Edge<unsigned int> EdgeInt;
typedef Edge<float> EdgeFloat;
typedef Edge<double> EdgeDouble;

typedef GraphInt CPPGraph;
typedef unsigned int CPPWeight;
typedef VertexInt CPPVertex;
typedef EdgeInt CPPEdge;


#endif // GRAPHTYPES_H
