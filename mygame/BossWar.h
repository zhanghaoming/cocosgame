#ifndef BOSSWAR_H
#define BOSSWAR_H
#include"cocos2d.h"
#include"FirstWar.h"
USING_NS_CC;
//与boss的战斗场景，继承自firstwar场景，对部分技能的使用、效果的执行进行了改动
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