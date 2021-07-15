//µ–»À¿‡
#pragma once
#include <cocos2d.h>
#include "AnimationSprite.h"


class Monster : public AnimationSprite
{
private:
    int HealthPoint = 1;
    int AttackPoint = 1;
public:
    void move();

};
