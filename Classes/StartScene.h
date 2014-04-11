/******************************************************************************

Test Application for FastNotificationCenter

Based on HelloCpp demo from Cocos2d.
 
Copyright (c) KARPOLAN 
http://karpolan.com

******************************************************************************/

#ifndef __Start_SCENE_H__
#define __Start_SCENE_H__

#include "cocos2d.h"

class Start : public cocos2d::CCLayer
{
protected:
	int _countObservers;

	cocos2d::CCLabelTTF* lbAdd1; cocos2d::CCMenuItem* miAdd1;
	cocos2d::CCLabelTTF* lbAdd2; cocos2d::CCMenuItem* miAdd2;
	cocos2d::CCLabelTTF* lbAdd3; cocos2d::CCMenuItem* miAdd3;

	cocos2d::CCLabelTTF* lbRemove1; cocos2d::CCMenuItem* miRemove1;
	cocos2d::CCLabelTTF* lbRemove2; cocos2d::CCMenuItem* miRemove2;
	cocos2d::CCLabelTTF* lbRemove3; cocos2d::CCMenuItem* miRemove3;

	cocos2d::CCLabelTTF* lbNotify1; cocos2d::CCMenuItem* miNotify1;
	cocos2d::CCLabelTTF* lbNotify2; cocos2d::CCMenuItem* miNotify2;
	cocos2d::CCLabelTTF* lbNotify3; cocos2d::CCMenuItem* miNotify3;

	cocos2d::CCLabelTTF* lbInfo;

	void updateObserversInfo();
	void resetLabelColors();

	void SEL_CallFunc(CCObject* object);

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseClick(CCObject* pSender);
	void menuAddClick(CCObject* pSender);
	void menuRemoveClick(CCObject* pSender);
	void menuNotifyClick(CCObject* pSender);
	void menuUpdateInfoClick(CCObject* pSender);	
    void menuRemoveAllClick(CCObject* pSender);	
    
    // implement the "static node()" method manually
    CREATE_FUNC(Start);
};

#endif // __Start_SCENE_H__
