#include "clients.h"

Clients::Clients()
{

}

Clients::Clients(const std::vector<std::vector<std::string> > &data)
{
    fromVector(data);
}

const Client &Clients::at(unsigned int index) const
{
    return clients.at(index);
}
Client &Clients::at(unsigned int index)
{
    return clients.at(index);
}

unsigned int Clients::size() const
{
    return clients.size();
}

void Clients::fromVector(const std::vector<std::vector<std::string> > &data)
{
    this->clients = std::vector<Client>();
    for(const std::vector<std::string> &row : data) {
        Client c;
        c.index = stoi(row.at(0));
        c.firstName = row.at(1);
        c.lastName = row.at(2);
        this->clients.push_back(c);
    }
}
