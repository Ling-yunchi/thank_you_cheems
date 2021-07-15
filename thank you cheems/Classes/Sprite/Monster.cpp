#include "Monster.h"


void Monster::move()
{
    auto action = MoveBy::create(1, Vec2(random(-1, 1) * 99, 0));
    runAction(action);
}

