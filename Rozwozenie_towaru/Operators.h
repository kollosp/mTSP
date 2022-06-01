#ifndef OPERATORS_H
#define OPERATORS_H

#include <ostream>
#include <vector>
#include <iomanip>

inline std::ostream& operator << (std::ostream& os, const std::vector<std::vector<float> >& v)
{
    os<<std::fixed;
    for(unsigned int i=0;i<v.size();++i){
        for(unsigned int j=0;j<v.at(i).size();++j){
            os<<std::setprecision(0)<<std::setw(5)<<v.at(i).at(j);
        }
        os<<std::endl;
    }
    return os;
}


template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
{
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}

inline std::vector<std::string> stdstringsplit(const std::string& s, char seperator)
{
    std::vector<std::string> output;
    std::string::size_type prev_pos = 0, pos = 0;

    while((pos = s.find(seperator, pos)) != std::string::npos)
    {
        std::string substring( s.substr(prev_pos, pos-prev_pos) );

        output.push_back(substring);

        prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos, pos-prev_pos)); // Last word

    return output;
}

#endif // OPERATORS_H
