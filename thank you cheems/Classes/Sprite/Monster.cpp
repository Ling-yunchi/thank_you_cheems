#include "Monster.h"
#include "Base/ConstValue.h"

void Monster::Move()
{
    auto action = MoveBy::create(1, Vec2(random(-1, 1) * 99, 0));
    runAction(action);
}

void Monster::Attack()
{
	AnimationSprite::attack();
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

	return true;
}

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