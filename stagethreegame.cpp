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
    Memento* memento = nullptr;
    auto idx = 0;
    if(isCueBallMoving()){
        memento = new Memento();
        memento = m_mementoes.at(idx);
        m_mementoes.clear();
        m_mementoes.push_back(memento);
    }else{
        if(m_mementoes.size() > 1){
            idx = m_mementoes.size()-2;
        }
    }
    State* lastState = m_mementoes.at(idx)->getLastState();
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
    if(!isCueBallMoving() && !hadMemento){
        m_mementoes.push_back(createMemento());
        hadMemento = true;
    }else if(isCueBallMoving()){
        hadMemento = false;
    }
}

void StageThreeGame::createBall(QVector2D &pos, QVector2D &vel, QColor &color, int radius, double mass)
{
    Ball* ball = new StageOneBall(color, pos, vel, mass, radius);
    auto balls = Game::getBalls();
    balls->push_back(ball);

    auto memento = createMemento();
    m_mementoes.clear();
    m_mementoes.push_back(memento);
}
