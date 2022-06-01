#include "csvreader.h"


std::vector<std::vector<std::string> > CSVReader::load(const std::string &path){

    std::string line;
    std::ifstream file(path);
    std::vector<std::vector<std::string> > ret;
    if (file.is_open())
    {
        while (getline(file,line)){
            ret.push_back(stdstringsplit(line, ','));
        }
        file.close();
    }
    else {
        throw(std::runtime_error("Blad pliku"));
    }

    return ret;
}
