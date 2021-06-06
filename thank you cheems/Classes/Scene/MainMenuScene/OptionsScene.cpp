#include "OptionsScene.h"

using namespace cocos2d;

Scene* OptionsScene::createScene()
{
	return OptionsScene::create();
}

bool OptionsScene::init()
{
	if (!Scene::init())
		return false;

	creatCheckBox();
	creatSlider();
	creatButton();

	return true;
}

void OptionsScene::creatSlider()
{
}

void OptionsScene::creatCheckBox()
{
}

void OptionsScene::creatButton()
{
}
