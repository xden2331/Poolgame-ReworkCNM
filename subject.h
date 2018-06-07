#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"

class Subject
{
public:
    Subject(){}
    virtual void notifyObservers(int sound) const = 0;
    virtual void addObservers(Observer*) = 0;
    virtual void deleteObservers(Observer* observer) = 0;
};

#endif // SUBJECT_H
