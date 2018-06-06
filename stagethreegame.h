#ifndef STAGETHREEGAME_H
#define STAGETHREEGAME_H

#include "game.h"
#include "memento.h"

class StageThreeGame : public Game
{
private:
    bool m_pressR = false;
    std::vector<Memento*> m_mementoes;
    bool hadMemento = false;

public:
    StageThreeGame(Game* baseGame) : Game(baseGame->getBalls(), baseGame->getTable()),
        m_mementoes(std::vector<Memento*>()){
        m_mementoes.push_back(createMemento());
        revert();
    }
    ~StageThreeGame(){}

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
};

#endif // STAGETHREEGAME_H
