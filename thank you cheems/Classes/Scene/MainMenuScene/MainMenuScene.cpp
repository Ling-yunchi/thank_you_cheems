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
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto startBackground = Sprite::create("startBackground.jpg");
    startBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    float winw = visibleSize.width; //获取屏幕宽度
    float winh = visibleSize.height;//获取屏幕高度
    float spx = startBackground->getTextureRect().getMaxX();
    float spy = startBackground->getTextureRect().getMaxY();
    startBackground->setScaleX(winw / spx); //设置精灵宽度缩放比例
    startBackground->setScaleY(winh / spy);
    this->addChild(startBackground, 1);

    creatMenu();
    petalParticle();

    return true;
}

void MainMenuScene::creatMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
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

    auto startItem = MenuItemLabel::create(start, [&](Ref* sender) {
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
        OptionsScene_ = OptionsScene::createScene();
        Director::getInstance()->pushScene(OptionsScene_);
    });
    auto closeItem = MenuItemLabel::create(close, [&](Ref* sender) {
        log("close");
        Director::getInstance()->end();
    });

    auto menu = Menu::create(startItem, helpItem, optionItem, closeItem, nullptr);
    menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 300));
    int pitch = 80;
    startItem->setPosition(Vec2(0, 0));
    helpItem->setPosition(Vec2(0, -pitch));
    optionItem->setPosition(Vec2(0, -2 * pitch));
    closeItem->setPosition(Vec2(0, -3 * pitch));
    addChild(menu, 9999);
}

void MainMenuScene::petalParticle()
{
    //CCParticleSystem* huaban1 = CCParticleSnow::create();
    //huaban1->setTexture(CCTextureCache::sharedTextureCache()->addImage("huaban1.png"));
    //huaban1->setSpeed(50);
    //huaban1->setGravity(Vec2(-20,-9.8));
    //huaban1->setScale(2);
    //addChild(huaban1,999);

    CCParticleSystem* huaban2 = CCParticleSnow::create();
    huaban2->setTexture(CCTextureCache::sharedTextureCache()->addImage("huaban2.png"));
    huaban2->setSpeed(50);
    huaban2->setGravity(Vec2(-20, -9.8));
    huaban2->setScale(2);
    addChild(huaban2, 999);

    CCParticleSystem* huaban3 = CCParticleSnow::create();
    huaban3->setTexture(CCTextureCache::sharedTextureCache()->addImage("huaban3.png"));
    huaban3->setSpeed(50);
    huaban3->setGravity(Vec2(-20, -9.8));
    huaban3->setScale(2);
    addChild(huaban3, 999);
}
