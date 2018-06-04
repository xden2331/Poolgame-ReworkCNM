#ifndef STAGETHREEBUILDER_H
#define STAGETHREEBUILDER_H

#include "stagetwobuilder.h"
#include "stagethreegame.h"

class StageThreeBuilder : public GameBuilder{
public:
    virtual ~StageThreeBuilder() {delete m_builder;}
    StageThreeBuilder() : m_builder(new StageTwoBuilder()){}
    // GameBuilder interface
    virtual void addBall(QJsonObject &ballData) override{
        m_builder->addBall(ballData);
    }
    virtual void addTable(QJsonObject &tableData) override{
        m_builder->addTable(tableData);
    }
    virtual Game *getResult() override;

private:
    StageTwoBuilder* m_builder;
};

#endif // STAGETHREEBUILDER_H
