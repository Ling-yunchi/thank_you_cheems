/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainMenuScene.h"

#include "SimpleAudioEngine.h"
#include "Scene/SaveChooseScene/SaveChooseScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

bool MainMenuScene::init()
{
    if ( !Scene::init() )
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto startBackground = Sprite::create("startbg169.jpg");
    startBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    float winw = visibleSize.width; //获取屏幕宽度
    float winh = visibleSize.height;//获取屏幕高度
    float spx = startBackground->getTextureRect().getMaxX();
    float spy = startBackground->getTextureRect().getMaxY();
    startBackground->setScaleX(winw / spx); //设置精灵宽度缩放比例
    startBackground->setScaleY(winh / spy);
    this->addChild(startBackground,1);

    TTFConfig ttfConfig("fonts/Marker Felt.ttf", 100);
	//add title
    auto title = Label::createWithTTF(ttfConfig, "thank you, cheems!");
	title->enableShadow();
    addChild(title, 9999);
    title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 130));
	
    ttfConfig.fontSize = 50;
    auto start = Label::createWithTTF(ttfConfig, "start");
    auto help = Label::createWithTTF(ttfConfig, "help");
    auto option = Label::createWithTTF(ttfConfig, "option");
    auto close = Label::createWithTTF(ttfConfig, "close");

    start->enableShadow();
    help->enableShadow();
    option->enableShadow();
    close->enableShadow();

    auto startItem = MenuItemLabel::create(start, [&](Ref* sender){
	    log("start");
        chooseSaveScene_ = SaveChooseScene::createScene();
        Director::getInstance()->pushScene(chooseSaveScene_);
    });
    auto helpItem = MenuItemLabel::create(help, [&](Ref* sender) {
	    log("help");
        helpScene_ = HelpScene::createScene();
        Director::getInstance()->pushScene(helpScene_);
    });
    auto optionItem = MenuItemLabel::create(option, [&](Ref* sender) {
	    log("options");
    	//TODO OptionScene
    });	
    auto closeItem = MenuItemLabel::create(close, [&](Ref* sender) {
	    log("close");
    	Director::getInstance()->end();
    });

    auto menu = Menu::create(startItem,helpItem,optionItem,closeItem, nullptr);
    menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 300));
    int pitch = 80;
    startItem->setPosition(Vec2(0,0));
    helpItem->setPosition(Vec2(0, -pitch));
    optionItem->setPosition(Vec2(0, -2*pitch));
    closeItem->setPosition(Vec2(0, -3*pitch));
    addChild(menu, 9999);

	
    return true;
}

