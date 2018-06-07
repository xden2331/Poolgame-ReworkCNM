#ifndef VISITOR_H
#define VISITOR_H

#include <QColor>
#include <QVector2D>

class Ball;
class CompositeBall;

class Visitor
{
public:
    virtual ~Visitor(){}

    virtual void visitSimpleBall(Ball*) = 0;
    virtual void visitCompositeBall(CompositeBall*) = 0;

protected:
    Visitor();
};

class MixingBallVisitor : public Visitor{
public:
    ~MixingBallVisitor(){}

    MixingBallVisitor(){}

    Ball* getMixedBall() const;

    // Visitor interface
    virtual void visitSimpleBall(Ball *) override;
    virtual void visitCompositeBall(CompositeBall *) override;

private:
    // SOURCE: https://blog.embedded.pro/blending-colors-in-qt/
    QColor blendColors (const QColor& color1, const QColor& color2, qreal ratio = 0.5);

    QColor m_mixedColor = QColor(0,0,0);
    QVector2D m_mixedPos = QVector2D(0,0);
    QVector2D m_mixedVel = QVector2D(0,0);
    double m_mixedMass = 0;
    int m_mixedRadius = 0;
};

#endif // VISITOR_H
