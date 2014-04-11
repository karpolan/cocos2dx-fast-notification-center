/******************************************************************************

Test Application for FastNotificationCenter

Based on HelloCpp demo from Cocos2d.
 
Copyright (c) KARPOLAN 
http://karpolan.com

******************************************************************************/

#include "cocos2d.h"
#include "StartScene.h"
//#include "..\..\cocos2d\cocos2dx\support\ccnotificationcenter.h"
#include "..\FastNotificationCenter.h"

USING_NS_CC;

CCScene* Start::scene()
{

    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Start *layer = Start::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

//-----------------------------------------------------------------------------

// on "init" you need to initialize your instance
bool Start::init()
{

	_countObservers = 0;

    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    int sizeMin = visibleSize.width;
    if (sizeMin > visibleSize.height) sizeMin = visibleSize.height;

    int sizeMax = visibleSize.width;
    if (sizeMax < visibleSize.height) sizeMax = visibleSize.height;

    int sizeFont = 80;
    if (sizeMin <= 720) sizeFont = 40;
    if (sizeMin <= 480) sizeFont = 30;
    if (sizeMin <= 320) sizeFont = 20;
	

	CCMenuItemLabel* itemMenu = NULL; 
	CCLabelTTF* itemLabel = NULL;

	CCMenu* menuMain = CCMenu::create();
    menuMain->setPosition(CCPointZero);
    this->addChild(menuMain, 1);

	// X button
    itemLabel = CCLabelTTF::create("[X]", "Arial", sizeFont);
	itemLabel->setColor(ccYELLOW);
	itemMenu = CCMenuItemLabel::create(itemLabel, this, menu_selector(Start::menuCloseClick));
   	itemMenu->setPosition(ccp(sizeMax - (sizeFont *2), sizeMin - sizeFont));
   	menuMain->addChild(itemMenu);

    // Title label
    itemLabel = CCLabelTTF::create("FastNotificationCenter Test App", "Arial", sizeFont);
	itemLabel->setPosition(ccp((sizeMax / 2), sizeMin - (sizeMin / 10)));
    this->addChild(itemLabel);

	// Info label
	lbInfo = CCLabelTTF::create("Info: XXX", "Arial", int(sizeFont * 0.75));
	lbInfo->setPosition(ccp((sizeMax / 2),  sizeMin / 3));
    this->addChild(lbInfo);

	// Update Info button
	itemLabel = CCLabelTTF::create("Update Info", "Arial", sizeFont);
	itemLabel->setColor(ccYELLOW);
	itemMenu = CCMenuItemLabel::create(itemLabel, this, menu_selector(Start::menuUpdateInfoClick)); 
   	itemMenu->setPosition(ccp((sizeMax / 2) + (sizeMax / 3.5), sizeMin / 5));
   	menuMain->addChild(itemMenu);

	// Remove All Notification button
	itemLabel = CCLabelTTF::create("Remove All Notification", "Arial", sizeFont);
	itemLabel->setColor(ccORANGE);
	itemMenu = CCMenuItemLabel::create(itemLabel, this, menu_selector(Start::menuRemoveAllClick)); 
   	itemMenu->setPosition(ccp((sizeMax / 2) - (sizeMax / 4), sizeMin / 5));
   	menuMain->addChild(itemMenu);

	
	// Add/Remove/Notify labels
	int y = (sizeMin / 2) + (sizeMin / 10) + (sizeMin / 7);
	
	this->lbAdd1 = CCLabelTTF::create("Add1", "Arial", sizeFont);
	this->miAdd1 = CCMenuItemLabel::create(this->lbAdd1, this, menu_selector(Start::menuAddClick)); 
	this->miAdd1->setTag(1);
   	this->miAdd1->setPosition(ccp((sizeMax / 2) - (sizeMax / 5), y));
	
	this->lbAdd2 = CCLabelTTF::create("Add2", "Arial", sizeFont);
	this->miAdd2 = CCMenuItemLabel::create(this->lbAdd2, this, menu_selector(Start::menuAddClick)); 
	this->miAdd2->setTag(2);
   	this->miAdd2->setPosition(ccp(sizeMax / 2, y));

	this->lbAdd3 = CCLabelTTF::create("Add3", "Arial", sizeFont);
	this->miAdd3 = CCMenuItemLabel::create(this->lbAdd3, this, menu_selector(Start::menuAddClick)); 
	this->miAdd3->setTag(3);
   	this->miAdd3->setPosition(ccp((sizeMax / 2) + (sizeMax / 5), y));


	y = (sizeMin / 2) + (sizeMin / 10);
	
	this->lbRemove1 = CCLabelTTF::create("Remove1", "Arial", sizeFont);
	this->miRemove1 = CCMenuItemLabel::create(this->lbRemove1, this, menu_selector(Start::menuRemoveClick)); 
	this->miRemove1->setTag(1);
   	this->miRemove1->setPosition(ccp((sizeMax / 2) - (sizeMax / 5), y));

	this->lbRemove2 = CCLabelTTF::create("Remove2", "Arial", sizeFont);
	this->miRemove2 = CCMenuItemLabel::create(this->lbRemove2, this, menu_selector(Start::menuRemoveClick)); 
	this->miRemove2->setTag(2);
   	this->miRemove2->setPosition(ccp((sizeMax / 2), y));

	this->lbRemove3 = CCLabelTTF::create("Remove3", "Arial", sizeFont);
	this->miRemove3 = CCMenuItemLabel::create(this->lbRemove3, this, menu_selector(Start::menuRemoveClick)); 
	this->miRemove3->setTag(3);
   	this->miRemove3->setPosition(ccp((sizeMax / 2) + (sizeMax / 5), y));


	y = (sizeMin / 2) + (sizeMin / 10) - (sizeMin / 7);
	
	this->lbNotify1 = CCLabelTTF::create("Notify1", "Arial", sizeFont);
	this->miNotify1 = CCMenuItemLabel::create(this->lbNotify1, this, menu_selector(Start::menuNotifyClick)); 
	this->miNotify1->setTag(1);
   	this->miNotify1->setPosition(ccp((sizeMax / 2) - (sizeMax / 5), y));

	this->lbNotify2 = CCLabelTTF::create("Notify2", "Arial", sizeFont);
	this->miNotify2 = CCMenuItemLabel::create(this->lbNotify2, this, menu_selector(Start::menuNotifyClick)); 
	this->miNotify2->setTag(2);
   	this->miNotify2->setPosition(ccp(sizeMax / 2, y));

	this->lbNotify3 = CCLabelTTF::create("Notify3", "Arial", sizeFont);
	this->miNotify3 = CCMenuItemLabel::create(this->lbNotify3, this, menu_selector(Start::menuNotifyClick)); 
	this->miNotify3->setTag(3);
   	this->miNotify3->setPosition(ccp((sizeMax / 2) + (sizeMax / 5), y));


   	menuMain->addChild(miAdd1);
   	menuMain->addChild(miAdd2);
   	menuMain->addChild(miAdd3);

   	menuMain->addChild(miRemove1);
   	menuMain->addChild(miRemove2);
   	menuMain->addChild(miRemove3);

   	menuMain->addChild(miNotify1);
   	menuMain->addChild(miNotify2);
   	menuMain->addChild(miNotify3);


	resetLabelColors();
	updateObserversInfo();
    
    return true;
}

//-----------------------------------------------------------------------------

void Start::resetLabelColors()
{
	this->lbAdd1->setColor(ccRED);
	this->lbAdd2->setColor(ccGREEN);
	this->lbAdd3->setColor(ccBLUE);

	this->lbRemove1->setColor(ccRED);
	this->lbRemove2->setColor(ccGREEN);
	this->lbRemove3->setColor(ccBLUE);

	this->lbNotify1->setColor(ccRED);
	this->lbNotify2->setColor(ccGREEN);
	this->lbNotify3->setColor(ccBLUE);
}

//-----------------------------------------------------------------------------

void Start::updateObserversInfo()
{
	FastNotificationCenter* NC = FastNotificationCenter::sharedObject();

	int count = _countObservers;
	_countObservers = NC->getObserversCount();

	CCString* text = CCString::createWithFormat("Observers old count: %d, Observers current count: %d.", count, _countObservers);
	lbInfo->setString(text->getCString());
}


//-----------------------------------------------------------------------------
// Events and Callbacks
//-----------------------------------------------------------------------------

void Start::SEL_CallFunc(CCObject* object)
{
	CCMenuItemLabel* menuItem = (CCMenuItemLabel*) object;
	CCLabelTTF* label = (CCLabelTTF*) menuItem->getLabel();

	///	ccColor3B color = ccc3(63 + rand() % 191, 63 + rand() % 191, 63 + rand() % 191);
	ccColor3B color;
	color.r = 63 + rand();
	color.g = 63 + rand();
	color.b = 63 + rand();
	label->setColor(color);
}

//-----------------------------------------------------------------------------

void Start::menuCloseClick(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

//-----------------------------------------------------------------------------

void Start::menuAddClick(CCObject* pSender)
{
	CCMenuItem* menuItem = (CCMenuItem*) pSender;
	unsigned int code = menuItem->getTag();
	CCObject* target = menuItem;
	
	CCObject* object = menuItem;
	SEL_CallFuncO function = callfuncO_selector(Start::SEL_CallFunc);

	switch (code) 
	{
		case 1: 
			target = miNotify1;
			lbAdd1->setColor(ccWHITE);
			break;
		case 2: 
			target = miNotify2;
			lbAdd2->setColor(ccWHITE);
			break;
		case 3: 
			target = miNotify3;
			lbAdd3->setColor(ccWHITE);
			break;
		default:
			return;
	}

	FastNotificationCenter* NC = FastNotificationCenter::sharedObject();
	NC->addObserver(target, function, object, code);

	updateObserversInfo();
}

//-----------------------------------------------------------------------------

void Start::menuRemoveClick(CCObject* pSender)
{
	CCMenuItem* menuItem = (CCMenuItem*) pSender;
	unsigned int code = menuItem->getTag();
	CCObject* target = menuItem;

	switch (code) 
	{
		case 1: 
			target = miNotify1;
			lbAdd1->setColor(ccRED);
			break;
		case 2: 
			target = miNotify2;
			lbAdd2->setColor(ccGREEN);
			break;
		case 3: 
			target = miNotify3;
			lbAdd3->setColor(ccBLUE);
			break;
		default:
			return;
	}

	FastNotificationCenter* NC = FastNotificationCenter::sharedObject();
	NC->removeObserver(target, code);

	updateObserversInfo();
}

//-----------------------------------------------------------------------------

void Start::menuNotifyClick(CCObject* pSender)
{
	CCMenuItem* menuItem = (CCMenuItem*) pSender;
	unsigned int code = menuItem->getTag();

	FastNotificationCenter* NC = FastNotificationCenter::sharedObject();
	NC->postNotification(code);

	updateObserversInfo();
}

//-----------------------------------------------------------------------------

void Start::menuUpdateInfoClick(CCObject* pSender)
{
	updateObserversInfo();
}

//-----------------------------------------------------------------------------

void Start::menuRemoveAllClick(CCObject* pSender)
{
	FastNotificationCenter::sharedObject()->removeAllObservers(NULL); // NULL means: remove all observers from internal array.
	resetLabelColors();
	updateObserversInfo();
}

//-----------------------------------------------------------------------------


