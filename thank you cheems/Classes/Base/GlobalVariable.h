/**
 * 全局变量存储 
 */
#pragma once
#include <string>

#include "UserInformation.h"

/**
 * \brief 字体Maker Felt的路径
 */
#define FONT_MARKER_FELT "fonts/Marker Felt.ttf"

class Global
{
public:
	static Global* getInstance();
	bool displayStats;
	UserInformation* userInfo_;
	std::string saveName;
private:
	Global();
	~Global();
	//单例模式
	static  Global* instance_;
};

