/**
 * ��Ϸ���г���
 * @author wr
 */
#pragma once
#include "cocos2d.h"
#include "Base/GlobalVariable.h"
#include "Sprite/AnimationSprite.h"
#include <list>

using namespace cocos2d;

class GameScene :public Scene
{
private:
	AnimationSprite* cheems_;
	std::list<Sprite*> monsters;
	std::list<Sprite*> flyItems;
	Global* global_;
	EventDispatcher* eventDispatcher_;
	TMXTiledMap* map_;
	Layer* spriteLayer_;

	bool left_ = false;
	bool right_ = false;
	int dir_ = 0;

	//��Դ���غ���
	void loadMap();
	void createSprites();
	void createMenu();
	void createListener();

	//���º���
	void update(float delta) override;
	void updateMove(int dir);
	void moveMap();

public:
	GameScene();
	~GameScene();
	static cocos2d::Scene* creatScsene();
	bool init() override;
	
	CREATE_FUNC(GameScene);
};