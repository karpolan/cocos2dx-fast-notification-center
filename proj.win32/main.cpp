/******************************************************************************

Test Application for FastNotificationCenter

Based on HelloCpp demo from Cocos2d.
 
Copyright (c) KARPOLAN 
http://karpolan.com

******************************************************************************/
#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->setViewName(project_name);
//    eglView->setFrameSize(480, 320);
    eglView->setFrameSize(800, 480);
//    eglView->setFrameSize(1280, 720);
    return CCApplication::sharedApplication()->run();
}
