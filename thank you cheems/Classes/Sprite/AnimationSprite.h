/*
 * 控制运动物体动画显示的基类
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

	//动画调用函数
	void hurt();
	void move(int dir);
	void jump();
	void down();				//落地时调用
	void attack();
	void die();
	void updateAnimation();		//用于在播放完完整播放的动画后回到普通状态
	void updatePosition();
	int getDir();

	bool isDie() const { return isDieComplete_; }

	//运动变量
	float speedX_;
	float jumpHeight_;

private:
	dragonBones::CCFactory* factory_;
	dragonBones::CCArmatureDisplay* armatureDisplay_;
	dragonBones::Animation* animation_;


	/**
	 * 动画优先级:
	 * die > hurt > jump > attack > move >normal
	 */
	dragonBones::AnimationState* attackState_;
	dragonBones::AnimationState* moveState_;

	//状态变量
	bool isJumpA_;		//正在跳跃
	bool isJumpB_;		//是否落地
	bool isAttackA_;	//正在攻击
	bool isAttackB_;	//attack动画是否播放完毕
	bool isHurt_;		//是否需要播放hurt动画
	bool isDie_;		//die动画是否播放
	bool isDieComplete_;//die动画是否播放完毕
	int moveDir_;		//运动方向



	void animationEventHandler_(cocos2d::EventCustom* event);	//检测动画是否播放完毕,并做后续处理
	//void frameEventHandler_(cocos2d::EventCustom* event);
};
