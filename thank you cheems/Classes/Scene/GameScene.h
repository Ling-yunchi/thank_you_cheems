/**
 * ��Ϸ���г���
 * @author wr
 */
#pragma once
#include "cocos2d.h"
#include "../Base/GlobalVariable.h"
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
	//���ڴ洢�����Ƿ����ͷ�
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;

	//��Դ���غ���
	void loadMap();
	void creatSprites();
	void creatMenu();

	//���º���
	void update(float delta) override;

	//������⺯��
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKenReleased(EventKeyboard::KeyCode keyCode, Event* event);

public:
	GameScene();
	~GameScene();
	static cocos2d::Scene* createScene();
	bool init() override;
	
	CREATE_FUNC(GameScene);
};

