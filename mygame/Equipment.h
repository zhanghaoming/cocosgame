#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "cocos2d.h"
#include"hero.h"


USING_NS_CC;
//equipment类是一个可拾取道具的类
class Equipment :public Node
{
private:
	Sprite* _inMap;//图片
	bool hasTaken;//是否被拾取
public:
	virtual bool init();
	virtual void update(float dt);
	bool isCollideWithHero(hero* m_hero);//碰撞函数
	CREATE_FUNC(Equipment);
};
#endif