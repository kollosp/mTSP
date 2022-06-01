#include "Observable.h"
#include <QDebug>

Observable::Observable()
{

}

Observer* Observable::attach(Observer *o)
{
    if(o!= nullptr)
        observers.push_back(o);
    return o;
}

Observer* Observable::detach(Observer *o)
{
    for(unsigned int i=0;i<observers.size();++i){
        if(observers[i] == o){
            observers.erase(observers.begin()+i);
            break;
        }
    }
    return o;
}

void Observable::notify(Observer::EventTypes eventNb)
{
    for(unsigned int i=0;i<observers.size();++i){
        if(observers[i]){
            observers[i]->updatedObservable(eventNb);
        }
    }
}
