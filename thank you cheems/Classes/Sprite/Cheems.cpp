#include "Cheems.h"
#include "Base/ConstValue.h"

bool Cheems::init()
{
	AnimationSprite::initWithNameAndSize("cheems", Size(220, 300));
	setTag(CheemsTag);
	getPhysicsBody()->setCategoryBitmask(CheemsCateoryBitmask);
	getPhysicsBody()->setCollisionBitmask(CheemsCollisionBitmask);
	getPhysicsBody()->setContactTestBitmask(CheemsContactTestBitmask);
	setScale(0.1);

	return true;
}

bool Cheems::CheemsAttact(int directon, std::list<Monster> monsters)
{
	AnimationSprite::attack();
	isattack = true;
	if (directon == 1)
	{
		Rect RightAttact(this->getPositionX() + 22,this->getPositionY(),30,30);
		Rect soybean(monster_x, monster_y, 60, 39);
		return RightAttact.intersectsRect(soybean);
	}
	else if (directon == -1)
	{
		Rect LeftAttact(this->getPositionX() - 30, this->getPositionY(), 30, 30);
		Rect soybean(monster_x, monster_y, 60, 39);
		return LeftAttact.intersectsRect(soybean);
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
	if(isattack)
		timerAttack += 1;
	
	if (timerAttack == 100 )
	{
		isattack = false;
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