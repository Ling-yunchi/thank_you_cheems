#pragma once
#include <cocos2d.h>

class Drop: public cocos2d::Sprite
{
public:
	static Drop* create(cocos2d::Vec2 soybean, cocos2d::Vec2 cheems);
private:
	bool init(cocos2d::Vec2, cocos2d::Vec2);
};

