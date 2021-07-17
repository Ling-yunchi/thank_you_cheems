#include "Cheems.h"
#include "Base/ConstValue.h"

bool Cheems::init()
{
	AnimationSprite::initWithNameAndSize("cheems", Size(220, 300));
	getPhysicsBody()->setTag(CheemsTag);
	getPhysicsBody()->setCategoryBitmask(CheemsCateoryBitmask);
	getPhysicsBody()->setCollisionBitmask(CheemsCollisionBitmask);
	getPhysicsBody()->setContactTestBitmask(CheemsContactTestBitmask);
	setScale(0.1);

	auto attackNode = Node::create();
	attackArea = PhysicsBody::createBox(Size(30,30));
	attackNode->setPhysicsBody(attackArea);
	attackNode->setPosition(-30,0);
	attackArea->setTag();
	attackArea->setCategoryBitmask();
	attackArea->setCollisionBitmask();
	attackArea->setContactTestBitmask();

	addChild(attackNode);
	
	return true;
}


void Cheems::attack()
{
	if (isattack != true)
	{
		AnimationSprite::attack();
		isattack = true;
		attackArea->setCategoryBitmask();
		attackArea->setCollisionBitmask();
		attackArea->setContactTestBitmask();
	}
}

int Cheems::getHP()
{
	return HP;
}


Cheems* Cheems::create()
{
	auto cheems = new (std::nothrow) Cheems();
	if (cheems && cheems->init()) {
		cheems->autorelease();
		return cheems;
	}
	CC_SAFE_FREE(cheems);

	return nullptr;
}

void Cheems::hurt()
{
	ishurt = true;
	AnimationSprite::hurt();
	HP -= 1;
}

void Cheems::updateTimer()
{
	if (isattack)
		timerAttack += 1;

	if (timerAttack == 100)
	{
		isattack = false;
		attackArea->setCategoryBitmask(0);
		attackArea->setCollisionBitmask(0);
		attackArea->setContactTestBitmask(0);
		timerAttack = 0;
	}

	if (ishurt)
		timerHurt += 1;
	 
	if (timerHurt == 120)
	{
		ishurt = false;
		timerHurt = 0;
	}
}

bool Cheems::getIsattact()
{
	return isattack;
}