#include"First.h"
#include"FirstWar.h"
#include"BossWar.h"
#include"backpacker.h"
#include"cmath"
#include"SimpleAudioEngine.h"

using namespace CocosDenshion;

Scene* First::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = First::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool First::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SimpleAudioEngine::getInstance()->preloadEffect("getnew.wav");
	
	auto background = Sprite::create("background.jpg");
	background->setPosition(visibleSize / 2);
	this->addChild(background);



	//将主角添加至地图
	_hero = hero::create();
	_hero->setPosition(visibleSize.width / 2 - 200, 300);
	this->addChild(_hero);

	//玩家属性初始化
	hero_attack = 80;
	hero_armor = 50;
	hero_life = 500;
	hero_speed = 60;
	hasShoes = false;
	hasArmor= false;
	hasBlade = false;
	hasUniqueskill = false;
	openbackpacker = false;




	//可拾取装备的添加
	_shoes = Equipment::create();
	_shoes->setPosition(visibleSize.width/2-100,100);
	this->addChild(_shoes);

	//敌人的添加
	_enemy1 = enemy::create();
	_enemy1->setPosition(visibleSize.width/2,visibleSize.height/2-50);
	this->addChild(_enemy1);
	_enemy2 = enemy::create();
	_enemy2->setPosition(200,400);
	_enemy2->setScaleX(-1.0);
	this->addChild(_enemy2);
	_enemy3 = enemy::create();
	_enemy3->setPosition(800,300);
	this->addChild(_enemy3);

	_boss = boss::create();
	_boss->setPosition(760, 400);
	this->addChild(_boss);

	//menu添加
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(First::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto backpackerItem = MenuItemImage::create(
		"beibao2.png",
		"beibao1.png",
		CC_CALLBACK_1(First::backpackerCallback, this));
	backpackerItem->setPosition(Vec2(visibleSize.width - backpackerItem->getContentSize().width ,
		visibleSize.height -backpackerItem->getContentSize().height));
		
	auto menu = Menu::create(closeItem,backpackerItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	packTips = Label::createWithTTF("Get New Equipment", "fonts/Marker Felt.ttf", 36);
	packTips->setColor(Color3B::GREEN);
	packTips->setPosition(visibleSize.width - backpackerItem->getContentSize().width - 170,
		visibleSize.height - backpackerItem->getContentSize().height);
	addChild(packTips);
	packTips->setVisible(false);

	//添加触摸侦听器使玩家移动到点击处（必须在地图内）
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [visibleSize,this](Touch*t, Event*e){
		if (t->getLocation().y <480)
		{
			this->_hero->cleanup();
			this->_hero->runAction(MoveTo::create(abs((t->getLocation().x - this->_hero->getPosition().x) / this->getSpeed()) + abs((t->getLocation().y - this->_hero->getPosition().y) / this->getSpeed())
				, t->getLocation()));
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	this->scheduleUpdate();

	return true;
}

void First::update(float dt)
{
	//boss追踪玩家的逻辑实现
	double unitzation = sqrt((_hero->getPosition().x - _boss->getPosition().x)*(_hero->getPosition().x - _boss->getPosition().x)
		+ (_hero->getPosition().y - _boss->getPosition().y)*(_hero->getPosition().y - _boss->getPosition().y));
	auto direction = ccp((_hero->getPosition().x - _boss->getPosition().x) /unitzation, (_hero->getPosition().y - _boss->getPosition().y) / unitzation);
	_boss->setPosition(_boss->getPosition() + direction);

	//打开背包
	if (openbackpacker)
	{
		auto open = backpacker::create();
		open->setPackContent(hasShoes, hasArmor, hasBlade, hasUniqueskill);
		packTips->setVisible(false);
		openbackpacker = false;
		Director::getInstance()->pushScene(open);
	}


	//切换战斗的判断
	////////////////////////////////////////
	if (_enemy1->isCollideWithHero(_hero))
	{
		auto War = FirstWar::create();
		War->propertyinit(hero_life, hero_attack, hero_armor, hasArmor, hasBlade,hasUniqueskill);
		if (_enemy1->getisFightRun() == false)
		{
			Director::getInstance()->pushScene(War);
			_enemy1->setisFightRun();
		}
	}
	if (_enemy2->isCollideWithHero(_hero))
	{
		auto War = FirstWar::create();
		War->propertyinit(hero_life, hero_attack, hero_armor, hasArmor, hasBlade, hasUniqueskill);
		if (_enemy2->getisFightRun() == false)
		{
			Director::getInstance()->pushScene(War);
			_enemy2->setisFightRun();
		}
	}
	if (_enemy3->isCollideWithHero(_hero))
	{
		auto War = FirstWar::create();
		War->propertyinit(hero_life, hero_attack, hero_armor, hasArmor, hasBlade,hasUniqueskill);
		if (_enemy3->getisFightRun() == false)
		{
			Director::getInstance()->pushScene(War);
			_enemy3->setisFightRun();
		}
	}

	if (_boss->isCollideWithHero(_hero))
	{
		auto War = BossWar::create();
		War->propertyinit(hero_life, hero_attack, hero_armor, hasArmor, hasBlade, hasUniqueskill);
		if (_boss->getisFightRun() == false)
		{
			SimpleAudioEngine::getInstance()->unloadEffect("getnew.wav");
			Director::getInstance()->pushScene(War);
			_boss->setisFightRun();
		}
	}

	//物品的获得与大招的解锁
	//////////////////////////////////////
	if (_enemy1->getisFightRun() == true && hasArmor==false)
	{
		hasArmor = true;
		packTips->setVisible(true);
		SimpleAudioEngine::getInstance()->playEffect("getnew.wav");
	}//击败1号敌人获得装备
	if (_enemy2->getisFightRun() == true && hasBlade==false)
	{
		hasBlade = true;
		packTips->setVisible(true);
		SimpleAudioEngine::getInstance()->playEffect("getnew.wav");
	}//击败2号敌人获得武器
	if (_enemy3->getisFightRun() == true && hasUniqueskill==false)
	{
		hasUniqueskill = true;
		packTips->setVisible(true);
		SimpleAudioEngine::getInstance()->playEffect("getnew.wav");
	}
	if (_shoes->isCollideWithHero(_hero) && hasShoes==false)
	{
		hasShoes = true;
		hero_speed = 140;
		packTips->setVisible(true);
		SimpleAudioEngine::getInstance()->playEffect("getnew.wav");
	}//拾取鞋子

	if (hasArmor)
	{
		hero_armor = 60;
	}
	if (hasBlade)
	{
		hero_attack = 90;
	}
}

double First::getSpeed()
{
	return hero_speed;
}

void First::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void First::backpackerCallback(Ref* pSender)
{
	openbackpacker = true;
}