#pragma once
#include "cocos2d.h"
#include "AnimationSprite.h"
#include "Monster.h"	

class Cheems :public AnimationSprite
{
	int HP;
	bool init() override;
	bool isattack = false;
	int timerAttack;
	bool ishurt = false;
	int timerHurt;
	PhysicsBody* attackArea;
public:
	void attack();
	int getHP();
	static Cheems* create();
	void hurt();
	void updateTimer();
	bool getIsattact();
};

  