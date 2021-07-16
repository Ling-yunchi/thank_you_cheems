#include "AnimationSprite.h"

#include "cocos2dx/CCFactory.h"

AnimationSprite* AnimationSprite::create(const std::string& animationName, const Size& size)
{
	AnimationSprite* sprite = new (std::nothrow) AnimationSprite();
	if (sprite && sprite->initWithNameAndSize(animationName, size)) {
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}

AnimationSprite::AnimationSprite()
	:factory_(dragonBones::CCFactory::getFactory()),
	armatureDisplay_(nullptr),
	isJumpA_(false),
	isJumpB_(true),
	isAttackA_(false),
	isAttackB_(true),
	isHurt_(false),
	moveState_(nullptr),
	attackState_(nullptr),
	speedX_(200),
	isDie_(false),
	isDieComplete_(false),
	jumpHeight_(650),
	moveDir_(0)
{
}

bool AnimationSprite::initWithNameAndSize(std::string animationName, Size size)
{	
	armatureDisplay_ = factory_->buildArmatureDisplay(animationName);
	if (!armatureDisplay_)
		return false;
	animation_ = armatureDisplay_->getAnimation();
	animation_->play("normal");
	addChild(armatureDisplay_);

	//添加刚体
	PhysicsBody* body = PhysicsBody::createBox(size);
	body->setRotationEnable(false);
	body->setContactTestBitmask(1);
	setPhysicsBody(body);

	//添加事件监听器
	armatureDisplay_->getEventDispatcher()->setEnabled(true);
	armatureDisplay_->getEventDispatcher()->addCustomEventListener(dragonBones::EventObject::FADE_IN_COMPLETE, std::bind(&AnimationSprite::animationEventHandler_, this, std::placeholders::_1));
	armatureDisplay_->getEventDispatcher()->addCustomEventListener(dragonBones::EventObject::FADE_OUT_COMPLETE, std::bind(&AnimationSprite::animationEventHandler_, this, std::placeholders::_1));
	armatureDisplay_->getEventDispatcher()->addCustomEventListener(dragonBones::EventObject::COMPLETE, std::bind(&AnimationSprite::animationEventHandler_, this, std::placeholders::_1));

	return true;
}

dragonBones::CCArmatureDisplay* AnimationSprite::getArmature()
{
	return armatureDisplay_;
}

void AnimationSprite::hurt()
{
	if (isDie_)
		return;

	if (!isHurt_) {
		isHurt_ = true;
		animation_->play("hurt");

		updateAnimation();
	}
}

void AnimationSprite::move(int dir)
{
	if (moveDir_ == dir)
		return;

	moveDir_ = dir;
	updateAnimation();
}

void AnimationSprite::jump()
{
	if (isDie_ || isHurt_)
		return;

	if (isJumpB_) {
		isJumpA_ = true;
		isJumpB_ = false;

		animation_->play("jump", 1);

		moveState_ = nullptr;
	}
}

void AnimationSprite::down()
{
	isJumpB_ = true;
}

void AnimationSprite::attack()
{
	if (isDie_ || isHurt_ || isJumpA_)
		return;

	if (isAttackB_) {
		isAttackA_ = true;
		isAttackB_ = false;

		attackState_ = animation_->fadeIn("attack");
		attackState_->resetToPose = false;
		attackState_->autoFadeOutTime = attackState_->fadeTotalTime;
	}
}

void AnimationSprite::die()
{
	isDie_ = true;
	animation_->play("die");
}

void AnimationSprite::updateAnimation()
{
	if (isDie_ || isHurt_ || isJumpA_ || isAttackA_)//不需要更新动画,需要播放完毕
		return;

	if (moveDir_ == 0)
	{
		animation_->fadeIn("normal", -1.0f, -1, 0)
			->resetToPose = false;
		moveState_ = nullptr;
	}
	else
	{
		setScaleX(-moveDir_ * abs(getScaleX()));
		if (!moveState_)
		{
			moveState_ = animation_->fadeIn("move", -1.0f, -1, 0);
			moveState_->resetToPose = false;
		}
	}
}

void AnimationSprite::updatePosition()
{
	if (!isHurt_) {
		if (moveDir_ != 0) {
			//runAction(MoveBy::create(0.0001, Vec2(moveDir_ * speedX_, 0)));
			getPhysicsBody()->setVelocity(Vec2(moveDir_ * speedX_, getPhysicsBody()->getVelocity().y));
		}
		if (isJumpA_) {
			//runAction(JumpBy::create(0.55, Vec2(0, jumpHeight_), jumpHeight_, 1));
			getPhysicsBody()->setVelocity(Vec2(getPhysicsBody()->getVelocity().x, jumpHeight_));
			isJumpA_ = false;
		}
	}
}

int AnimationSprite::getDir()
{
	return moveDir_;
}

void AnimationSprite::animationEventHandler_(cocos2d::EventCustom* event)
{
	const auto eventObject = static_cast<dragonBones::EventObject*>(event->getUserData());
	if (eventObject->type == dragonBones::EventObject::COMPLETE)
	{
		if (eventObject->animationState->getName() == "die") {
			isDie_ = true;
		}
		if (eventObject->animationState->getName() == "hurt") {
			isHurt_ = false;
			updateAnimation();
		}
		if (eventObject->animationState->getName() == "jump") {
			isJumpA_ = false;
			moveState_ = nullptr;
			updateAnimation();
		}
	}
	if (eventObject->type == dragonBones::EventObject::FADE_OUT_COMPLETE)
	{
		if (eventObject->animationState->getName() == "attack")
		{
			isAttackA_ = false;
			isAttackB_ = true;
			attackState_ = nullptr;
			updateAnimation();
		}
	}
}
