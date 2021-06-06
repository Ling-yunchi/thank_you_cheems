#include "GameScene.h"

void GameScene::update(float delta)
{
	for (auto& key : keyMap) {
		if (key.second) {
			switch (key.first)
			{

			case EventKeyboard::KeyCode::KEY_W:
			{
				break;
			}

			case EventKeyboard::KeyCode::KEY_S:
			{
				break;
			}

			case EventKeyboard::KeyCode::KEY_A:
			{
				break;
			}

			case EventKeyboard::KeyCode::KEY_D:
			{
				break;
			}

			case EventKeyboard::KeyCode::KEY_ESCAPE:
			{
				break;
			}

			case EventKeyboard::KeyCode::KEY_SPACE:
			{
				break;
			}
				
			default: 
				break;
			}
		}
	}
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	keyMap[keyCode] = true;
}

void GameScene::onKenReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	keyMap[keyCode] = false;
}

GameScene::GameScene():
player(nullptr),
global_(Global::getInstance())
{
	
}

GameScene::~GameScene()
{
	
}

cocos2d::Scene* GameScene::creatScsene()
{
	return  GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::initWithPhysics())
		return false;

	

	//添加调度器,使每一帧都进入update函数
	this->scheduleUpdate();
}
