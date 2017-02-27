#include"enemy.h"
#include"hero.h"
#include"FirstWar.h"

bool enemy::init()
{
	_monster = Sprite::create("enemy.png");
		this->addChild(_monster);
	isFightRun = false;
	this->scheduleUpdate();
	return true;
}

bool enemy::isCollideWithHero(hero* m_hero)
{
	Rect heroRect = m_hero->getBoundingBox();
	Point monsterPos = this->getPosition();
	return heroRect.containsPoint(monsterPos);
}


bool enemy::getisFightRun()
{
	return isFightRun;
}

void enemy::setisFightRun()
{
	isFightRun = true;
}

void enemy::update(float dt)
{

	if (isFightRun == true)
		this->setVisible(false);
}


bool boss::init()
{
	_monster = Sprite::create("boss.png");
	this->addChild(_monster);
	isFightRun = false;
	this->scheduleUpdate();
	return true;
}

Rect boss::getBoundingBox(){
	Size spriteSize =_monster->getContentSize();
	Point Pos = this->getPosition();
	return CCRectMake(
		Pos.x - spriteSize.width / 2,
		Pos.y - spriteSize.height / 2,
		spriteSize.width,
		spriteSize.height
		);
}

bool boss::isCollideWithHero(hero* m_hero)
{
	return (this->getBoundingBox().containsPoint(m_hero->getPosition()));
}