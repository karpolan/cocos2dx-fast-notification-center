#include "AppDelegate.h"
#include "StartScene.h"
#include "FastNotificationCenter.h"
#include "cocos2d.h"

USING_NS_CC;

const char* project_name		= "FastNotificationCenter Test App";
const char* project_version		= "1.0.0.3";
const char* product_ver			= "1.0";
const char* project_description = "Application on Cocos2D engine for testion FastNotificationCenter class";
const char* project_copyright	= "Copyright (c) KARPOLAN";


AppDelegate::AppDelegate() {
	FastNotificationCenter * FNC = FastNotificationCenter::sharedObject();
}

AppDelegate::~AppDelegate() 
{
	FastNotificationCenter::sharedObjectFree;
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = Start::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
