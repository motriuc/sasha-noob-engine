/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_msg_gesture.h
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

#ifndef _RD3_MSG_GESTURE_INC_
#define _RD3_MSG_GESTURE_INC_

namespace Rd3
{

using namespace System::d3Math;
using namespace System::d2Math;
	
/**
 * GestureTap
 */
class GestureTap
{
public:
	GestureTap()
	{
	}
	
	GestureTap( const d3Point& pos, d3Float acc = 0.0f ) :
		_position( pos ),
		_acceleration( acc )
	{
	}
	
	const d3Point& Position() const
	{
		return _position;
	}
	
	d3Float Acceleration() const
	{
		return _acceleration; 
	}

private:	
	d3Point	_position;
	d3Float	_acceleration;
};

typedef System::Cnt::sVector<GestureTap>  GestureTaps;

/**
 * GestureEvent
 */
class GestureEvent
{
public:
	
	enum Type
	{
		E_Begin,
		E_Move,
		E_End
	};

	GestureEvent()
	{
	}
	
	GestureEvent( Type type ) :
		_type( type ),
		_taps( 2 )
	{
	}
	
	/**
	 *
	 */
	void Add( const GestureTap& tap )
	{
		_taps.Add( tap );
	}
	
	/**
	 *
	 */
	Type GetType() const
	{
		return _type;
	}
	
	const GestureTaps& Taps() const
	{
		return _taps;
	}
private:	
	Type			_type;
	GestureTaps		_taps;
};

/**
 * GestureDetect2D
 */
class GestureDetect
{
public:
	enum Gestures
	{
		eTap				= 1,
		eSwipe				= 2,
		eSwipeAcceleration	= 4,
		eZoom				= 8,
		eRotate				= 16
	};
public:
	GestureDetect( sUInt gestures );

	/**
	 *
	 */
	void Process( EngineData& edata, const GestureEvent& gestureEvent );

	void Idle( EngineData& edata );

	Events::sEvent2<EngineData&, const d3Point& /*tap position*/>		onTap;
	Events::sEvent2<EngineData&, const d3Vector& /*delta swipe*/ > onSwipe;

private:
	sUInt		_enabledGestures;
	sUInt		_inProgressGestures;

	sVector<d3Vector>	_positions;
private:
	void ProcessBegin( EngineData& edata, const GestureEvent& gestureEvent );
	void ProcessMove( EngineData& edata, const GestureEvent& gestureEvent );
	void ProcessEnd( EngineData& edata, const GestureEvent& gestureEvent );
};

}

#endif // _RD3_MSG_GESTURE_INC_