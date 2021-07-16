#include "Drop.h"
#include "Base/ConstValue.h"


Drop* Drop::create(cocos2d::Vec2 soybean, cocos2d::Vec2 cheems)
{
	auto drop = new (std::nothrow) Drop();
	if (drop && drop->init(soybean,cheems)) {
		drop->autorelease();
		return drop;
	}
	CC_SAFE_FREE(drop);
	return nullptr;
}

bool Drop::init(cocos2d::Vec2 soybean, cocos2d::Vec2 cheems)
{
	if (!Sprite::init())
		return false;
	
	setTexture("drop.png");
	auto body = cocos2d::PhysicsBody::createCircle(60);
	body->setTag(DropTag);
	body->setCategoryBitmask(DropCateoryBitmask);
	body->setCollisionBitmask(DropCollisionBitmask);
	body->setContactTestBitmask(DropContactTestBitmask);
	body->setGravityEnable(false);
	setPhysicsBody(body);

	setScale(0.1);
	
	setPosition(soybean);
	
	//if(cheems.x<soybean.x)
	//	setRotation(90-soybean.getAngle(cheems)* 57.29578);
	//else
	//	setRotation(soybean.getAngle(cheems) * 57.29578 - 90);
	
	auto v = cheems - soybean;
	
	body->setVelocity(v / v.length() * 150);
	
	return true;
}
