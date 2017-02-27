#include"FirstWar.h"
#include"GameOver.h"
#include"SimpleAudioEngine.h"

using namespace CocosDenshion;

///////英雄数据初始化
void FirstWar::propertyinit(double life, double attack, double armor, bool DrinkerBlade, bool KingBlade,bool Uniqueskill)
{
	hero_life=life;
	hero_attack=attack;
	hero_armor=armor;
	hasArmor = DrinkerBlade;
	hasBlade = KingBlade;
	hasUniqueskill = Uniqueskill;
}

bool FirstWar::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SimpleAudioEngine::sharedEngine()->preloadEffect("Normalhit.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("uniqueskill.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("enemy.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("attackrise.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("boss1.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("resur.wav");

	enemy = Sprite::create("fenemy.png");
	hero = Sprite::create("fhero.png");

	//背景添加
	uniqueskill = Sprite::create("unique.jpg");
	uniqueskill->setPosition(visibleSize / 2);
	this->addChild(uniqueskill);
	uniqueskill->setVisible(false);
	background = Sprite::create("zhandoubeijing.jpg");
	background->setPosition(visibleSize / 2);
	this->addChild(background);

	//数据初始化
	if (hasUniqueskill == true)
		enemy_life = 600;
	else
		enemy_life = 500;
	enemy_attack = 80;
	enemy_armor = 40;
	enemysturn = false;
	isFightRun = 0;
	isKey = true;
	
	//提示的添加
	lifeline_enemy = LabelTTF::create("500",  "Arial", 50);
	lifeline_enemy->setColor(Color3B::GREEN);
	lifeline_hero = LabelTTF::create("500", "Arial", 50);
	lifeline_hero->setColor(Color3B::GREEN);

	Tips_enemy = LabelTTF::create("2", "Helvetica", 30);
	Tips_enemy->setPosition(visibleSize.width - 150, 450);
	Tips_enemy->setColor(Color3B::ORANGE);
	this->addChild(Tips_enemy);
	Tips_hero = LabelTTF::create("2", "Helvetica", 30);
	Tips_hero->setPosition(150, 450);
	Tips_hero->setColor(Color3B::ORANGE);
	this->addChild(Tips_hero);

	lifeline_hero->setPosition(150, 600);
	hero->setPosition(150, 300);
	enemy->setPosition(visibleSize.width-150, 300);
	lifeline_enemy->setPosition(visibleSize.width - 150, 600);
	addChild(lifeline_hero);
	addChild(hero);
	addChild(lifeline_enemy);
	addChild(enemy);

	//技能提示的添加
	_skill1 = Sprite::create("fjineng1.png");
	_skill1->setPosition(150,100);
	addChild(_skill1);
	_skill2 = Sprite::create("fjineng2.png");
	_skill2->setPosition(450,100);
	addChild(_skill2);
	_skill3 = Sprite::create("fjineng3.png");
	_skill3->setPosition(750, 100);
	addChild(_skill3);


	this->scheduleUpdate();


	auto hero_listener = EventListenerKeyboard::create();
	hero_listener->onKeyPressed = [this](EventKeyboard::KeyCode code, Event *e){
		switch (code)
		{
			//在按下qwe中的键位后，会重置isKey为false，调整isFightRun来决定玩家执行的
			//战斗技能
		case cocos2d::EventKeyboard::KeyCode::KEY_Q:
			if (isKey&&isFightRun == 0){
				isKey = false;
				isFightRun = 1;
			}
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			if (isKey&&isFightRun == 0){
				isKey = false;
				isFightRun = 2;
			}
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_E:
			if (isKey&&isFightRun == 0 && hasUniqueskill == true){
				isKey = false;
				isFightRun = 3;
			}
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(hero_listener,this);
	return true;
}
////////////////////////////////////////////////////////////////////
//////////////////////以下是战斗逻辑函数///////////////////////////
//包括英雄和怪物的技能释放的实现，包括动画，音效，提示的改变//////
/////////////////////////////////////////////////////////////////
void FirstWar::NormalHit(bool ishero)
{
	ccBezierConfig bezier;
	bezier.controlPoint_1 = ccp(560, 600);
	bezier.controlPoint_2 = ccp(300, 50);
	bezier.endPosition = ccp(150, 300);
	auto* enemy_action = Sequence::create(BezierTo::create(0.3f, bezier),MoveTo::create(0.6f, Vec2(810, 300)), NULL);

	auto* hero_action = Sequence::create(RotateBy::create(0.5f, 60), MoveTo::create(0.5f, Vec2(810, 300)), RotateBy::create(0.1f, -60),
		MoveTo::create(0.2f, Vec2(150, 300)), NULL);
	if (ishero)
	{
		hero->runAction(hero_action);
		enemy_life -= hero_attack - enemy_armor;
		Tips_hero->setString("Thunder Clap !!!");
		SimpleAudioEngine::sharedEngine()->playEffect("Normalhit.wav",false);
		enemysturn = true;
	}
	else
	{
		enemy->runAction(enemy_action);
		hero_life -= enemy_attack - hero_armor;
		Tips_enemy->setString("Fierce Hit !!!");
		SimpleAudioEngine::sharedEngine()->playEffect("boss1.wav", false);
		enemysturn = false;
	}
}
void FirstWar::CrazyHit()//当怪物进入低血量时执行的攻击
{
	ccBezierConfig bezier;
	bezier.controlPoint_1 = ccp(560, 800);
	bezier.controlPoint_2 = ccp(300, 50);
	bezier.endPosition = ccp(150, 300);
	auto* enemy_action = Sequence::create(BezierTo::create(0.2f, bezier), MoveTo::create(0.6f, Vec2(810, 300)), NULL);
	enemy->runAction(enemy_action);
	Tips_enemy->setString("Crazy Hit!");
	SimpleAudioEngine::sharedEngine()->playEffect("enemy.wav", false);
	hero_life -= 2.0*(enemy_attack - hero_armor);
	enemysturn = false;
}
void FirstWar::AttackRise()//英雄的技能2,提升攻击
{
	hero_attack += 10;
	enemysturn = true;
	SimpleAudioEngine::sharedEngine()->playEffect("attackrise.wav", false);
	Tips_hero->setString("Fighting Heart!\n Attack Up!");
}
void FirstWar::UniqueSkill()//英雄的绝招
{
	enemy_life -= 100;
	enemysturn=true;
	hasUniqueskill = false;
	Tips_hero->setString("UNIUE SKILL!!!\nThudering Rage!!!");
	hero->runAction(Sequence::create(MoveTo::create(0.8f, ccp(150, 500)),MoveTo::create(0.2f, ccp(150, 300)), NULL));
	SimpleAudioEngine::sharedEngine()->playEffect("uniqueskill.wav", false);
	background->setVisible(false);
	uniqueskill->setVisible(true);
	this->scheduleOnce(schedule_selector(FirstWar::setUniqueUnvisible), 1.0f);
}
//////////////////////////////////////////////////////////////////////////
//在玩家的每个战斗函数后都要使enemysturn为true以开始敌人的动作///////////
//而在敌人的每个战斗函数后都要使enemysturn为false以结束敌人回合的重复///
///////////////////////////////////////////////////////////////////////

void FirstWar::update(float dt)
{
	//血量值的变化
	char str1[100] = "LIFE:";
	sprintf(str1+5, "%.0f",enemy_life);
	lifeline_enemy->setString(str1);
	char str2[100] = "LIFE:";
	sprintf(str2+5, "%.0f",hero_life);
	lifeline_hero->setString(str2);

	if (hasBlade)
		enemy_armor = 50;
	if (hasArmor)
		enemy_attack = 100;

	if (isKey)//技能、提示的显示调节
	{
		_skill1->setVisible(true);
		_skill2->setVisible(true);
		if (hasUniqueskill == true)
			_skill3->setVisible(true);
		else
			_skill3->setVisible(false);

		Tips_enemy->setVisible(false);
		Tips_hero->setVisible(false);
	}
	if (false == isKey)
	{
		_skill1->setVisible(false);
		_skill2->setVisible(false);
		_skill3->setVisible(false);
		Tips_enemy->setVisible(true);
		Tips_hero->setVisible(true);
	}

	//判断isFightRun开始执行玩家的技能动作
	if (isFightRun)
	{
		if (isFightRun == 1)
			NormalHit(true);
		if (isFightRun == 2)
			AttackRise();
		if (isFightRun == 3)
			UniqueSkill();
	}
	//判断enemysturn开始执行怪物的逻辑
	if (enemysturn)
	{
		if (enemy_life > 200)
		{
			NormalHit(false);
		}
		else{
			lifeline_enemy->setColor(Color3B::RED);
			CrazyHit();
		}
		isFightRun = 0;//结束此回合
		
		this->scheduleOnce(schedule_selector(FirstWar::setisFightRun), 1.3f);//延时1.3s将键盘标记为可用
		///////////////////////////////////////////////////////////////////////确保精灵动作完成后才能开始下一回合
	}

	if (enemy_life <= 0)//击败敌人获得胜利则退出此场景
	{
		CCLabelTTF* label = LabelTTF::create("YOU WIN!", "Arial", 50);
		label->setColor(Color3B::RED);
		label->setPosition(480, 360);
		this->addChild(label);
		SimpleAudioEngine::sharedEngine()->unloadEffect("Normalhit.wav");
		SimpleAudioEngine::sharedEngine()->unloadEffect("uniqueskill.wav");
		SimpleAudioEngine::sharedEngine()->unloadEffect("enemy.wav");
		SimpleAudioEngine::sharedEngine()->unloadEffect("boss1.wav");
		SimpleAudioEngine::sharedEngine()->unloadEffect("attackrise.wav");
		SimpleAudioEngine::sharedEngine()->stopAllEffects();
		Director::getInstance()->popScene();
	}
	else if (hero_life <= 0)//英雄濒死时的判断
	{
		if (hasArmor == true)//是否有装甲的被动，复活一次
		{
			hero_life =50;
			hasArmor= false;
			CCLabelTTF* label = LabelTTF::create("The Armor Has Been Broken", "Arial", 24);
			label->setColor(Color3B::RED);
			label->setPosition(150, 200);
			this->addChild(label);
			SimpleAudioEngine::sharedEngine()->playEffect("resur.wav", false);
		}
		else//死亡，切换至失败场景
		{
			CCLabelTTF* label = LabelTTF::create("YOU ARE KILLED!", "Arial", 50);
			label->setColor(Color3B::GRAY);
			label->setPosition(480, 360);
			this->addChild(label);
			SimpleAudioEngine::sharedEngine()->unloadEffect("Normalhit.wav");
			SimpleAudioEngine::sharedEngine()->unloadEffect("uniqueskill.wav");
			SimpleAudioEngine::sharedEngine()->unloadEffect("enemy.wav");
			SimpleAudioEngine::sharedEngine()->unloadEffect("attackrise.wav");
			SimpleAudioEngine::sharedEngine()->unloadEffect("boss1.wav");
			SimpleAudioEngine::sharedEngine()->end();
			this->scheduleOnce(schedule_selector(FirstWar::Death), 2.0f);
			
		}
	}
}
void FirstWar::Death(float dt)
{
	Director::getInstance()->replaceScene(Over::create());
}

void FirstWar::setUniqueUnvisible(float dt)//调节释放大招时的动画显示
{
	background->setVisible(true);
	uniqueskill->setVisible(false);
}