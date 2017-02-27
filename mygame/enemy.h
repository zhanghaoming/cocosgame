#include"cocos2d.h"
#include"hero.h"
USING_NS_CC;

class enemy :public Node
{
protected:	
	Sprite* _monster;

	bool isFightRun;
public:
	virtual bool init();

	virtual bool isCollideWithHero(hero* m_hero);

	CREATE_FUNC(enemy);

	bool getisFightRun();

	void setisFightRun();

	virtual void update(float dt);

}; 

class boss :public enemy//boss�̳���enemy�࣬��enemy��ǿ����
{
public:
	virtual bool init();

	Rect getBoundingBox();

	virtual bool isCollideWithHero(hero* m_hero);

	CREATE_FUNC(boss);
};

