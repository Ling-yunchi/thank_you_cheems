/**
 * ȫ�ֱ����洢 
 */
#pragma once
#include <string>

#include "UserInformation.h"

/**
 * \brief ����Maker Felt��·��
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
	//����ģʽ
	static  Global* instance_;
};

