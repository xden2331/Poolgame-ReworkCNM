#ifndef OBSERVER_H
#define OBSERVER_H

#include <QApplication>

#define CUE_BALL_REST 0

class Observer
{
public:
    Observer(){}
    virtual ~Observer(){}

    virtual void notify(int sound){
        switch (sound) {
        case CUE_BALL_REST:
            QApplication::beep();
            break;
        default:
            break;
        }
    }
};

#endif // OBSERVER_H
