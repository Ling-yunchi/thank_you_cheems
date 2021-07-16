#pragma once
#include <cocos2d.h>

class Drop: public cocos2d::Sprite
{
public:
	static Drop* create();
private:
	bool init() override;
};

