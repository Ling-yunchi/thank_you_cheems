/**
 * 确定选择存档的界面
 * @author wr
 */
#pragma once
#include "cocos2d.h"
#include "Base/Save.h"
using namespace cocos2d;

class SaveChooseConfirmScene :public Scene
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(SaveChooseConfirmScene);
private:
	Save save;
	void creatLabel();
	void createBackground();
	void creatButton();
	void fileRead();
	void fileWrite();
};

