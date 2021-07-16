//敌人类
#pragma once
#include <cocos2d.h>
#include "AnimationSprite.h"


class Monster : public AnimationSprite
{
public:
    int HealthPoint = 1;
    int AttackPoint = 1;
    bool init() override;
    bool IsAttack = false;//判断是否攻击了
    int TimerAttack = 0;
    int TimerMove = 0;
    void Move();
    void attack();
    static Monster* create();
    //void UpdateMove();
    //bool UpdateAttack();
    bool UpdateTimer();//返回IsAttack
    void die();
};
