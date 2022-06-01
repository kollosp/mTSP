#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer
{
public:
    enum EventTypes {
        EVENT_ANY = 0,
        EVENT_RELOAD = 10,
    };

    Observer();

    virtual void updatedObservable(EventTypes eventNb) = 0;
};

#endif // OBSERVER_H
