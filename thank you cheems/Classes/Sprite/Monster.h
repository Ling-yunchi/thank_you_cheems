//������
#pragma once
#include <cocos2d.h>
#include "AnimationSprite.h"


class Monster : public AnimationSprite
{
public:
    int HealthPoint = 1;
    int AttackPoint = 1;
    bool init() override;
    bool IsAttack = false;//�ж��Ƿ񹥻���
    int TimerAttack = 0;
    int TimerMove = 0;
    void Move();
    void Attack();
    static Monster* create();
    void UpdateMove();
    bool UpdateAttack();
};
