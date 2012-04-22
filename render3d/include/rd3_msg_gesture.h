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
	
	GestureTap( const d3Point& pos, sDouble time ) :
		_position( pos ),
		_time( time )
	{
	}
	
	const d3Point& Position() const
	{
		return _position;
	}
		
	sDouble Time() const
	{
		return _time;
	}

private:	
	d3Point	_position;
	sDouble _time;
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

}

#endif // _RD3_MSG_GESTURE_INC_