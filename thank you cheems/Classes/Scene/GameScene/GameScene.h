/**
 * ��Ϸ���г���
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
	//���ڴ洢�����Ƿ����ͷ�
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;

	//��Դ���غ���
	void loadMap();
	void createSprites();
	void createMenu();
	void createKBListener();

	//���º���
	void update(float delta) override;

public:
	GameScene();
	~GameScene();
	static cocos2d::Scene* creatScsene();
	bool init() override;
	
	CREATE_FUNC(GameScene);
};

