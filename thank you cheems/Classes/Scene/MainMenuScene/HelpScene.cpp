#include "HelpScene.h"

#include "ui/UIButton.h"

Scene* HelpScene::createScene()
{
	return HelpScene::create();
}

bool HelpScene::init()
{
	if(!Scene::init())
		return false;

	visibleSize_ = Director::getInstance()->getVisibleSize();
	auto startBackground = Sprite::create("bg169.jpg");
	startBackground->setPosition(Vec2(visibleSize_.width / 2, visibleSize_.height / 2));
	float winw = visibleSize_.width; //获取屏幕宽度
	float winh = visibleSize_.height;//获取屏幕高度
	float spx = startBackground->getTextureRect().getMaxX();
	float spy = startBackground->getTextureRect().getMaxY();
	startBackground->setScaleX(winw / spx); //设置精灵宽度缩放比例
	startBackground->setScaleY(winh / spy);
	this->addChild(startBackground, 1);
	
	createLabel();
	createButton();
	
	return true;
}

void HelpScene::createButton()
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
	back->setPosition(Vec2(540, 70));
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

void HelpScene::createLabel()
{
	TTFConfig ttfConfig("fonts/Marker Felt.ttf", 100);
	//添加标题
	auto title = Label::createWithTTF(ttfConfig, "HELP");
	title->enableShadow();
	addChild(title, 9999);
	title->setPosition(Vec2(visibleSize_.width / 2, visibleSize_.height - 100));

	//填加帮助文本
	ttfConfig.fontSize = 45;
	auto helpText = Label::createWithTTF(ttfConfig, 
		"W, S, A, D control up and down left and right moving \nSPACE can also control jumping \nJ key attack \nESC key pause \n\n                                                        qwqq");
	helpText->setColor(Color3B::BLACK);
	addChild(helpText, 9999);
	helpText->setPosition(Vec2(visibleSize_.width / 2, visibleSize_.height-350));
}

