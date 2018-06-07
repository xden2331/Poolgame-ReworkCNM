#ifndef STAGETHREEGAME_H
#define STAGETHREEGAME_H

#include "game.h"
#include "memento.h"
#include "subject.h"
#include "observer.h"

#include "visitor.h"

#define CUE_BALL_REST 0

class StageThreeGame : public Game, public Subject
{
private:
    bool m_pressR = false;
    std::vector<Memento*> m_mementoes;
    bool hadMemento = false;
    std::vector<Observer*> m_observers;

public:
    StageThreeGame(Game* baseGame) : Game(baseGame->getBalls(), baseGame->getTable()),
        m_mementoes(std::vector<Memento*>()), m_observers(std::vector<Observer*>())
    {
        m_mementoes.push_back(createMemento());
        revert();
        addObservers(new Observer());
    }

    virtual ~StageThreeGame(){
        for(auto m : m_mementoes) delete m;
        for(auto o : m_observers) delete o;
    }

    void keyPress(bool pressOnR){
        m_pressR = pressOnR;
    }

    // Game interface
    virtual void render(QPainter &painter) const override;

    virtual void animate(double dt) override;

    void checkMemento();

    Memento* createMemento();

    void revert();

    void createBall(QVector2D& pos, QVector2D& vel,
                    QColor& color, int radius, double mass);

    void visitBalls();

    // Subject interface
public:
    virtual void notifyObservers(int sound) const override{
        for(auto observer : m_observers){
            observer->notify(sound);
        }
    }
    virtual void addObservers(Observer* observer) override{
        m_observers.push_back(observer);
    }

    /**
     * @brief deleteObservers detach an observer from a subject
     * @param observer the observer removed
     */
    virtual void deleteObservers(Observer *observer) override{
        delete observer;
        m_observers.erase(std::find(m_observers.begin(), m_observers.end(), nullptr));
    }
};

#endif // STAGETHREEGAME_H
