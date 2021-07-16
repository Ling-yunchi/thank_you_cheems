#include "Drop.h"
#include "Base/ConstValue.h"

Drop* Drop::create()
{
	auto drop = new (std::nothrow) Drop();
	if (drop && drop->init()) {
		drop->autorelease();
		return drop;
	}
	CC_SAFE_FREE(drop);
	return nullptr;
}

bool Drop::init()
{
	if (!Sprite::init())
		return false;
	
	setTexture("drop.png");
	auto body = cocos2d::PhysicsBody::createCircle(60);
	body->setCategoryBitmask(DropCateoryBitmask);
	body->setCollisionBitmask(DropCollisionBitmask);
	body->setContactTestBitmask(DropContactTestBitmask);
	body->setGravityEnable(false);
	setPhysicsBody(body);

	setScale(0.1);
	
	return true;
}
