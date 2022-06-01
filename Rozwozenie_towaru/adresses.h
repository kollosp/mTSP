#ifndef ADRESSES_H
#define ADRESSES_H

#include "Operators.h"
#include <iostream>
#include <vector>
#include <string>

class Adress {
public:
    unsigned int index;
    std::string city;
    std::string street;
    unsigned int streetNo;
    unsigned int flatNo = 0;
};

class Adresses
{
    std::vector<Adress> adresses;


    std::vector<std::vector<float> > distance;
public:
    Adresses();
    Adresses(const std::vector<std::vector<std::string>> &data);
    const Adress& at(unsigned int index) const;
    Adress& at(unsigned int index) ;
    unsigned int size() const;
    void fromVector(const std::vector<std::vector<std::string>> &data);
    void randomDistance();
    const std::vector<std::vector<float> >& distanceMatrix() const;

};


inline std::ostream& operator << (std::ostream& os, const Adress& obj)
{
    os << obj.index <<". "<<obj.city <<" "<< obj.street <<" " << obj.streetNo;

    if(obj.flatNo > 0){
        os<<" m. "<<obj.flatNo;
    }

    return os;
}

inline std::ostream& operator << (std::ostream& os, const Adresses& objs)
{
    for(unsigned int i=0;i<objs.size();++i){
        os << objs.at(i) <<std::endl;
    }
    return os;
}



#endif // ADRESSES_H
