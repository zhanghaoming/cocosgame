#ifndef __FIRST_WAR_SCENE
#define __FIRST_WAR_SCENE

#include"cocos2d.h"
USING_NS_CC;

class FirstWar :public Scene
{	
protected:
	Sprite* hero;
	Sprite* enemy;

	Sprite* uniqueskill;
	Sprite* background;

	Sprite* _skill1;
	Sprite* _skill2;
	Sprite* _skill3;
	
	LabelTTF* lifeline_hero;
	LabelTTF* lifeline_enemy;
	LabelTTF* Tips_hero;
	LabelTTF* Tips_enemy;

	double hero_life;
	double hero_attack;
	double hero_armor;

	double enemy_life;
	double enemy_attack;
	double enemy_armor;

	bool hasArmor;
	bool hasBlade;
	bool hasUniqueskill;

	int isFightRun;

	bool isKey;//键盘交互是否可用

	bool enemysturn;//标志着敌人是否可以执行动作
public:

	virtual bool init();

	virtual void update(float dt);

	CREATE_FUNC(FirstWar);

	void propertyinit(double life, double attack, double armor,bool DrinkerBlade,bool KingBlade,bool Uniqueskill);

	//战斗逻辑函数
	void NormalHit(bool ishero);

	void CrazyHit();

	void AttackRise();

	virtual void UniqueSkill();

	void setisFightRun(float dt)
	{
		isKey = true;
	}

	void setUniqueUnvisible(float dt);

	void Death(float dt);

};

#endif