#include"GameOver.h"
#include"StartScene.h"
#include"SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

void Over::backgrondinit()
{
	background = Sprite::create("false.png");
	SimpleAudioEngine::getInstance()->preloadEffect("defeat.wav");
	SimpleAudioEngine::getInstance()->playEffect("defeat.wav");
}

void Over::menuCloseCallback(Ref* pSender)
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

bool Over::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	backgrondinit();
	background->setPosition(visibleSize / 2);
	addChild(background);

	auto closeItem = MenuItemImage::create(
		"tuichu1.png",
		"tuichu2.png",
		CC_CALLBACK_1(Over::menuCloseCallback, this));
	closeItem->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 250);

	auto startItem = MenuItemImage::create(
		"caidan1.png",
		"caidan2.png",
		[](Object *obj){
		Director::getInstance()->
			replaceScene(TransitionFadeBL::create(1, Start::createScene()));
	});
	startItem->setPosition(visibleSize.width/2,visibleSize.height/2-100);
	auto menu = Menu::create(closeItem, startItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void Win::backgrondinit(){
	background = Sprite::create("true.png");
	SimpleAudioEngine::getInstance()->preloadEffect("win.wav");
	SimpleAudioEngine::getInstance()->playEffect("win.wav");
}

bool Help::init()
{
	background = Sprite::create("bangzhu.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	background->setPosition(visibleSize / 2);
	addChild(background);

	auto BackItem = Label::createWithTTF("Click For Back", "fonts/Marker Felt.ttf", 50);
	BackItem->setColor(Color3B::ORANGE);
	BackItem->setPosition(150, 50);
	addChild(BackItem);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* t, Event* e){
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::getInstance()->popScene();
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, BackItem);

	return true;
}