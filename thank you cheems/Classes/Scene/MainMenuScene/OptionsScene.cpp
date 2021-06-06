#include "OptionsScene.h"

#include <iostream>

#include "VisibleRect.h"
#include "ui/UIButton.h"
#include "ui/CocosGUI.h"
#include "Base/GlobalVariable.h"

using namespace cocos2d;
using namespace ui;

OptionsScene::OptionsScene():
global_(Global::getInstance())
{
}

Scene* OptionsScene::createScene()
{
	return OptionsScene::create();
}

bool OptionsScene::init()
{
	if (!Scene::init())
		return false;

	createBackground();
	creatCheckBox();
	creatSlider();
	creatButton();

	return true;
}

void OptionsScene::createBackground()
{
	auto optionsBackground = Sprite::create("bg3.jpeg");
	optionsBackground->setPosition(VisibleRect::center());
	addChild(optionsBackground, 1);

	auto optionsWidgetBackground = Sprite::create("widget_bg.png");
	optionsWidgetBackground->setOpacity(200);
	optionsWidgetBackground->setScale(0.7);
	optionsWidgetBackground->setPosition(VisibleRect::center());
	addChild(optionsWidgetBackground, 2);
}

void OptionsScene::creatSlider()
{
	//标题
	auto options = Label::createWithTTF("Options", FONT_MARKER_FELT, 50);
	options->setPosition(Vec2(540, 660));
	addChild(options, 100);
	
	//音乐music
	auto musicLabel = Label::createWithTTF("music:", FONT_MARKER_FELT, 40);
	musicLabel->setPosition(Vec2(240, 530));
	musicLabel -> setColor(Color3B::BLACK);
	addChild(musicLabel, 100);

	auto music = Slider::create();
	music->loadBarTexture("Slider_Back.png");
	music->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	music->loadProgressBarTexture("Slider_PressBar.png");
	music->setScale9Enabled(true);
	music->setContentSize(Size(420, 20));
	music->setMaxPercent(100);
	music->setPercent(100);
	music->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED: {
			auto musicField = dynamic_cast<TextField*>(getChildByName("musicField"));
			log("music moved %d", dynamic_cast<Slider*>(sender)->getPercent());
			musicField->setString(std::to_string( dynamic_cast<Slider*>(sender)->getPercent()));
			break;
		}
		default:
			break;
		}
	});
	music->setPosition(Vec2(540,530));
	this->addChild(music, 100,"music");

	auto musicField = TextField::create("", FONT_MARKER_FELT, 30);
	musicField->setString("100");
	musicField->setPosition(Vec2(800, 530));
	musicField->setColor(Color3B::BLACK);
	musicField->addEventListener([&](Ref* sender, TextField::EventType type) {
		if (type == TextField::EventType::INSERT_TEXT) {
			auto musicField = dynamic_cast<TextField*>(sender);
			auto music = dynamic_cast<Slider*>(getChildByName("music"));
			log(musicField->getString().c_str());
			std::stringstream input(dynamic_cast<TextField*>(sender)->getString());
			int temp = 0;
			input >> temp;
			if(input.fail()) {
				musicField->setString("0");
				music->setPercent(0);
			}else {
				if (temp > 100)
					temp = 100;
				if (temp < 0)
					temp = 0;
				musicField->setString(std::to_string(temp));
				music->setPercent(temp);
			}
		}
	});
	this->addChild(musicField, 100,"musicField");

	//音效sound
	auto soundLabel = Label::createWithTTF("sound:", FONT_MARKER_FELT, 40);
	soundLabel->setPosition(Vec2(240, 460));
	soundLabel->setColor(Color3B::BLACK);
	addChild(soundLabel, 100);
	
	auto sound = Slider::create();
	sound->loadBarTexture("Slider_Back.png");
	sound->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	sound->loadProgressBarTexture("Slider_PressBar.png");
	sound->setScale9Enabled(true);
	sound->setContentSize(Size(420, 20));
	sound->setMaxPercent(100);
	sound->setPercent(100);
	sound->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED: {
			auto musicField = dynamic_cast<TextField*>(getChildByName("soundField"));
			log("sound moved %d", dynamic_cast<Slider*>(sender)->getPercent());
			musicField->setString(std::to_string(dynamic_cast<Slider*>(sender)->getPercent()));
			break;
		}
		default:
			break;
		}
	});
	sound->setPosition(Vec2(540,460));
	this->addChild(sound, 999,"sound");

	auto soundField = TextField::create("", FONT_MARKER_FELT, 30);
	soundField->setString("100");
	soundField->setPosition(Vec2(800, 460));
	soundField->setColor(Color3B::BLACK);
	soundField->addEventListener([&](Ref* sender, TextField::EventType type) {
		if (type == TextField::EventType::INSERT_TEXT) {
			auto soundField = dynamic_cast<TextField*>(sender);
			auto music = dynamic_cast<Slider*>(getChildByName("sound"));
			log(soundField->getString().c_str());
			std::stringstream input(dynamic_cast<TextField*>(sender)->getString());
			int temp = 0;
			input >> temp;
			if (input.fail()) {
				soundField->setString("0");
				music->setPercent(0);
			}
			else {
				if (temp > 100)
					temp = 100;
				if (temp < 0)
					temp = 0;
				soundField->setString(std::to_string(temp));
				music->setPercent(temp);
			}
		}
	});
	this->addChild(soundField, 100, "soundField");
}

void OptionsScene::creatCheckBox()
{
	//显示帧率
	auto FPSLabel = Label::createWithTTF("Show FPS:", FONT_MARKER_FELT, 40);
	FPSLabel->setPosition(Vec2(260, 200));
	FPSLabel->setColor(Color3B::BLACK);
	addChild(FPSLabel, 100);

	auto FPSBox = CheckBox::create("CheckBox_Disable.png", "CheckBoxNode_Disable.png");
	FPSBox->setPosition(Vec2(400, 200));
	FPSBox->setContentSize(Size(50, 50));
	//这里的SelectedState有点反直觉,与图像上的是否选择相反
	FPSBox->setSelectedState(global_->displayStats);
	FPSBox->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED: {
			bool flag = dynamic_cast<CheckBox*>(getChildByName("FPSBox"))->getSelectedState();
			log(std::string(flag ? "false" : "true").c_str());
			Director::getInstance()->setDisplayStats(!flag);
			global_->displayStats = !global_->displayStats;
			break;
		}
		default:
			break;
		}
	});

	this->addChild(FPSBox,100,"FPSBox");
}

void OptionsScene::creatButton()
{
	TTFConfig config("fonts/Marker Felt.ttf", 30);
	//back btn
	auto back = ui::Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
	back->ignoreContentAdaptWithSize(true);
	back->setScale9Enabled(true);
	back->setContentSize(Size(200, 50));
	auto label = Label::createWithTTF(config, "back");
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
}
