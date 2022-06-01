#include "Vertex.h"

Vertex::Vertex(const std::string &value) : _value(value) {}

const std::string &Vertex::value() const  {
    return _value;
}

std::string &Vertex::value()  {
    return _value;
}
