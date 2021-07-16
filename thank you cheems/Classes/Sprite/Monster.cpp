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
	setTag(2);
	getPhysicsBody()->setCategoryBitmask(SoybeanCateoryBitmask);
	getPhysicsBody()->setCollisionBitmask(SoybeanCollisionBitmask);
	getPhysicsBody()->setContactTestBitmask(SoybeanContactTestBitmask);

	setScale(0.1);

	return true;
}