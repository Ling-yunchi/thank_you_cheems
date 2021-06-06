#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Base/Save.h"
#include <array>

const int saveNumMax = 4;

class SaveChooseScene : public cocos2d::Scene
{
private:
	void file();
	void creatButton();
	std::array<Save, saveNumMax> saves;
	int saveCount;
	std::array<cocos2d::ui::Button*, saveNumMax+1> buttons_;
public:
	static cocos2d::Scene* createScene();

	bool init() override;

	CREATE_FUNC(SaveChooseScene);
};

