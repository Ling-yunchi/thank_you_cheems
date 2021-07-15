/**
 * 游戏结束界面
 * @author wr
 */
#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class GameOverScene :public cocos2d::Scene
{
public:
	static Scene* createScene(bool res);
	bool init() override;
	CREATE_FUNC(GameOverScene);
	static bool victory_;
private:

	void victory_front_create();
	void victory_menu_create();

	void defeat_front_create();
	void defeat_menu_create();

	void save();
};

