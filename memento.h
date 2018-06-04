#ifndef MEMENTO_H
#define MEMENTO_H

#include "state.h"

class Memento
{
public:
    ~Memento(){delete m_state;}

private:
    friend class StageThreeGame;
    Memento() : m_state(new State()){}

    void backupBalls(std::vector<Ball*>& balls){
        m_state->backupBalls(balls);
    }

    State* getLastState() const {return m_state;}

    State* m_state;
};

#endif // MEMENTO_H
