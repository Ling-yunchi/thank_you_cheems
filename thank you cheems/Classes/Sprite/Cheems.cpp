#include "Cheems.h"
#include "Base/ConstValue.h"

bool Cheems::init()
{
	HP = 3;
	
	AnimationSprite::initWithNameAndSize("cheems", Size(220, 300));
	getPhysicsBody()->setTag(CheemsTag);
	getPhysicsBody()->setCategoryBitmask(CheemsCateoryBitmask);
	getPhysicsBody()->setCollisionBitmask(CheemsCollisionBitmask);
	getPhysicsBody()->setContactTestBitmask(CheemsContactTestBitmask);
	setScale(0.1);


	return true;
}

bool Cheems::CheemsAttact(int directon, std::list<Monster*> &monsters)
{
	AnimationSprite::attack();
	isattack = true;
	for (auto it = monsters.begin(); it != monsters.end();) {
		if (directon == 1)
		{
			Rect RightAttact(this->getPositionX() + 22, this->getPositionY(), 30, 30);
			Rect soybean((*it)->getPositionX(), (*it)->getPositionY(), 60, 39);
			
			if (RightAttact.intersectsRect(soybean))
				monsters.erase(it++);
			else
				it++;
		}
		else if (directon == -1)
		{
			Rect LeftAttact(this->getPositionX() - 30, this->getPositionY(), 30, 30);
			Rect soybean((*it)->getPositionX(), (*it)->getPositionY(), 60, 39);
			
			if (LeftAttact.intersectsRect(soybean))
				monsters.erase(it++);
			else
				it++;
		}
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
	if(ishurt!=true) {
		ishurt = true;
		AnimationSprite::hurt();
		HP -= 1;
	}
}

void Cheems::updateTimer()
{
	if (isattack)
		timerAttack += 1;

	if (timerAttack == 100)
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