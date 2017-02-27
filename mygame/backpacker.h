#ifndef BACKPACKER_SCENE_H
#define BACKPACKER_SCENE_H
#include"cocos2d.h"
USING_NS_CC;
  /////////////////////////
 ///������Ϸ�еı�������//
/////////////////////////
class backpacker :public Scene
{
private:
	//��Ʒ�Ƿ�ӵ��
	bool hasShoes;
	bool hasArmor;
	bool hasBlade;
	bool hasUniqueSkill;

	Sprite* _Shoes;
	Sprite* _Armor;
	Sprite* _Blade;

	Sprite* _skill1;
	Sprite* _skill2;
	Sprite* _skill3;

public:
	virtual bool init();

	CREATE_FUNC(backpacker);

	void setPackContent(bool shoes, bool armor, bool blade, bool uniqueskill);

	virtual void update(float dt);
};

#endif