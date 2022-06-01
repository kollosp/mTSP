#ifndef CSVREADER_H
#define CSVREADER_H

#include "Operators.h"

#include <string>
#include <vector>
#include <fstream>

#include <QFile>
#include <QStringList>
#include <QDebug>

class CSVReader
{
public:
    static std::vector<std::vector<std::string>> load(const std::string& path);
};

#endif // CSVREADER_H
