#ifndef CLIENTS_H
#define CLIENTS_H

#include "Operators.h"

class Client{
public:
    int index;
    std::string firstName;
    std::string lastName;
};

class Clients
{
    std::vector<Client> clients;

public:
    Clients();
    Clients(const std::vector<std::vector<std::string>> &data);
    const Client& at(unsigned int index) const;
    Client& at(unsigned int index) ;
    unsigned int size() const;
    void fromVector(const std::vector<std::vector<std::string>> &data);
};

inline std::ostream& operator << (std::ostream& os, const Client& client)
{
    os << client.index<<". "<<client.firstName <<" "<< client.lastName;
    return os;
}

inline std::ostream& operator << (std::ostream& os, const Clients& clients)
{
    for(unsigned int i=0;i<clients.size();++i){
        os << clients.at(i) <<std::endl;
    }
    return os;
}




#endif // CLIENTS_H
