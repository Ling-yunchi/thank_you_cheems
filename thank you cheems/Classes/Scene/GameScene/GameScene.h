/**
 * 游戏运行场景
 * @author wr
 */
#pragma once
#include "cocos2d.h"
#include "Base/GlobalVariable.h"
#include <list>
#include <map>

using namespace cocos2d;

class GameScene :public Scene
{
private:
	Sprite* player;
	std::list<Sprite*> monsters;
	std::list<Sprite*> flyItems;
	Global* global_;
	EventDispatcher* eventDispatcher_;
	//用于存储按键是否按下释放
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;

	//资源加载函数
	void loadMap();
	void createSprites();
	void createMenu();
	void createKBListener();

	//更新函数
	void update(float delta) override;

public:
	GameScene();
	~GameScene();
	static cocos2d::Scene* creatScsene();
	bool init() override;
	
	CREATE_FUNC(GameScene);
};

