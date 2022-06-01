#include "adresses.h"

Adresses::Adresses()
{

}

Adresses::Adresses(const std::vector<std::vector<std::string> > &data)
{
    fromVector(data);
}

const Adress &Adresses::at(unsigned int index) const
{
    return adresses.at(index);
}

Adress &Adresses::at(unsigned int index)
{
    return adresses.at(index);
}

unsigned int Adresses::size() const
{
    return adresses.size();
}

void Adresses::fromVector(const std::vector<std::vector<std::string> > &data)
{
    this->adresses = std::vector<Adress>();
    for(const std::vector<std::string> &row : data) {
        Adress a;
        a.index = stoi(row.at(0));
        a.city = row.at(1);
        a.street = row.at(2);
        a.streetNo = stoi(row.at(3));
        std::cout<<row<<", "<<row.size() <<std::endl;

        if(row.size() > 4){
            a.flatNo = stoi(row.at(4));
        }

        this->adresses.push_back(a);
    }

    randomDistance();
}

void Adresses::randomDistance()
{
    distance = std::vector<std::vector<float> > ();
    for(unsigned int i=0;i<adresses.size();++i){
        std::vector<float> r(adresses.size());
        distance.push_back(r);
    }

    for(unsigned int i=0;i<adresses.size();++i){
        distance.at(i).at(i) = 0;
        for(unsigned int j=0;j<i;++j){
            distance.at(i).at(j) = 100;
            distance.at(j).at(i) = 100;
        }
    }
}

const std::vector<std::vector<float> > &Adresses::distanceMatrix() const
{
    return distance;
}
