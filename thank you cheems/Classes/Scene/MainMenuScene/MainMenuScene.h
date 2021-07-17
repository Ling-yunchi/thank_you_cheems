/**
 * Ö÷²Ëµ¥³¡¾°
 */
#pragma once
#include "cocos2d.h"
#include <vector>
#include "Scene/SaveChooseScene/SaveChooseScene.h"
#include "OptionsScene.h"
#include "HelpScene.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(MainMenuScene);

private:
    Scene* chooseSaveScene_;
    Scene* OptionsScene_;
    Scene* helpScene_;

    void creatMenu();
    void petalParticle();
};
