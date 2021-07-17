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

	setScale(0.15);
	
	setPosition(soybean);
	
	auto v = cheems - soybean;
	auto radians = -cocos2d::Vec2(0, -1).getAngle(v) * 57.2957;
	setRotation(radians);
	body->setVelocity(v / v.length() * 180);

	setOpacity(0);
	//cocos2d::Sequence::createWithTwoActions(cocos2d::MoveBy::create(1.5, cocos2d::Vec2::ZERO), cocos2d::FadeIn::create(0.1))
	runAction(cocos2d::Sequence::createWithTwoActions(
		cocos2d::MoveBy::create(0.3, cocos2d::Vec2::ZERO),
		cocos2d::FadeIn::create(0.1)));
	
	return true;
}
