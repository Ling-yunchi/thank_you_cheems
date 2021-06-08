#include "GameScene.h"

void GameScene::loadMap()
{
}

void GameScene::createSprites()
{
}

void GameScene::createMenu()
{
}

void GameScene::createKBListener()
{
	auto kbListener = EventListenerKeyboard::create();
	kbListener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event) {
		keyMap[code] = true;
	};
	kbListener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event* event) {
		keyMap[code] = false;
	};
	eventDispatcher_->addEventListenerWithSceneGraphPriority(kbListener, this);
}

void GameScene::update(float delta)
{
	for (auto& key : keyMap) {
		if (key.second) {
			log(std::to_string(static_cast<int>(key.first)).c_str());
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

GameScene::GameScene() :
	player(nullptr),
	global_(Global::getInstance()),
	eventDispatcher_(Director::getInstance()->getEventDispatcher())
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

	loadMap();
	createSprites();
	createMenu();
	createKBListener();

	//添加调度器,使每一帧都进入update函数
	this->scheduleUpdate();
	
	return true;
}
