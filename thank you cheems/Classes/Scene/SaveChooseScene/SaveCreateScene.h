/**
 * 创建新存档的界面
 * @author wr
 */
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class SaveCreateScene :public Scene
{
public:
	static  cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(SaveCreateScene);
private:
	void createBackground();
	void creatEditBox();
	void creatButton();
	void fileControl();
};

