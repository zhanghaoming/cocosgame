#ifndef __FIRST_SCENE_H__
#define __FIRST_SCENE_H__

#include"cocos2d.h"
#include"hero.h"
#include"enemy.h"
#include"Equipment.h"
USING_NS_CC;

class First : public cocos2d::Layer
{
private:
	//隐藏在背景下的地图
	TMXTiledMap* _map;

	//添加在地图中的英雄，敌人及道具
	hero* _hero;
	enemy* _enemy1;
	enemy* _enemy2;
	enemy* _enemy3;
	boss* _boss;
	Equipment* _shoes;

	//英雄数据
	double hero_life;
	double hero_attack;
	double hero_armor;
	double hero_speed;
	bool hasShoes;
	bool hasArmor;
	bool hasBlade;
	bool hasUniqueskill;

	//背包提示
	Label* packTips;
	bool openbackpacker;
	
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	void backpackerCallback(cocos2d::Ref* pSender);

	virtual void update(float dt);

	double getSpeed();

	CREATE_FUNC(First);
};
#endif