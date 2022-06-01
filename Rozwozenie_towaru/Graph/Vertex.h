#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <iomanip>
#include <QDebug>

template <class T>
class Vertex
{
    /**
     * @brief value is vertex label. Used to determinate what the vertice is.
     */
    T _value;
    int xPos;
    int yPos;

    /**
     * @brief isArtificial variable used to determinate if vertex has been originaly in the graph or was added by CPP algorytm
     */
    bool isArtificial;

public:
    /**
     * @brief Vertex default constructor. Sets value 0
     */
    Vertex() : _value(T()), isArtificial(false), xPos(0), yPos(0) {}

    /**
     * @brief Vertex contructor sets value as givien
     * @param value the label of the vertex
     */
    Vertex(const T& value) : _value(value), isArtificial(false), xPos(0), yPos(0) {}
    Vertex(const T& value, unsigned int x, unsigned int y) : _value(value), isArtificial(false), xPos(x), yPos(y) {}

    /**
     * @brief get Function returns value of the vertice.
     * @return
     */
    const T& value() const noexcept { return _value; }
    T& value() noexcept { return _value; }

    const int &x() const noexcept { return xPos; }
    int &x() noexcept { return xPos; }
    const int &y() const noexcept { return yPos; }
    int &y() noexcept { return yPos; }

    const bool& artificialFlag() const noexcept { return isArtificial; }
    bool& artificialFlag() noexcept { return isArtificial; }

    void setArtificialFlag(bool art){
        isArtificial = art;
    }
};

template <class T>
std::ostream& operator<<(std::ostream& str, const Vertex<T>& v){
    str<<v.value() << " " <<v.x() << " " << v.y() << " " << (int)v.artificialFlag();
    return str;
}

template <class T>
std::istream& operator>>(std::istream& str, Vertex<T>& v){
    int b;
    str>>v.value() >> v.x() >> v.y() >> b;
    v.artificialFlag() = (b > 0);
    return str;
}

#endif // VERTEX_H
