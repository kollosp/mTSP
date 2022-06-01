#include "VectorInteger.h"

VectorInteger::VectorInteger(unsigned int size, unsigned int system) :
    c_size(size), c_system(system)
{
    c_data = std::vector<unsigned char>(size);
    //zeros + ssystem
    c_digitsCount = std::vector<unsigned int>(c_system);

    //only zeros in number
    c_digitsCount.at(0) = c_data.size();
}

unsigned char VectorInteger::at(unsigned int pos) const
{
    return c_data.at(pos);
}
unsigned char& VectorInteger::at(unsigned int pos)
{
    return c_data.at(pos);
}

unsigned int VectorInteger::size() const
{
    return c_data.size();
}

unsigned int VectorInteger::system() const
{
    return c_system;
}

void VectorInteger::overflow(bool of)
{
    this->isOverflow = of;
}

bool VectorInteger::overflow() const
{
    return isOverflow;
}

bool VectorInteger::hasAllDigitsUsed() const
{
    for(unsigned int i=0;i<c_digitsCount.size();++i){
        if(c_digitsCount.at(i) == 0)
            return false;
    }
    return true;
}

VectorInteger &VectorInteger::operator++()
{
    unsigned char c = 1;
    for(unsigned int i=0;i<c_data.size() && c!= 0;++i){

        c_digitsCount[c_data[i]]--;

        c_data[i] += c;

        c = 0;
        if(c_data[i] >= c_system){
            c_data[i] -= c_system;
            c = 1;
        }

        c_digitsCount[c_data[i]]++;
    }

    //set overflow
    if(c == 1) isOverflow = true;

    return *this;
}

unsigned int VectorInteger::getDigists(unsigned int pos) const
{
    return c_digitsCount.at(pos);
}

bool VectorInteger::isIncreasing() const
{
    for(unsigned int i=1;i<c_digitsCount.size();++i){
        if(c_digitsCount[i-1] < c_digitsCount[i]){
            return false;
        }
    }

    /*for(unsigned int i=1;i<c_data.size();++i){
        if(c_data[i-1] < c_data[i]){
            return false;
        }
    }*/

    return true;
}

bool VectorInteger::hasEqualCountOfDigites(int accurancy) const
{
    float avg = 0;
    for(unsigned int i=0;i<c_digitsCount.size();++i){
        avg += c_digitsCount[i];
    }
    avg /= c_digitsCount.size();

    for(unsigned int i=0;i<c_digitsCount.size();++i){
        if(!(c_digitsCount[i] > avg - accurancy && c_digitsCount[i] < avg + accurancy)){
            return false;
        }
    }
    return true;
}



std::vector<unsigned int> VectorInteger::split(const std::vector<unsigned int> &vec, unsigned int digit) const
{
    if(vec.size() != c_data.size()){
        throw std::range_error("Vector vec.size() and this.size() have to be the same");
    }

    std::vector<unsigned int> ret;
    for(unsigned int i=0;i<size();++i){
        if(c_data[i] == digit)
            ret.push_back(vec[i]);
    }

    return ret;
}

std::ostream &operator<<(std::ostream &str, const VectorInteger &integer)
{
    str<<(char)(integer.system()+'0')<<"x";

    //because of overflow on unsigned int ((unsigned int)0-1 == MAX_INT)
    for(unsigned int i=integer.size()-1;i < integer.size();--i){

        if(integer.at(i) + '0' <= '9'){
            str<<"("<<(char)(integer.at(i) + '0')<<")";
        }else{
            str<<"("<<(char)(integer.at(i) + 'A' - 10)<<")";
        }
    }
    str<<".";

    for(unsigned int i=0; i < integer.system();++i){
        str<<"("<<integer.getDigists(i)<<")";
    }

    str<<".";

    if(integer.isIncreasing()){
        str<<"inc";
    }else{
        str<<"dec";
    }

    str<<".";

    if(integer.hasAllDigitsUsed()){
        str<<"usedAll";
    }else{
        str<<"usedSome";
    }

    return str;
}
