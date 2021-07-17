/**
 * °ïÖú³¡¾°
 */
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class HelpScene:public Scene
{
public:
	static Scene* createScene();
	bool init() override;
	CREATE_FUNC(HelpScene);
private:
	Size visibleSize_;
	void createButton();
	void createLabel();
};

