#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <iomanip>
#include <QDebug>

class Vertex
{
    /**
     * @brief value is vertex label. Used to determinate what the vertice is.
     */
    std::string _value;
    int xPos;
    int yPos;

public:
    /**
     * @brief Vertex default constructor. Sets value 0
     */
    Vertex() : _value(""), xPos(0), yPos(0) {}

    /**
     * @brief Vertex contructor sets value as givien
     * @param value the label of the vertex
     */
    Vertex(const std::string& value);

    /**
     * @brief get Function returns value of the vertice.
     * @return
     */
    const std::string& value() const ;
    std::string& value() ;

};

inline std::ostream& operator<<(std::ostream& str, const Vertex& v){
    str<<v.value() << " ";
    return str;
}
inline std::istream& operator>>(std::istream& str, Vertex& v){
    str>>v.value();
    return str;
}

#endif // VERTEX_H
