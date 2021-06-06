#pragma once
#include "cocos2d.h"
#include "Base/GlobalVariable.h"
using namespace cocos2d;

class OptionsScene:public Scene
{
public:
	cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(OptionsScene);
private:
	Global* global_;

	void creatSlider();
	void creatCheckBox();
	void creatButton();
};

