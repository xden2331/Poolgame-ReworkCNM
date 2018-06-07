#include "visitor.h"

#include "ball.h"

Visitor::Visitor()
{

}

void MixingBallVisitor::visitSimpleBall(Ball *ball){
    m_mixedColor = blendColors(m_mixedColor, ball->getColor());
    m_mixedPos = (m_mixedPos + ball->getPosition())/2;
    m_mixedVel = (m_mixedVel + ball->getVelocity())/2;
    m_mixedMass = (m_mixedMass + ball->getMass())/2;
    m_mixedRadius = (m_mixedRadius + ball->getRadius())/2;
}

void MixingBallVisitor::visitCompositeBall(CompositeBall *ball){
    m_mixedColor = blendColors(m_mixedColor, ball->getColor());
    m_mixedPos = (m_mixedPos + ball->getPosition())/2;
    m_mixedVel = (m_mixedVel + ball->getVelocity())/2;
    m_mixedMass = (m_mixedMass + ball->getMass())/2;
    m_mixedRadius = (m_mixedRadius + ball->getRadius())/2;
}

Ball* MixingBallVisitor::getMixedBall() const{
    return new StageOneBall(m_mixedColor,m_mixedPos,m_mixedVel,m_mixedMass,m_mixedRadius);
}

QColor MixingBallVisitor::blendColors(const QColor &color1, const QColor &color2, qreal ratio){
    int r = color1.red()*(1-ratio) + color2.red()*ratio;
    int g = color1.green()*(1-ratio) + color2.green()*ratio;
    int b = color1.blue()*(1-ratio) + color2.blue()*ratio;

    return QColor(r, g, b, 255);
}
