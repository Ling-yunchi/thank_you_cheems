#include "SaveChooseScene.h"
#include <fstream>
using namespace std;
using namespace cocos2d;

void SaveChooseScene::file() {
	saveCount = 0;
	fstream saveFile("save.dat", ios::in | ios::out);
	if (saveFile.peek() != EOF) {
		fclose(fopen("save.dat", "w"));//创建文件
		saveFile.open("save.dat");
	}
	while (!saveFile.eof()) {
		saveFile.read(reinterpret_cast<char*>(&saves[saveCount++]), sizeof(Save));
	}
	saveFile.close();
}

void SaveChooseScene::creatButton() {

	//save btn
	TTFConfig config("fonts/Marker Felt.ttf", 60);
	for (int i = 0; i < saveNumMax; i++) {
		auto btn = ui::Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
		auto label = Label::createWithTTF(config, i<saveCount?saves[i].getName():"null");
		label->setTextColor(Color4B::BLACK);
		btn->setTitleLabel(label);
		buttons_[i] = btn;
	}
	for (int i = 0; i < saveNumMax; i++) {
		buttons_[i]->ignoreContentAdaptWithSize(true);
		buttons_[i]->setScale9Enabled(true);
		buttons_[i]->setContentSize(Size(500, 100));
		buttons_[i]->setPosition(Vec2(540, 600 - 130 * i));
		buttons_[i]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				//TODO checkbox
				break;
			default:
				break;
			}
		});
		addChild(buttons_[i], 999);
	}

	//back btn
	auto back = ui::Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
	back->ignoreContentAdaptWithSize(true);
	back->setScale9Enabled(true);
	back->setContentSize(Size(200, 50));
	config.fontSize = 30;
	auto label = Label::createWithTTF(config, "back");
	label->setTextColor(Color4B::BLACK);
	back->setTitleLabel(label);
	back->setPosition(Vec2(540, 70));
	back->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->popScene();
			break;
		default:
			break;
		}
	});
	addChild(back, 999);
}

cocos2d::Scene* SaveChooseScene::createScene() {
	return SaveChooseScene::create();
}

bool SaveChooseScene::init() {
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto startBackground = Sprite::create("bg169.jpg");
	startBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	float winw = visibleSize.width;
	float winh = visibleSize.height;
	float spx = startBackground->getTextureRect().getMaxX();
	float spy = startBackground->getTextureRect().getMaxY();
	startBackground->setScaleX(winw / spx);
	startBackground->setScaleY(winh / spy);
	this->addChild(startBackground, 1);

	file();
	creatButton();

	return true;
}
