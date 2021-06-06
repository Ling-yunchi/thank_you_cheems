#include "SaveCreateScene.h"

#include <fstream>
#include <ui/UIEditBox/UIEditBox.h>

#include "SaveChooseScene.h"
#include "VisibleRect.h"
#include "Base/GlobalVariable.h"
#include "Base/Save.h"
#include "ui/UIButton.h"

cocos2d::Scene* SaveCreateScene::createScene()
{
	return SaveCreateScene::create();
}

bool SaveCreateScene::init()
{
	if (!Scene::init())
		return false;

	createBackground();
	creatEditBox();
	creatButton();
	
	return true;
}

void SaveCreateScene::createBackground()
{
	auto background = Sprite::create("bg1.jpeg");
	background->setPosition(VisibleRect::center());
	addChild(background, 1);

	auto widgetBackground = Sprite::create("widget_bg.png");
	widgetBackground->setOpacity(200);
	widgetBackground->setScale(0.7,0.5);
	widgetBackground->setPosition(Vec2(540,400));
	addChild(widgetBackground, 2);
}

void SaveCreateScene::creatEditBox()
{
	//БъЬт
	auto options = Label::createWithTTF("Create Save", FONT_MARKER_FELT, 50);
	options->setPosition(Vec2(540, 660));
	addChild(options, 100);

	auto editTitle = Label::createWithTTF("Enter Save Name:", FONT_MARKER_FELT, 40);
	editTitle->setPosition(Vec2(430, 520));
	editTitle->setColor(Color3B::BLACK);
	addChild(editTitle, 100);

	auto warning = Label::createWithTTF("Once input cannot be modified!", FONT_MARKER_FELT, 30);
	warning->setPosition(Vec2(460, 400));
	warning->setColor(Color3B::RED);
	addChild(warning, 100);

	//editBox
	auto editBox = ui::EditBox::create(Size(510, 60),"widget.png");
	editBox->setMaxLength(15);
	editBox->setFontColor(Color3B::BLACK);
	editBox->setText("Save Name");
	editBox->setPosition(Vec2(540, 450));
	addChild(editBox, 100,"editBox");
}

void SaveCreateScene::creatButton()
{
	TTFConfig config("fonts/Marker Felt.ttf", 40);

	//confirm btn
	auto confirm = ui::Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
	confirm->ignoreContentAdaptWithSize(true);
	confirm->setScale9Enabled(true);
	confirm->setContentSize(Size(400, 60));
	auto label = Label::createWithTTF(config, "confirm");
	label->setTextColor(Color4B::BLACK);
	confirm->setTitleLabel(label);
	confirm->setPosition(Vec2(540, 300));
	confirm->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			fileControl();
			break;
		default:
			break;
		}

	});
	addChild(confirm, 999);
	
	//back btn
	auto back = ui::Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
	back->ignoreContentAdaptWithSize(true);
	back->setScale9Enabled(true);
	back->setContentSize(Size(200, 50));
	config.fontSize = 30;
	auto label1 = Label::createWithTTF(config, "back");
	label1->setTextColor(Color4B::BLACK);
	back->setTitleLabel(label1);
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

void SaveCreateScene::fileControl()
{
	std::list<Save> saves;
	std::ifstream in("save.dat");
	while (in.peek() != EOF) {
		Save temp;
		in.read(reinterpret_cast<char*>(&temp), sizeof(Save));
		saves.push_back(temp);
	}
	in.close();

	auto editBox = dynamic_cast<ui::EditBox*>(getChildByName("editBox"));
	bool flag = false;
	char name[30];
	strcpy(name, editBox->getText());
	
	for (auto it = saves.begin(); it != saves.end(); it++) {
		if(strcmp(name,(*it).getName())==0) {
			flag = true;
			break;
		}
	}
	if (flag) {
		if (getChildByName("Duplicate") == nullptr) {
			auto warning = Label::createWithTTF("Duplicate name", FONT_MARKER_FELT, 30);
			warning->setPosition(Vec2(460, 350));
			warning->setColor(Color3B::RED);
			addChild(warning, 100, "Duplicate");
		}
	}
	else {
		std::ofstream saveFile("save.dat", std::ios::app);
		Save save(name);
		saveFile.write(reinterpret_cast<char*>(&save), sizeof(Save));
		saveFile.close();
		Director::getInstance()->replaceScene(SaveChooseScene::createScene());
	}
}
