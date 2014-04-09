#include "StartScene.h"
//#include "..\..\cocos2d\cocos2dx\support\ccnotificationcenter.h"
#include "FastNotificationCenter.h"

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

// on "init" you need to initialize your instance
bool Start::init()
{

	_countObservers = 0;

	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(Start::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);



	
	this->lbAdd1 = CCLabelTTF::create("Add1", "Arial", 20);
	this->miAdd1 = CCMenuItemLabel::create(this->lbAdd1, this, menu_selector(Start::menuAddClick)); 
	this->miAdd1->setTag(1);
   	this->miAdd1->setPosition(ccp(80, 250));
		

	this->lbAdd2 = CCLabelTTF::create("Add2", "Arial", 20);
	this->miAdd2 = CCMenuItemLabel::create(this->lbAdd2, this, menu_selector(Start::menuAddClick)); 
	this->miAdd2->setTag(2);
   	this->miAdd2->setPosition(ccp(240, 250));
//	this->addChild(miAdd2, 1);

	this->lbAdd3 = CCLabelTTF::create("Add3", "Arial", 20);
	this->miAdd3 = CCMenuItemLabel::create(this->lbAdd3, this, menu_selector(Start::menuAddClick)); 
	this->miAdd3->setTag(3);
   	this->miAdd3->setPosition(ccp(400, 250));
//	this->addChild(miAdd3, 1);



	this->lbRemove1 = CCLabelTTF::create("Remove1", "Arial", 20);
	this->miRemove1 = CCMenuItemLabel::create(this->lbRemove1, this, menu_selector(Start::menuRemoveClick)); 
	this->miRemove1->setTag(1);
   	this->miRemove1->setPosition(ccp(80, 200));
//	this->addChild(miRemove1, 1);

	this->lbRemove2 = CCLabelTTF::create("Remove2", "Arial", 20);
	this->miRemove2 = CCMenuItemLabel::create(this->lbRemove2, this, menu_selector(Start::menuRemoveClick)); 
	this->miRemove2->setTag(2);
   	this->miRemove2->setPosition(ccp(240, 200));
//	this->addChild(miRemove2, 1);

	this->lbRemove3 = CCLabelTTF::create("Remove3", "Arial", 20);
	this->miRemove3 = CCMenuItemLabel::create(this->lbRemove3, this, menu_selector(Start::menuRemoveClick)); 
	this->miRemove3->setTag(3);
   	this->miRemove3->setPosition(ccp(400, 200));
//	this->addChild(miRemove3, 1);




	this->lbNotify1 = CCLabelTTF::create("Notify1", "Arial", 20);
	this->miNotify1 = CCMenuItemLabel::create(this->lbNotify1, this, menu_selector(Start::menuNotifyClick)); 
	this->miNotify1->setTag(1);
   	this->miNotify1->setPosition(ccp(80, 150));
//	this->addChild(miNotify1, 1);

	this->lbNotify2 = CCLabelTTF::create("Notify2", "Arial", 20);
	this->miNotify2 = CCMenuItemLabel::create(this->lbNotify2, this, menu_selector(Start::menuNotifyClick)); 
	this->miNotify2->setTag(2);
   	this->miNotify2->setPosition(ccp(240, 150));
//	this->addChild(miNotify2, 1);

	this->lbNotify3 = CCLabelTTF::create("Notify3", "Arial", 20);
	this->miNotify3 = CCMenuItemLabel::create(this->lbNotify3, this, menu_selector(Start::menuNotifyClick)); 
	this->miNotify3->setTag(3);
   	this->miNotify3->setPosition(ccp(400, 150));
//	this->addChild(miNotify3, 1);


	pMenu->addChild(miAdd1);
	pMenu->addChild(miAdd2);
	pMenu->addChild(miAdd3);

	pMenu->addChild(miRemove1);pMenu->addChild(miRemove2);
	pMenu->addChild(miRemove3);

	pMenu->addChild(miNotify1);
	pMenu->addChild(miNotify2);
	pMenu->addChild(miNotify3);


	CCMenuItemLabel* itemMenu = NULL; 
	CCLabelTTF* itemLabel = NULL;

	// Title label
    itemLabel = CCLabelTTF::create("FastNotificationCenter Test App", "Arial", 20);
	itemLabel->setPosition(ccp(240, 290));
    this->addChild(itemLabel);

	// Info label
    lbInfo = CCLabelTTF::create("Info: XXX", "Arial", 14);
	lbInfo->setPosition(ccp(240, 100));
    this->addChild(lbInfo);

	// Update Info button
	itemLabel = CCLabelTTF::create("Update Info", "Arial", 20);
	itemLabel->setColor(ccYELLOW);
	itemMenu = CCMenuItemLabel::create(itemLabel, this, menu_selector(Start::menuUpdateInfoClick)); 
   	itemMenu->setPosition(ccp(380, 60));
	pMenu->addChild(itemMenu);

	// Remove All Notification button
	itemLabel = CCLabelTTF::create("Remove All Notification", "Arial", 20);
	itemLabel->setColor(ccORANGE);
	itemMenu = CCMenuItemLabel::create(itemLabel, this, menu_selector(Start::menuRemoveAllClick)); 
   	itemMenu->setPosition(ccp(150, 60));
	pMenu->addChild(itemMenu);





	// position the label on the center of the screen
   // pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
   //                         origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
   // this->addChild(pLabel, 1);


/*
    // add "Start" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
*/

	resetLabelColors();
	updateObserversInfo();
    
    return true;
}


void Start::menuCloseCallback(CCObject* pSender)
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


void Start::menuNotifyClick(CCObject* pSender)
{
	CCMenuItem* menuItem = (CCMenuItem*) pSender;
	unsigned int code = menuItem->getTag();

	FastNotificationCenter* NC = FastNotificationCenter::sharedObject();
	NC->postNotification(code);

	updateObserversInfo();
}


void Start::SEL_CallFunc(CCObject* object)
{
	CCMenuItemLabel* menuItem = (CCMenuItemLabel*) object;
	CCLabelTTF* label = (CCLabelTTF*) menuItem->getLabel();
	label->setColor(ccc3(63 + rand() % 191, 63 + rand() % 191, 63 + rand() % 191));
}


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


void Start::updateObserversInfo()
{
	FastNotificationCenter* NC = FastNotificationCenter::sharedObject();

	int count = _countObservers;
	_countObservers = NC->getObserversCount();

	CCString* text = CCString::createWithFormat("Observers old count: %d, Observers current count: %d.", count, _countObservers);
	lbInfo->setString(text->getCString());
/*
int score = 35;
float time = 0.03;
char* name = "Michael";
char text[256];
sprintf(text,"name is %s, time is %.2f, score is %d", name, time, score);
CCLabelTTF* label = CCLabelTTF::labelWithString(text,"Arial",20);
this->addChild(label);
*/
}


void Start::menuUpdateInfoClick(CCObject* pSender)
{
	updateObserversInfo();
}

void Start::menuRemoveAllClick(CCObject* pSender)
{
	FastNotificationCenter::sharedObject()->removeAllObservers(NULL); // NULL means: remove all observers from internal array.
	resetLabelColors();
	updateObserversInfo();
}

