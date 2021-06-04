/*
 * @author wr
 */
#pragma once
#include "cocos2d.h"
#include "GlobalVariable.h"

using namespace cocos2d;

class Dialog :public LayerColor
{
public:
	//������������
	static EventListenerTouchOneByOne* creatTouchListener(Sprite* sprite);
	
	//����������
	virtual void setMouseListener(EventListenerMouse* listener);

protected:
	//������ǩ
	virtual Label* label(
		const std::string& name, 
		const float& fontSize,
		Vec2& vec2 = Vec2(0, 0),
		const float& space = 0,
		const Color3B& color = Color3B::BLACK,
		const float &scale = 1);
	
	//������ť�ϵı�ǩ
	virtual void createLabel(
		Sprite* sprite, 
		MenuItemImage* MenuItem, 
		const std::string& name,
		Vec2& vec2, float& fontsize, 
		const float& space = 0, 
		const Color3B& color = Color3B::GREEN);
	
	//�������β�
	virtual void createShieldLayer(Node* node);
	
	//ɾ����
	virtual void deleteDialog() {}
	
	//�����������Ƿ����
	virtual void setMouseListenerEnable(bool isEnable = true);
public:
	Dialog();
	~Dialog();

protected:
	EventListenerMouse* _mouseListener;

private:
	Vec2 _phasePosition; // ���λ��
	EventListenerTouchOneByOne* _shieldListener;
	Global* global_;
};

