#ifndef BOSSWAR_H
#define BOSSWAR_H
#include"cocos2d.h"
#include"FirstWar.h"
USING_NS_CC;
//��boss��ս���������̳���firstwar�������Բ��ּ��ܵ�ʹ�á�Ч����ִ�н����˸Ķ�
class BossWar :public FirstWar
{
private:
	bool hasCrazyHit;
public:
	virtual bool init();

	virtual void update(float dt);

	virtual void CrazyHit();

	virtual void UniqueSkill();

	void AmazingVitality();

	void Victory(float dt);

	CREATE_FUNC(BossWar);
};
#endif