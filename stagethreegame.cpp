#include "stagethreegame.h"

void StageThreeGame::render(QPainter &painter) const{
    Game::render(painter);
}

void StageThreeGame::animate(double dt)
{
    if(m_pressR){
        revert();
        m_pressR = false;
    }
    checkMemento();
    Game::animate(dt);
}

Memento* StageThreeGame::createMemento(){
    Memento* memento = new Memento();
    memento->backupBalls(*Game::getBalls());
    return memento;
}

void StageThreeGame::revert(){
    State* lastState = m_mementoes.at(0)->getLastState();
    auto lastBalls = lastState->getBalls();
    m_balls->clear();
    for(auto b : lastBalls){
        m_balls->push_back(b->clone());
    }
    Ball* c = m_balls->front();
    CueBall* cb = new CueBall(c);
    m_balls->front() = static_cast<Ball*>(cb);
    Game::addMouseFunctions(cb->getEvents());
}

void StageThreeGame::checkMemento(){
    //CueBall* cb = dynamic_cast<CueBall*>(Game::getBalls()->front());
}
