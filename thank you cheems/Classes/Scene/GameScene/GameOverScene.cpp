#include "GameOverScene.h"

#include <fstream>

#include "GameScene.h"
#include "base/GlobalVariable.h"
#include "Base/Save.h"
#include "Scene/SaveChooseScene/SaveChooseScene.h"

bool GameOverScene::victory_ = false;

Scene* GameOverScene::createScene(bool res)
{
	if (res)
		victory_ = true;
	else
		victory_ = false;

	return GameOverScene::create();
}

bool GameOverScene::init()
{
	if (!Scene::init())
		return false;

	log("GameOverScene init begin");
	
	if (victory_) {
		victory_front_create();
		victory_menu_create();
	}
	else {
		defeat_front_create();
		defeat_menu_create();
	}

	log("GameOverScene init finished");
	
	return true;
}

void GameOverScene::victory_front_create()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("win_bg.jpg");
	background->setPosition(Vec2(size.width / 2, size.height / 2));
	background->setScale(size.width / background->getTextureRect().getMaxX());
	this->addChild(background, 1);
}

void GameOverScene::victory_menu_create()
{
	auto thank = Label::create("Thank you for playing", FONT_MARKER_FELT, 30);
	thank->setPosition(Vec2(870, 670));
	addChild(thank, 999);

	auto save = Label::create("Save and Exit", FONT_MARKER_FELT, 40);
	auto item = MenuItemLabel::create(save,[&](Ref* sender) {
		GameOverScene::save();
		Director::getInstance()->replaceScene(SaveChooseScene::createScene());
	});
	auto menu = Menu::create(item, NULL);
	menu->setPosition(Vec2(880, 80));
	addChild(menu, 999);
}

void GameOverScene::defeat_front_create()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("defeat_bg.jpg");
	background->setPosition(Vec2(size.width / 2, size.height / 2));
	background->setScale(size.width / background->getTextureRect().getMaxX());
	this->addChild(background, 1);
}

void GameOverScene::defeat_menu_create()
{
	auto retry = Label::create("Retry", FONT_MARKER_FELT, 40);
	retry->setTextColor(Color4B::RED);
	auto retryItem = MenuItemLabel::create(retry, [&](Ref* sender) {
		Director::getInstance()->replaceScene(GameScene::creatScsene());
	});
	auto exit = Label::create("Exit", FONT_MARKER_FELT, 40);
	exit->setTextColor(Color4B::RED);
	auto exitItem = MenuItemLabel::create(exit, [&](Ref* sender) {
		Director::getInstance()->replaceScene(SaveChooseScene::createScene());
	});
	
	auto menu = Menu::create(retryItem, exitItem, NULL);
	menu->setPosition(Vec2(850, 200));
	exitItem->setPosition(Vec2(0, -100));

	addChild(menu, 999);
}

void GameOverScene::save()
{
	std::list<Save> saves;
	std::ifstream in("save.dat");
	while (in.peek() != EOF) {
		Save temp;
		in.read(reinterpret_cast<char*>(&temp), sizeof(Save));
		saves.push_back(temp);
	}
	in.close();

	for (auto& save : saves) {
		if (strcmp(Global::getInstance()->saveName.c_str() ,save.getName()) == 0)
			save.update();
	}
	
	std::ofstream out("save.dat");
	for (auto it = saves.begin(); it != saves.end(); it++) {
		out.write(reinterpret_cast<char*>(&(*it)), sizeof(Save));
	}
	out.close();
}

