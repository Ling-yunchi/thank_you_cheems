#include "Monster.h"
#include "Base/ConstValue.h"
#include "AnimationSprite.h"

void Monster::Move()
{
	AnimationSprite::move(random(-1, 1));
}

void Monster::attack()
{
	if(IsAttack == false){
		AnimationSprite::attack();
		IsAttack = true;
	}
}

Monster* Monster::create()
{
	auto monster = new (std::nothrow) Monster();
	if (monster && monster->init()) {
		monster->autorelease();
		return monster;
	}
	CC_SAFE_FREE(monster);
	return nullptr;
}

bool Monster::init()
{
	AnimationSprite::initWithNameAndSize("soybean", Size(300, 195));
	getPhysicsBody()->setTag(SoybeanTag);
	getPhysicsBody()->setCategoryBitmask(SoybeanCateoryBitmask);
	getPhysicsBody()->setCollisionBitmask(SoybeanCollisionBitmask);
	getPhysicsBody()->setContactTestBitmask(SoybeanContactTestBitmask);

	setScale(0.1);

	speedX_ = 50;

	return true;
}

/*
void Monster::UpdateMove()
{
	int sec = 1;
	TimerMove++;
	if (TimerMove == 60 * sec)
	{
		TimerMove = 0;
		Monster::Move();
	}
}

bool Monster::UpdateAttack()
{
	int sec = 1;
	if (IsAttack==true&& TimerAttack<0)
	{
		TimerAttack = 60 * sec;
	}
	TimerAttack--;
	if (TimerAttack < 0)
	{
		IsAttack = false;
	}


	return IsAttack;
}
*/

bool Monster::UpdateTimer()
{
	int sec1 = 1;
	TimerMove++;
	if (TimerMove == 60 * sec1)
	{
		TimerMove = 0;
		Monster::Move();
	}

	int sec2 = 5;
	if (IsAttack == true && TimerAttack < 0)
	{
		TimerAttack = 60 * sec2;
	}
	TimerAttack--;
	if (TimerAttack < 0)
	{
		IsAttack = false;
	}


	return IsAttack;
}

void Monster::die()
{
	AnimationSprite::die();
	getPhysicsBody()->release();
	setPhysicsBody(nullptr);
}