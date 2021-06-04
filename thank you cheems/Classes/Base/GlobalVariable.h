/**
 * 全局变量存储 
 * @author wr
 */
#pragma once
#include "UserInformation.h"

/**
 * \brief 字体Maker Felt的路径
 */
#define FONT_MARKER_FELT "fonts/Marker Felt.ttf"

class Global
{
public:
	static Global* getInstance();
private:
	Global();
	~Global();
	//单例模式
	static  Global* instance_;
	UserInformation* userInfo_;
};

