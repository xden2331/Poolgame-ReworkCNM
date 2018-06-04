#include "stagethreebuilder.h"

Game *StageThreeBuilder::getResult()
{
    return new StageThreeGame(m_builder->getResult());
}
