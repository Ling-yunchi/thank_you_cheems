#include "GameScene.h"

#include "GameOverScene.h"
#include "PauseScene.h"
#include "VisibleRect.h"
#include "ui/UIRichText.h"
#include "Base/ConstValue.h"

#define DEBUG

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
		body->setCategoryBitmask(GroundCateoryBitmask);
		body->setCollisionBitmask(GroundCollisionBitmask);
		body->setContactTestBitmask(GroundContactTestBitmask);
		body->setDynamic(false);
		node->setPhysicsBody(body);
		map->addChild(node);
	}

	map->setScale(2.5);
	map_ = map;
	addChild(map_, 0);
}

void GameScene::createSprites()
{
	const auto factory = dragonBones::CCFactory::getFactory();
	factory->loadDragonBonesData("Animation/Cheems/Cheems_ske.json", "cheems");
	factory->loadTextureAtlasData("Animation/Cheems/Cheems_tex.json", "cheems");
	factory->loadDragonBonesData("Animation/Sweating_soybean/Sweating_soybean_ske.json", "soybean");
	factory->loadTextureAtlasData("Animation/Sweating_soybean/Sweating_soybean_tex.json", "soybean");

	cheems_ = AnimationSprite::create("cheems", Size(220, 300));
	auto pos = map_->getObjectGroup("cheems")->getObject("cheems");
	cheems_->setPosition(pos["x"].asFloat(),pos["y"].asFloat());
	cheems_->setScale(0.1);
	cheems_->getPhysicsBody()->setCategoryBitmask(0x1);
	cheems_->getPhysicsBody()->setCollisionBitmask(0x1);
	cheems_->getPhysicsBody()->setContactTestBitmask(0x2);
	map_->addChild(cheems_, 999);

	//auto objGroup = map_->getObjectGroup("soybean");
	//auto& objs = objGroup->getObjects();
	//for(auto& obj : objs) {
	//	auto& vmap = obj.asValueMap();
	//	auto soybean = AnimationSprite::create("soybean", Size(300, 195));
	//	soybean->setScale(0.2);
	//	soybean->setPosition(Vec2(vmap["x"].asFloat(), vmap["y"].asFloat()));
	//	map_->addChild(soybean, 999);
	//}
	auto soybean = AnimationSprite::create("soybean", Size(300, 195));
	soybean->setScale(0.2);
	soybean->setPosition(VisibleRect::center());
	soybean->getPhysicsBody()->setCategoryBitmask(0x2);
	soybean->getPhysicsBody()->setCollisionBitmask(0x1);
	soybean->getPhysicsBody()->setContactTestBitmask(0x1);


	map_->addChild(soybean, 999);
	
	auto drop = Sprite::create("drop.png");
	drop->setPosition(VisibleRect::center());
	auto body = cocos2d::PhysicsBody::createCircle(60);
	drop->setScale(0.1);
	drop->setPhysicsBody(body);
	map_->addChild(drop);
}

void GameScene::createMenu()
{
	//HP显示
	auto hp = ui::RichText::create();
	hp->pushBackElement(ui::RichElementText::create(1, Color3B::WHITE, 255, "H P : ", FONT_MARKER_FELT, 40));
	hp->setPosition(Vec2(100, 660));
	addChild(hp, 999);

	hp_ = 3;//cheems_.getHP();
	hearts_.resize(3);
	for (int i = 0; i < hp_; i++) {
		auto h = Sprite::create("heart.png");
		h->setScale(3);
		h->setPosition(Vec2(170 + 60 * i, 660));
		addChild(h, 999);
		hearts_.push_back(h);
	}

	//暂停按钮
	auto label = Label::create("pause", FONT_MARKER_FELT, 40);
	auto pause = MenuItemLabel::create(label, [&](Ref* sender) {
		Director::getInstance()->pushScene(PauseScene::createScene());	
	});
	auto menu = Menu::create(pause, NULL);
	menu->setPosition(Vec2(990, 660));
	addChild(menu, 999);
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
		case cocos2d::EventKeyboard::KeyCode::KEY_O:
			gameOver(true);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_P:
			gameOver(false);
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
	updateAttack();
	updateMonsters();
	updateHeart();
	judgeGameOver();
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

void GameScene::updateAttack()
{
	//TODO: 矩形检测
}

void GameScene::updateMonsters()
{
	//TODO : Move, Attack; 
}

void GameScene::updateHeart()
{
	//更新血量显示
	/*if (cheems_.getHP != hp_) {
		auto heart = Sprite::create("heart.png");
		auto empty_heart = Sprite::create("empty_heart.png");
		for (int i = 0; i < cheems_.getMaxHP; i++)
			if (i < hp_)
				hearts_[i]->setTexture(heart->getTexture());
			else
				hearts_[i]->setTexture(empty_heart->getTexture());
	}*/
}

void GameScene::judgeGameOver()
{
	//if (monsters.empty())
	//	gameOver(true);
	
	//if(cheems_.getHP()==0)
	//	gameOver(false);
}

void GameScene::moveMap()
{
	auto a = map_->getPosition();
	auto b = cheems_->getPosition();

	static float x = b.x;
	static float y = b.y;
	
	map_->runAction(MoveBy::create(0.1, Vec2((x - b.x)*map_->getScale(), y - b.y)));

	x = b.x;
	y = b.y;
}

void GameScene::gameOver(bool res)
{
	Director::getInstance()->runWithScene(GameOverScene::createScene(res));
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
	auto scene = GameScene::create();
#ifdef  DEBUG
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif
	return scene;
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
