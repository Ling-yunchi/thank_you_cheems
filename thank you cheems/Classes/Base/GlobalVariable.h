/**
 * ȫ�ֱ����洢 
 * @author wr
 */
#pragma once
#include "UserInformation.h"

/**
 * \brief ����Maker Felt��·��
 */
#define FONT_MARKER_FELT "fonts/Marker Felt.ttf"

class Global
{
public:
	static Global* getInstance();
private:
	Global();
	~Global();
	//����ģʽ
	static  Global* instance_;
	UserInformation* userInfo_;
};

