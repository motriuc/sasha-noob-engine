/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_msg_gesture_detect.h
//  Created                 : 10 2 2012   19:58
//  File path               : SLibF\render3d\include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

#ifndef _RD3_MSG_GESTURE_DETECT_INC_
#define _RD3_MSG_GESTURE_DETECT_INC_

#include "rd3_msg_gesture.h"

namespace Rd3
{

using namespace System::d3Math;
using namespace System;

class GestureDetect;

/**
 * GestureDetect_Base
 */
class GestureDetect_Base
{
public:	
	void Enable()									{ _bEnabled = sTrue; }
protected:
	GestureDetect_Base()							: _bEnabled( sFalse )	{}
	sBool IsEnabled() const							{ return _bEnabled; }
private:
	sBool	_bEnabled;	
	friend class GestureDetect;
};
	
/**
 * GestureDetect_Tap
 */
class GestureDetect_Tap : public GestureDetect_Base
{
public:
	GestureDetect_Tap();
	
	Events::sEvent2<EngineData&, const d3Point& /*tap position*/>  onTap;	
private:
	sBool	_bTap;
private:	
	void Process( EngineData& edata, const GestureEvent& gestureEvent );	
	friend class GestureDetect;
};

	
/**
 * GestureDetect_Swipe
 */
class GestureDetect_Swipe : public GestureDetect_Base
{
public:
	GestureDetect_Swipe();
	Events::sEvent2<EngineData&, const d3Vector& /*delta*/>  onSwipe;	
private:
		
	void Process( EngineData& edata, const GestureEvent& gestureEvent, const GestureEvent& prevGestureEvent );	
	friend class GestureDetect;	
};
	
/**
 * GestureDetect
 */
class GestureDetect
{
public:
	GestureDetect();
	void Process( EngineData& edata, const GestureEvent& gestureEvent );
	void Idle( EngineData& edata );
public:
	GestureDetect_Tap		Tap;
	GestureDetect_Swipe		Swipe;
private:	
	GestureEvent			_prevGestureEvent;
};
	
	
}

#endif // _RD3_MSG_GESTURE_DETECT_INC_