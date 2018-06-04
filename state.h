#ifndef STATE_H
#define STATE_H

#include "ball.h"
#include "table.h"

class State
{
public:
    virtual ~State(){}

private:
    friend class StageThreeGame;
    friend class Memento;

    State():m_balls(std::vector<Ball*>()){}

    void backupBalls(std::vector<Ball*>& balls){
        for(auto b:balls){
            m_balls.push_back(b->clone());
        }
    }

    std::vector<Ball*> getBalls() const {return m_balls;}

private:
    std::vector<Ball*> m_balls;
};

#endif // STATE_H
