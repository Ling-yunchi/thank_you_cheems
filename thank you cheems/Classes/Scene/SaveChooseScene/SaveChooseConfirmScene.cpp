#include "SaveChooseConfirmScene.h"

#include <fstream>

#include "SaveChooseScene.h"
#include "VisibleRect.h"
#include "Base/GlobalVariable.h"
#include "Base/Save.h"
#include "ui/UIButton.h"
#include "ui/UITextField.h"

cocos2d::Scene* SaveChooseConfirmScene::createScene()
{
	return SaveChooseConfirmScene::create();
}

bool SaveChooseConfirmScene::init()
{
	if (!Scene::init())
		return false;

	fileRead();
	createBackground();
	creatLabel();
	creatButton();

	return true;
}

void SaveChooseConfirmScene::creatLabel()
{
	//БъЬт
	auto save = Label::createWithTTF("Save", FONT_MARKER_FELT, 50);
	save->setPosition(Vec2(540, 660));
	addChild(save, 100);

	auto saveName = ui::TextField::create(this->save.getName(), FONT_MARKER_FELT, 40);
	saveName->setPosition(Vec2(630, 520));
	saveName->setColor(Color3B::GRAY);
	saveName->setTouchAreaEnabled(false);
	this->addChild(saveName, 100);

	auto saveN = Label::createWithTTF("Save Name:", FONT_MARKER_FELT, 40);
	saveN->setPosition(Vec2(290, 520));
	saveN->setColor(Color3B::BLACK);
	addChild(saveN, 100);

	auto createTime = ui::TextField::create(this->save.getCreateTime(), FONT_MARKER_FELT, 30);
	createTime->setPosition(Vec2(630, 440));
	createTime->setColor(Color3B::GRAY);
	createTime->setTouchAreaEnabled(false);
	this->addChild(createTime, 100);

	auto createT = Label::createWithTTF("Create Time:", FONT_MARKER_FELT, 30);
	createT->setPosition(Vec2(290, 450));
	createT->setColor(Color3B::BLACK);
	addChild(createT, 100);

	auto updateTime = ui::TextField::create(this->save.getSaveTime(), FONT_MARKER_FELT, 30);
	updateTime->setPosition(Vec2(630, 410));
	updateTime->setColor(Color3B::GRAY);
	updateTime->setTouchAreaEnabled(false);
	this->addChild(updateTime, 100);

	auto updateT = Label::createWithTTF("Update Time:", FONT_MARKER_FELT, 30);
	updateT->setPosition(Vec2(290, 420));
	updateT->setColor(Color3B::BLACK);
	addChild(updateT, 100);
}

void SaveChooseConfirmScene::createBackground()
{
	auto background = Sprite::create("bg1.jpeg");
	background->setPosition(VisibleRect::center());
	addChild(background, 1);

	auto widgetBackground = Sprite::create("widget_bg.png");
	widgetBackground->setOpacity(200);
	widgetBackground->setScale(0.7, 0.5);
	widgetBackground->setPosition(Vec2(540, 400));
	addChild(widgetBackground, 2);
}

void SaveChooseConfirmScene::creatButton()
{
	//back btn
	auto back = ui::Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
	back->ignoreContentAdaptWithSize(true);
	back->setScale9Enabled(true);
	back->setContentSize(Size(200, 50));
	auto label = Label::createWithTTF( "back",FONT_MARKER_FELT, 30);
	label->setTextColor(Color4B::BLACK);
	back->setTitleLabel(label);
	back->setPosition(Vec2(540, 50));
	back->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
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

	//confirm btn
	auto confirm = ui::Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
	confirm->ignoreContentAdaptWithSize(true);
	confirm->setScale9Enabled(true);
	confirm->setContentSize(Size(280, 90));
	auto label1 = Label::createWithTTF("Confirm", FONT_MARKER_FELT, 30);
	label1->setTextColor(Color4B::BLACK);
	confirm->setTitleLabel(label1);
	confirm->setPosition(Vec2(350, 300));
	confirm->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
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
	addChild(confirm, 999);

	//delete btn
	auto deletebtn = ui::Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
	deletebtn->ignoreContentAdaptWithSize(true);
	deletebtn->setScale9Enabled(true);
	deletebtn->setContentSize(Size(280, 90));
	auto label2 = Label::createWithTTF("Delete", FONT_MARKER_FELT, 30);
	label2->setTextColor(Color4B::BLACK);
	deletebtn->setTitleLabel(label2);
	deletebtn->setPosition(Vec2(730, 300));
	deletebtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			fileWrite();
			Director::getInstance()->replaceScene(SaveChooseScene::createScene());
			break;
		default:
			break;
		}
	});
	addChild(deletebtn, 999);
	
}

void SaveChooseConfirmScene::fileRead()
{
	std::ifstream in("save.dat");
	while (in.peek() != EOF) {
		Save temp;
		in.read(reinterpret_cast<char*>(&temp), sizeof(Save));
		if (strcmp(temp.getName(), Global::getInstance()->saveName.c_str()) == 0) {
			save = temp;
			break;
		}
	}
	in.close();
}

void SaveChooseConfirmScene::fileWrite()
{
	std::list<Save> saves;
	std::ifstream in("save.dat");
	while (in.peek() != EOF) {
		Save temp;
		in.read(reinterpret_cast<char*>(&temp), sizeof(Save));
		if(strcmp(temp.getName(), Global::getInstance()->saveName.c_str())!=0) {
			saves.push_back(temp);
		}
	}
	in.close();
	std::ofstream out("save.dat");
	for(auto it = saves.begin();it!=saves.end();it++) {
		out.write(reinterpret_cast<char*>(&(*it)), sizeof(Save));
	}
	out.close();
}
