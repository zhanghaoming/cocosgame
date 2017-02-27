#include"Equipment.h"
bool Equipment::init()
{
	_inMap = Sprite::create("shoes.png");
	this->addChild(_inMap);
	hasTaken = false;
	this->scheduleUpdate();
	return true;
}
void Equipment::update(float dt)
{
	if (hasTaken == true)
		this->setVisible(false);
}
bool Equipment::isCollideWithHero(hero* m_hero)
{
	Rect heroRect = m_hero->getBoundingBox();
	Point equipmentPos = this->getPosition();
	if (heroRect.containsPoint(equipmentPos))
	{
		hasTaken = true;
	}
	return heroRect.containsPoint(equipmentPos);
}