#include "PauseScene.h"

#include "Scene/MainMenuScene/OptionsScene.h"
#include "Scene/SaveChooseScene/SaveChooseScene.h"

Scene* PauseScene::createScene()
{
	return PauseScene::create();
}

bool PauseScene::init()
{
	if (!Scene::init())
		return false;

	creatBg();
	createMenu();
	
	return true;
}

void PauseScene::creatBg()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("pause_bg.jpg");
	background->setPosition(Vec2(size.width / 2, size.height / 2));
	background->setScale(size.height / background->getTextureRect().getMaxY());
	this->addChild(background, 1);
}

void PauseScene::createMenu()
{
	auto cheems = Sprite::create("pause_cheems.jpg");
	cheems->setScale(0.3);
	cheems->setPosition(Vec2(540, 460));
	addChild(cheems, 999);

	TTFConfig ttfConfig("fonts/Marker Felt.ttf", 40);
	auto continueLable = Label::createWithTTF(ttfConfig, "continue");
	auto optionLabel = Label::createWithTTF(ttfConfig, "option");
	auto exitLabel = Label::createWithTTF(ttfConfig, "exit");

	continueLable->enableShadow();
	optionLabel->enableShadow();
	exitLabel->enableShadow();

	auto continueItem = MenuItemLabel::create(continueLable, [&](Ref* sender) {
		Director::getInstance()->popScene();
	});
	auto optionItem = MenuItemLabel::create(optionLabel, [&](Ref* sender) {
		Director::getInstance()->pushScene(OptionsScene::createScene());
	});
	auto exitItem = MenuItemLabel::create(exitLabel, [&](Ref* sender) {
		Director::getInstance()->popScene();
		Director::getInstance()->popScene();
		Director::getInstance()->popScene();
	});

	auto menu = Menu::create(continueItem, optionItem, exitItem, NULL);
	menu->setPosition(Vec2(540, 240));
	optionItem->setPosition(Vec2(0, -80));
	exitItem->setPosition(Vec2(0, -160));

	addChild(menu, 999);
	
}
