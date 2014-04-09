/******************************************************************************

Based on CCNotificationCenter class from Cocos2d.

Changes:
Array of Observers objects is protected
Added findObserver() method to get object or verify does such Observer exit 
All postXXX() methods returns number of observers have been notified
Added methods for events/notifications specified by numeric constants
addXXX methods routine the new instance of observer
removeXXX() methods returns number of observers have been removed
Singleton management added.

Removed/Untested:
Scripts and LUA support

Copyright (c) KARPOLAN 
http://karpolan.com

******************************************************************************/

#ifndef __FASTNOTIFICATIONCENTER_H__
#define __FASTNOTIFICATIONCENTER_H__

#include "cocos2d.h"
//#include "..\..\cocos2d\cocos2dx\support\ccnotificationcenter.h"

NS_CC_BEGIN

//=============================================================================
// FastNotificationObserver
//=============================================================================
// Class to hold notification for some "Target" object. 
// The "Function" is called when notification by "Name" or "Code" is fired. 
// The "Object" is optional parameter, can be used to pass some additional data 
// into the "Function" during notification.
// Note: analog of CCNotificationObserver standard class.

class FastNotificationObserver : public CCObject
{
public:
	FastNotificationObserver();
	FastNotificationObserver(CCObject * target, SEL_CallFuncO function, CCObject* object, const unsigned int code, const char* name);
protected:
    ~FastNotificationObserver();      
	virtual void CreateParams(CCObject * target, SEL_CallFuncO function, CCObject* object, const unsigned int code, const char* name);
public:
    virtual void performFunction(CCObject *object);
// Properties
	CC_PROPERTY_READONLY(CCObject *, _target, Target);
    CC_PROPERTY_READONLY(SEL_CallFuncO, _function, Function);
    CC_PROPERTY_READONLY(char *, _name, Name);
	CC_PROPERTY_READONLY(unsigned int, _code, Code);
    CC_PROPERTY_READONLY(CCObject *, _object, Object);
//    CC_PROPERTY(int, _handler,Handler);
};


//=============================================================================
// FastNotificationCenter
//=============================================================================
// Class holds and manages array of FastNotificationObserver objects. 
// Can be used as singleton via sharedObjectXXX routines.
// Notifications by "Code" or "Name" are fired by postNotification() methods.
// Note: analog of CCNotificationCenter standard class.

class FastNotificationCenter : public CCObject
{	
public:
	FastNotificationCenter(); // Constructor
protected:
	virtual ~FastNotificationCenter(); // Destructor

// Singleton
public:
	static FastNotificationCenter* sharedObject(); 
	static void sharedObjectFree(); 

// Observer routines
protected:
	CCArray* observers; // Array of all observers, CCNotificationCenter class uses the private array.
	virtual FastNotificationObserver* findObserver(CCObject* target, const char* name);
	virtual FastNotificationObserver* findObserver(CCObject* target, const unsigned int code);
public:
	virtual unsigned int getObserversCount(void);
	virtual FastNotificationObserver* addObserver(CCObject* target, SEL_CallFuncO function, CCObject* object, const char* name);
	virtual FastNotificationObserver* addObserver(CCObject* target, SEL_CallFuncO function, CCObject* object, const unsigned int code);
	virtual int removeObserver(CCObject* target, const char* name);
	virtual int removeObserver(CCObject* target, const unsigned int code);
	virtual int removeAllObservers(CCObject* target = NULL); // Removes all observers by default

// Notification routines
public:
	virtual int postNotification(const char* name);
	virtual int postNotification(const char* name, CCObject* object);
	virtual int postNotification(const unsigned int code);
	virtual int postNotification(const unsigned int code, CCObject* object);
};

NS_CC_END

#endif//__FASTNOTIFICATIONCENTER_H__

