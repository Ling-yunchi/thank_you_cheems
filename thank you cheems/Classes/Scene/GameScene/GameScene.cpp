#include "GameScene.h"

#include "VisibleRect.h"

void GameScene::loadMap()
{
	auto map = cocos2d::TMXTiledMap::create("map/testMap.tmx");
	auto objGroup = map->getObjectGroup("ground");
	auto& objs = objGroup->getObjects();

	for (auto& obj : objs) {
		auto objMap = obj.asValueMap();
		auto node = Node::create();
		node->setPosition(objMap["x"].asFloat() + objMap["width"].asFloat() / 2, objMap["y"].asFloat() + objMap["height"].asFloat() / 2);
		auto body = PhysicsBody::createBox(Size(objMap["width"].asFloat(), objMap["height"].asFloat()));
		body->setDynamic(false);
		node->setPhysicsBody(body);
		map->addChild(node);
	}

	map->setScale(2);
	map_ = map;
	addChild(map_, 0);
}

void GameScene::createSprites()
{
	const auto factory = dragonBones::CCFactory::getFactory();
	factory->loadDragonBonesData("Animation/Cheems/Cheems_ske.json", "cheems");
	factory->loadTextureAtlasData("Animation/Cheems/Cheems_tex.json", "cheems");

	cheems_ = AnimationSprite::create("cheems", Size(220, 300));
	auto pos = map_->getObjectGroup("sprites")->getObject("cheems");
	cheems_->setPosition(pos["x"].asFloat(),pos["y"].asFloat());
	cheems_->setScale(0.1);
	map_->addChild(cheems_, 999);
}

void GameScene::createMenu()
{
}

void GameScene::createListener()
{
	auto kbListener = EventListenerKeyboard::create();
	kbListener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event) {
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			left_ = true;
			dir_ = -1;
			updateMove(-1);
			break;

		case cocos2d::EventKeyboard::KeyCode::KEY_D:
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			right_ = true;
			dir_ = 1;
			updateMove(1);
			break;

		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			cheems_->down();
			break;

		case cocos2d::EventKeyboard::KeyCode::KEY_W:
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			cheems_->jump();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_J:
			cheems_->attack();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_K:
			cheems_->hurt();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_L:
			cheems_->die();
			break;
		}
	};
	kbListener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event* event) {
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			left_ = false;
			updateMove(-1);
			dir_ = 0;
			break;

		case cocos2d::EventKeyboard::KeyCode::KEY_D:
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			right_ = false;
			updateMove(1);
			dir_ = 0;
			break;

		case cocos2d::EventKeyboard::KeyCode::KEY_W:
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			break;
		}};
	eventDispatcher_->addEventListenerWithSceneGraphPriority(kbListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [this](PhysicsContact& contact) {
		log("%f,%f", cheems_->getPosition().x, cheems_->getPosition().y);
		cheems_->down();
		return true;
	};
	eventDispatcher_->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameScene::update(float delta)
{
	cheems_->updatePosition();
	moveMap();
}

void GameScene::updateMove(int dir)
{
	if (left_ && right_)
		cheems_->move(dir);
	else if (left_)
		cheems_->move(-1);
	else if (right_)
		cheems_->move(1);
	else
		cheems_->move(0);
}

void GameScene::moveMap()
{
	auto a = map_->getPosition();
	auto b = cheems_->getPosition();

	static float x = b.x;
	static float y = b.y;
	if (a.x + x > 200 || a.x + x < map_->getContentSize().width - 200)
		map_->runAction(MoveBy::create(0.1, Vec2(x - b.x, y - b.y)));

	x = b.x;
	y = b.y;
}

GameScene::GameScene() :
	cheems_(nullptr),
	global_(Global::getInstance()),
	eventDispatcher_(Director::getInstance()->getEventDispatcher()),
	spriteLayer_(Layer::create())
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
	createListener();

	//添加调度器,使每一帧都进入update函数
	this->scheduleUpdate();

	return true;
}
