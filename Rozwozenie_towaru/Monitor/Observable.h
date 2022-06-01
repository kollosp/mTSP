#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer.h"
#include <string>
#include <vector>

class Observable
{
    std::vector<Observer*> observers;

public:
    Observable();

    Observer* attach(Observer* o);
    Observer* detach(Observer* o);
    void notify(Observer::EventTypes eventNb = Observer::EVENT_ANY);
};

#endif // OBSERVABLE_H
