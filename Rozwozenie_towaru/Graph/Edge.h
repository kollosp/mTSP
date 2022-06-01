#ifndef EDGE_H
#define EDGE_H

#include "../Operators.h"
#include <vector>
#include <sstream>
#include "Vertex.h"

template<class T>
class Edge
{
    T _value;
    std::vector<unsigned int> route;
    bool direct = true;
public:
    Edge() {
        route = std::vector<unsigned int>(0);
    }
    Edge(const T& val) : _value(val) {}
    T& value() noexcept {return _value;}
    const T& value() const noexcept {return _value;}

    T directValue() const noexcept {
        if(isDirect() || direct){
            return _value;
        }
        else{
            return T();
        }
    }

    void pushRouteVertex(unsigned int v){
        route.push_back(v);
    }

    /**
     * @brief isDirect function checks if edge is direct from source to destination. If not hten route vector contains some control points
     * @return
     */
    bool isDirect() const noexcept {return direct;}
    /**
     * @brief getPath return path - all vertices which build path from source to destination
     * @return
     */
    std::vector<unsigned int> getRoute () const noexcept {
        if(isDirect())
            return std::vector<unsigned int>();
        return route;
    }

    /**
     * @brief getPath return path - all vertices which build path from source to destination
     * @return
     */
    std::vector<unsigned int> getPlainRoute () const noexcept {
        return route;
    }

    void setDirectFlag(bool d) noexcept {direct = d; }
    void setRoute(const std::vector<unsigned int> &newRoute) noexcept { route = newRoute; }

    std::string toString() const{
        std::stringstream ss;
        ss << _value << "."<<isDirect();
        if(isDirect()){
            return ss.str();
        }else{
            ss<<" : ";
            ss<<route;
            return ss.str();
        }
    }

    void fromString(const std::string& str){
        if(isDirect()){
            std::stringstream ss;
            ss << str;
            T value;
            ss >> value;
            _value = value;
        }
    }
};


template <class T>
std::ostream& operator<<(std::ostream& str, const Edge<T>& edge){
    str<<edge.toString();

    return str;
}


#endif // EDGE_H
