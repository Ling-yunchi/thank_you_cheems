#pragma once
#include "cocos2d.h"
#include "AnimationSprite.h"

class Cheems:public AnimationSprite
{
	int HP;
	int MAXHP;
	bool init() override;
public:
	bool CheemsAttact(int directon, float monster_x, float monster_y);
	int getHP();
	void setHP(int Hp);
	static Cheems* create();
	void hurt();
};

  