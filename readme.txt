Faster analog to cocos2d::CCNotificationCenter with notification by numeric codes

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


//=============================================================================
// FastNotificationObserver
//=============================================================================
// Class to hold notification for some "Target" object. 
// The "Function" is called when notification by "Name" or "Code" is fired. 
// The "Object" is optional parameter, can be used to pass some additional data 
// into the "Function" during notification.
// Note: analog of CCNotificationObserver standard class.

class FastNotificationObserver : public CCObject


//=============================================================================
// FastNotificationCenter
//=============================================================================
// Class holds and manages array of FastNotificationObserver objects. 
// Can be used as singleton via sharedObjectXXX routines.
// Notifications by "Code" or "Name" are fired by postNotification() methods.
// Note: analog of CCNotificationCenter standard class.

class FastNotificationCenter : public CCObject


Copyright (c) KARPOLAN 
http://karpolan.com

