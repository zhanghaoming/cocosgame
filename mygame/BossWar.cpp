#include"BossWar.h"
#include"GameOver.h"
#include"SimpleAudioEngine.h"

using namespace CocosDenshion;

bool BossWar::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SimpleAudioEngine::sharedEngine()->preloadEffect("Normalhit.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("uniqueskill.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("enemy.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("attackrise.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("boss1.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("boss2.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("resur.wav");

	enemy = Sprite::create("fboss.png");
	hero = Sprite::create("fhero.png");

	background = Sprite::create("zhandoubeijing.jpg");
	background->setPosition(visibleSize / 2);
	this->addChild(background);
	uniqueskill = Sprite::create("unique.jpg");
	uniqueskill->setPosition(visibleSize / 2);
	this->addChild(uniqueskill);
	uniqueskill->setVisible(false);


	lifeline_enemy = LabelTTF::create("500", "Arial", 50);
	lifeline_enemy->setColor(Color3B::GREEN);
	lifeline_hero = LabelTTF::create("500", "Arial", 50);
	lifeline_hero->setColor(Color3B::GREEN);

	Tips_enemy = LabelTTF::create(" ", "Helvetica", 30);
	Tips_enemy->setPosition(visibleSize.width - 150, 450);
	Tips_enemy->setColor(Color3B::ORANGE);
	this->addChild(Tips_enemy);
	Tips_hero = LabelTTF::create(" ", "Helvetica", 30);
	Tips_hero->setColor(Color3B::ORANGE);
	Tips_hero->setPosition(150, 450);
	this->addChild(Tips_hero);

	enemy->setPosition(visibleSize.width - 150,300);
	lifeline_enemy->setPosition(visibleSize.width - 150, 600);
	lifeline_hero->setPosition(150, 600);
	hero->setPosition(150,300);

	addChild(lifeline_hero);
	addChild(hero);
	addChild(lifeline_enemy);
	addChild(enemy);

	enemy_life = 1000;
	enemy_attack = 80;
	enemy_armor = 50;
	enemysturn = false;
	hasCrazyHit = true;
	isKey = true;
	

	//技能提示的添加
	_skill1 = Sprite::create("fjineng1.png");
	_skill1->setPosition(150, 100);
	addChild(_skill1);
	_skill2 = Sprite::create("fjineng2.png");
	_skill2->setPosition(450, 100);
	addChild(_skill2);
	_skill3 = Sprite::create("fjineng3.png");
	_skill3->setPosition(750, 100);
	addChild(_skill3);

	this->scheduleUpdate();

	isFightRun = 0;
	auto hero_listener = EventListenerKeyboard::create();
	hero_listener->onKeyPressed = [this](EventKeyboard::KeyCode code, Event *e){
		switch (code)
		{
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
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(hero_listener, this);
	return true;
}
void BossWar::UniqueSkill()
{
	enemy_life -= 200;
	enemysturn = true;
	hasUniqueskill = false;
	Tips_hero->setString("UNIUE SKILL!!!\nThudering Rage!!!");
	hero->runAction(Sequence::create(MoveTo::create(0.8f, ccp(150, 500)),MoveTo::create(0.2f, ccp(150, 300)),NULL));
	SimpleAudioEngine::sharedEngine()->playEffect("uniqueskill.wav", false);
	uniqueskill->setVisible(true);
	this->scheduleOnce(schedule_selector(BossWar::setUniqueUnvisible), 1.0f);
}
void BossWar::CrazyHit()
{
	hero_life-= 500;
	enemy_life = 200;
	ccBezierConfig bezier;
	bezier.controlPoint_1 = ccp(560, 800);
	bezier.controlPoint_2 = ccp(300, 50);
	bezier.endPosition = ccp(150, 300);
	ccBezierConfig hit;
	hit.controlPoint_1 = ccp(200, 800);
	hit.controlPoint_2 = ccp(50, 0);
	hit.endPosition = ccp(150, 300);
	auto* enemy_action = Sequence::create(BezierTo::create(0.2f, bezier), BezierTo::create(0.5f, hit), BezierTo::create(0.5f, hit),
		MoveTo::create(0.5f, Vec2(810, 300)), NULL);
	enemy->runAction(enemy_action);
	Tips_enemy->setString("!!!Suicide Attack!!!");
	SimpleAudioEngine::getInstance()->playEffect("boss2.wav",false);
	enemysturn = false;
	hasCrazyHit = false;
	isFightRun = 0;
}

void BossWar::AmazingVitality()
{
	LabelTTF* tip = LabelTTF::create("Boss has amazing vitality,\nHis body can recover quickly!!!", "Arial", 24);
	tip->setColor(Color3B::RED);
	tip->setPosition(800, 500);
	this->addChild(tip);
	enemy_life += 50;
}

void BossWar::update(float dt)
{
	char str1[100] = "LIFE:";
	sprintf(str1 + 5, "%.0f", enemy_life);
	lifeline_enemy->setString(str1);
	char str2[100] = "LIFE:";
	sprintf(str2 + 5, "%.0f", hero_life);
	lifeline_hero->setString(str2);

	if (isKey)
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

	if (isFightRun)
	{
		if (isFightRun == 1)
			NormalHit(true);
		if (isFightRun == 2)
			AttackRise();
		if (isFightRun == 3)
			UniqueSkill();
	}

	if (enemysturn)
	{
		if (enemy_life > 500)
		{
			NormalHit(false);
		}
		else{
			lifeline_enemy->setColor(Color3B::RED);
			if (hasCrazyHit)
				CrazyHit();
			else
				NormalHit(false);
		}
		if (hasBlade == false && enemy_life <= 950)
		{
			AmazingVitality();
		}
		isFightRun =0;
		this->scheduleOnce(schedule_selector(BossWar::setisFightRun), 1.3f);
	}

	if (enemy_life <= 0)
	{
		CCLabelTTF* label = LabelTTF::create("YOU WIN!", "Arial", 50);
		label->setColor(Color3B::RED);
		label->setPosition(480, 360);
		this->addChild(label);
		SimpleAudioEngine::sharedEngine()->unloadEffect("Normalhit.wav");
		SimpleAudioEngine::sharedEngine()->unloadEffect("uniqueskill.wav");
		SimpleAudioEngine::sharedEngine()->unloadEffect("enemy.wav");
		SimpleAudioEngine::sharedEngine()->unloadEffect("attackrise.wav");
		SimpleAudioEngine::sharedEngine()->unloadEffect("boss1.wav");
		SimpleAudioEngine::sharedEngine()->unloadEffect("boss2.wav");
		SimpleAudioEngine::sharedEngine()->unloadEffect("resur.wav");
		this->scheduleOnce(schedule_selector(BossWar::Victory), 2.0f);
	}
	else if (hero_life <= 0)
	{
		if (hasArmor == true)
		{
			hero_life =50;
			hasArmor = false;
			Label* tip = Label::create("Armor Has Been Broken.", "Arial", 24);
			tip->setColor(Color3B::RED);
			tip->setPosition(150, 200);
			this->addChild(tip);
			SimpleAudioEngine::sharedEngine()->playEffect("resur.wav");
		}
		else
		{
			CCLabelTTF* label = LabelTTF::create("YOU ARE KILLED!", "Arial", 50);
			label->setColor(Color3B::RED);
			label->setPosition(480, 360);
			this->addChild(label);

			SimpleAudioEngine::sharedEngine()->unloadEffect("Normalhit.wav");
			SimpleAudioEngine::sharedEngine()->unloadEffect("uniqueskill.wav");
			SimpleAudioEngine::sharedEngine()->unloadEffect("enemy.wav");
			SimpleAudioEngine::sharedEngine()->unloadEffect("attackrise.wav");
			SimpleAudioEngine::sharedEngine()->unloadEffect("boss1.wav");
			SimpleAudioEngine::sharedEngine()->unloadEffect("boss2.wav");
			SimpleAudioEngine::sharedEngine()->unloadEffect("resur.wav");
			SimpleAudioEngine::sharedEngine()->end();
			this->scheduleOnce(schedule_selector(BossWar::Death), 2.0f);
		}
	}
}

void BossWar::Victory(float dt)
{
	Director::getInstance()->replaceScene(Win::create());
}