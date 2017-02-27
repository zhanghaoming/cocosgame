#include"backpacker.h"
//背包数据初始化创建
void backpacker::setPackContent(bool shoes, bool armor, bool blade, bool uniqueskill)
{
	hasShoes = shoes;
	hasArmor = armor;
	hasBlade = blade;
	hasUniqueSkill = uniqueskill;
}

bool backpacker::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("backpacker.png");
	background->setPosition(visibleSize / 2);
	addChild(background);

	auto BackItem = Label::createWithTTF("Click For Back", "fonts/Marker Felt.ttf", 50);
	BackItem->setColor(Color3B::ORANGE);
	BackItem->setPosition(visibleSize.width / 2, 50);
	addChild(BackItem);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* t,Event* e){
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::getInstance()->popScene();
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, BackItem);

	_Shoes = Sprite::create("xiezi.png");
	_Shoes->setPosition(180,425);
	addChild(_Shoes);

	_Armor = Sprite::create("zhuangjia.png");
	_Armor->setPosition(180, 275);
	addChild(_Armor);

	_Blade = Sprite::create("wuqi.png");
	_Blade->setPosition(180, 125);
	addChild(_Blade);

	_skill1 =Sprite::create("jineng1.png");
	_skill1->setPosition(visibleSize.width-180, 425);
	addChild(_skill1);

	_skill2 = Sprite::create("jineng2.png");
	_skill2->setPosition(visibleSize.width - 180, 275);
	addChild(_skill2);

	_skill3 = Sprite::create("jineng3.png");
	_skill3->setPosition(visibleSize.width - 180, 125);
	addChild(_skill3);

	this->scheduleUpdate();
	return true;
}
void backpacker::update(float dt)
{
	_Shoes->setVisible(hasShoes);
	_Armor->setVisible(hasArmor);
	_Blade->setVisible(hasBlade);
	_skill3->setVisible(hasUniqueSkill);
}