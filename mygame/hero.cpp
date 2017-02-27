#include"hero.h"

bool hero::init()
{
	_hero = Sprite::create("hero.png");
	this->addChild(_hero);
	return true;
}

Rect hero::getBoundingBox(){ 
	Size spriteSize = _hero->getContentSize();
	Point heroPos = this->getPosition();
	return CCRectMake(
		heroPos.x - spriteSize.width / 2,
		heroPos.y - spriteSize.height / 2,
		spriteSize.width,
		spriteSize.height
		);
}