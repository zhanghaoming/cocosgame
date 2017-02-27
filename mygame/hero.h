#ifndef __HERO_H__
#define __HERO_H__

#include"cocos2d.h"
USING_NS_CC;

class hero :public Node
{
private:
	Sprite* _hero;
public:
	virtual bool init();

	Rect getBoundingBox();

	CREATE_FUNC(hero);
};


#endif