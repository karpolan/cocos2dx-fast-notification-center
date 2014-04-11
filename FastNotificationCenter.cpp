/******************************************************************************

FastNotificationCenter

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

#include "cocos2d.h"
#include "FastNotificationCenter.h"
//#include "cocoa/CCArray.h"
//#include "script_support/CCScriptSupport.h"
//#include <string>

using namespace std;

USING_NS_CC;

//=============================================================================
// FastNotificationObserver
//=============================================================================

FastNotificationObserver::FastNotificationObserver()
{
	this->CreateParams(NULL, NULL, NULL, 0, "");
}

//-----------------------------------------------------------------------------

FastNotificationObserver::FastNotificationObserver(CCObject * target, SEL_CallFuncO function, CCObject* object, const unsigned int code, const char* name)
{
	this->CreateParams(target, function, object, code, name);
}

//-----------------------------------------------------------------------------

FastNotificationObserver::~FastNotificationObserver()
{
    CC_SAFE_DELETE_ARRAY(_name);
}

//-----------------------------------------------------------------------------

void FastNotificationObserver::CreateParams(CCObject * target, SEL_CallFuncO function, CCObject* object, const unsigned int code, const char* name)
{
    _target = target;
    _function = function;
    _object = object;
    _code = code;

	_name = "";
	if (name == NULL) return; // Fix for NULL name
	
	// Copy name to internal field
	_name = new char[strlen(name) + 1];
    memset(_name, 0, strlen(name) + 1);
    
    string orig(name);
    orig.copy(_name,strlen(name), 0);
	
//    _handler = 0;
}

//-----------------------------------------------------------------------------

void FastNotificationObserver::performFunction(CCObject* object)
{
    if (_target)
    {
		if (object) {
			(_target->*_function)(object);
		} else {
			(_target->*_function)(_object);
		}
    }
}

//-----------------------------------------------------------------------------
// Properties
//-----------------------------------------------------------------------------

unsigned int FastNotificationObserver::getCode()
{
    return _code;
}

CCObject* FastNotificationObserver::getTarget()
{
    return _target;
}

SEL_CallFuncO FastNotificationObserver::getFunction()
{
    return _function;
}

char* FastNotificationObserver::getName()
{
    return _name;
}

CCObject* FastNotificationObserver::getObject()
{
    return _object;
}

/*
int FastNotificationObserver::getHandler()
{
    _handler;
}

void FastNotificationObserver::setHandler(int var)
{
    _handler = var;
}
*/


//=============================================================================
// FastNotificationCenter
//=============================================================================

FastNotificationCenter::FastNotificationCenter()
{
	observers = CCArray::createWithCapacity(3);
	observers->retain();
}

//-----------------------------------------------------------------------------

FastNotificationCenter::~FastNotificationCenter()
{
	observers->release();
}


//-----------------------------------------------------------------------------
// Singleton
//-----------------------------------------------------------------------------

static FastNotificationCenter *_FastNotificationCenter = NULL;

FastNotificationCenter *FastNotificationCenter::sharedObject(void)
{
	if (!_FastNotificationCenter) _FastNotificationCenter = new FastNotificationCenter;
	return _FastNotificationCenter;
}

//-----------------------------------------------------------------------------

void FastNotificationCenter::sharedObjectFree()
{
	CC_SAFE_RELEASE_NULL(_FastNotificationCenter);
}


//-----------------------------------------------------------------------------
// Observer routines
//-----------------------------------------------------------------------------

unsigned int FastNotificationCenter::getObserversCount(void)
{
	return observers->count();
}

//-----------------------------------------------------------------------------

FastNotificationObserver* FastNotificationCenter::findObserver(CCObject* target, const char *name)
{
	CCObject* obj = NULL;
	CCARRAY_FOREACH(observers, obj)
	{
		FastNotificationObserver* observer = (FastNotificationObserver*) obj;
		if (!observer) continue;
  
		if (!strcmp(observer->getName(), name) && observer->getTarget() == target)
		return observer;
	}
	return NULL;
}

//-----------------------------------------------------------------------------

FastNotificationObserver* FastNotificationCenter::findObserver(CCObject* target, const unsigned int code)
{
	CCObject* obj = NULL;
	CCARRAY_FOREACH(observers, obj)
	{
		FastNotificationObserver* observer = (FastNotificationObserver*) obj;
		if (!observer) continue;
  
		if ((observer->getCode() == code) && observer->getTarget() == target)
		return observer;
	}
	return NULL;
}

//-----------------------------------------------------------------------------

FastNotificationObserver* FastNotificationCenter::addObserver(CCObject* target, SEL_CallFuncO function, CCObject* object,  const char* name)
{
	FastNotificationObserver* observer = findObserver(target, name);
	if (observer) return observer; // Already exists

	observer = new FastNotificationObserver(target, function, object, 0, name);

	if (!observer) return NULL; // Failed to create

	observer->autorelease();
	observers->addObject(observer); // Add to own list

	return observer;
}

//-----------------------------------------------------------------------------

FastNotificationObserver* FastNotificationCenter::addObserver(CCObject* target, SEL_CallFuncO function, CCObject* object, const unsigned int code)
{
	FastNotificationObserver* observer = findObserver(target, code);
	if (observer) return observer; // Already exists

	observer = new FastNotificationObserver(target, function, object, code, "");

	if (!observer) return NULL; // Failed to create

	observer->autorelease();
	observers->addObject(observer); // Add to own list

	return observer;
}

//-----------------------------------------------------------------------------

int FastNotificationCenter::removeObserver(CCObject* target, const char* name)
{
	int count = 0;
	CCObject* obj = NULL;
	CCARRAY_FOREACH(observers, obj)
	{
		FastNotificationObserver* observer = (FastNotificationObserver*) obj;
		if (!observer) continue;
  
		if (observer->getTarget() == target && !strcmp(observer->getName(), name))
		{
			observers->removeObject(observer);
			count++;
		}
	}
	return count;
}

//-----------------------------------------------------------------------------

int FastNotificationCenter::removeObserver(CCObject* target, const unsigned int code)
{
	int count = 0;
	CCObject* obj = NULL;
	CCARRAY_FOREACH(observers, obj)
	{
		FastNotificationObserver* observer = (FastNotificationObserver*) obj;
		if (!observer) continue;
  
		if (observer->getTarget() == target && observer->getCode() == code)
		{
			observers->removeObject(observer);
			count++;
		}
	}
	return count;
}

//-----------------------------------------------------------------------------

int FastNotificationCenter::removeAllObservers(CCObject *target)
{
	CCObject* obj = NULL;
	CCArray* toRemove = CCArray::create();
	CCARRAY_FOREACH(observers, obj)
	{
		FastNotificationObserver* observer = (FastNotificationObserver*) obj;
		if (!observer)
			continue;

		if (observer->getTarget() == target || target == NULL)
		{
			toRemove->addObject(observer);
		}
	}
	observers->removeObjectsInArray(toRemove);
	return toRemove->count();
}


//-----------------------------------------------------------------------------
// Notification routines
//-----------------------------------------------------------------------------

int FastNotificationCenter::postNotification(const char *name, CCObject *object)
{
	int count = 0;

	CCArray* ObserversCopy = CCArray::createWithCapacity(observers->count());
	ObserversCopy->addObjectsFromArray(observers);
	
	CCObject* obj = NULL;
	CCARRAY_FOREACH(ObserversCopy, obj)
	{
		FastNotificationObserver* observer = (FastNotificationObserver*) obj;
		if (!observer) continue;
  
		if ((observer->getObject() == object || observer->getObject() == NULL || object == NULL) && !strcmp(name, observer->getName()))
		{
/*	
		if (observer->getHandler() != 0)
			{
				CCScriptEngineProtocol* engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
				engine->executeNotificationEvent(this, name);
			}
			else
*/
			{
				observer->performFunction(object);
			}
			count++;
		}
	}

	return count;
}

//-----------------------------------------------------------------------------

int FastNotificationCenter::postNotification(const char *name)
{
	return this->postNotification(name, NULL);
}

//-----------------------------------------------------------------------------

int FastNotificationCenter::postNotification(const unsigned int code, CCObject* object)
{
	int count = 0;

	CCArray* ObserversCopy = CCArray::createWithCapacity(observers->count());
	ObserversCopy->addObjectsFromArray(observers);
	
	CCObject* obj = NULL;
	CCARRAY_FOREACH(ObserversCopy, obj)
	{
		FastNotificationObserver* observer = (FastNotificationObserver*) obj;
		if (!observer) continue;
  
		if ((observer->getCode() == code) && (observer->getObject() == object || observer->getObject() == NULL || object == NULL))
		{
/*			if (observer->getHandler() != 0)
			{
				CCScriptEngineProtocol* engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
				engine->executeNotificationEvent(this, name);
			}
			else
*/
			{
				observer->performFunction(object);
			}
			count++;
		}
	}

	return count;
}

//-----------------------------------------------------------------------------

int FastNotificationCenter::postNotification(const unsigned int code)
{
	return this->postNotification(code, NULL);
}

//-----------------------------------------------------------------------------
