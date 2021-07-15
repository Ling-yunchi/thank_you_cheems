/**
 * ÔÝÍ£³¡¾°
 * @author wr
 */
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class PauseScene :public Scene
{
public:
	static Scene* createScene();
	bool init() override;
	CREATE_FUNC(PauseScene);
private:
	void creatBg();
	void createMenu();
	
};

