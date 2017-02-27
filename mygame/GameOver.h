#ifndef __OVER_SCENE_H__
#define __OVER_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class Over :public Scene
{
protected:
	Sprite* background;
public:
	CREATE_FUNC(Over);

	virtual void backgrondinit();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

};

class Win :public Over
{
public:
	CREATE_FUNC(Win);

	virtual void backgrondinit();
};

class Help:public Over
{
public:

	CREATE_FUNC(Help);

	virtual bool init();

};
#endif