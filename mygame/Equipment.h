#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "cocos2d.h"
#include"hero.h"


USING_NS_CC;
//equipment����һ����ʰȡ���ߵ���
class Equipment :public Node
{
private:
	Sprite* _inMap;//ͼƬ
	bool hasTaken;//�Ƿ�ʰȡ
public:
	virtual bool init();
	virtual void update(float dt);
	bool isCollideWithHero(hero* m_hero);//��ײ����
	CREATE_FUNC(Equipment);
};
#endif