/*
 * �����˶����嶯����ʾ�Ļ���
 */
#pragma once

#include <cocos2d.h>

#include "cocos2dx/CCArmatureDisplay.h"
#include "cocos2dx/CCFactory.h"

using namespace cocos2d;

class AnimationSprite : public Node
{
public:
	static AnimationSprite* create(const std::string& animationName, const Size& size);

	AnimationSprite();
	bool initWithNameAndSize(std::string animationName, Size size);

	dragonBones::CCArmatureDisplay* getArmature();

	//�������ú���
	void hurt();
	void move(int dir);
	void jump();
	void down();				//���ʱ����
	void attack();
	void die();
	void updateAnimation();		//�����ڲ������������ŵĶ�����ص���ͨ״̬
	void updatePosition();
	int getDir();

	bool isDie() const { return isDieComplete_; }

	//�˶�����
	float speedX_;
	float jumpHeight_;

private:
	dragonBones::CCFactory* factory_;
	dragonBones::CCArmatureDisplay* armatureDisplay_;
	dragonBones::Animation* animation_;


	/**
	 * �������ȼ�:
	 * die > hurt > jump > attack > move >normal
	 */
	dragonBones::AnimationState* attackState_;
	dragonBones::AnimationState* moveState_;

	//״̬����
	bool isJumpA_;		//������Ծ
	bool isJumpB_;		//�Ƿ����
	bool isAttackA_;	//���ڹ���
	bool isAttackB_;	//attack�����Ƿ񲥷����
	bool isHurt_;		//�Ƿ���Ҫ����hurt����
	bool isDie_;		//die�����Ƿ񲥷�
	bool isDieComplete_;//die�����Ƿ񲥷����
	int moveDir_;		//�˶�����



	void animationEventHandler_(cocos2d::EventCustom* event);	//��⶯���Ƿ񲥷����,������������
	//void frameEventHandler_(cocos2d::EventCustom* event);
};
