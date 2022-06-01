#include "Data.h"

Data::Data(const std::string &path)
{
    readFromFile(path);
}

Data::Data()
{

}

void Data::readFromFile(const std::string &path)
{
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
}

void Data::writeToFile(const std::string &path)
{
    //open file
    std::ofstream stream;
    stream.open(path);
    //write graph to file
    stream<<(*this);
    //close file
    stream.close();
}

unsigned int Data::size() const
{
    return c_data.size();
}

std::vector<std::string> Data::at(const std::vector<unsigned int>& ii) const
{
    std::vector<std::string> ret(ii.size());
    for(unsigned int i=0;i<ii.size();++i){
        ret[i] = at(ii[i]);
    }
    return ret;
}

std::string Data::at(unsigned int i) const
{
    return c_data.at(i);
}

std::string Data::toString() const  {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
}

const std::vector<std::string> &Data::data() const
{
    return c_data;
}

std::vector<std::string> &Data::data()
{
    return c_data;
}

std::vector<std::string> Data::formatAsAddress(const std::vector<std::string> &data)
{
    std::vector<std::string> ret (data.size());

    for(unsigned int i=0;i<data.size();++i){
        std::vector<std::string> ss = stdstringsplit(data[i], ',');
        ret[i] = ss.at(1) + " ul. " + ss.at(2) + " " + ss.at(3);
    }

    return ret;
}

std::vector<std::string> Data::formatAsCustomer(const std::vector<std::string> &data)
{
    std::vector<std::string> ret (data.size());

    for(unsigned int i=0;i<data.size();++i){
        std::vector<std::string> ss = stdstringsplit(data[i], ',');
        ret[i] = ss.at(1) + " " + ss.at(2);
    }

    return ret;
}
