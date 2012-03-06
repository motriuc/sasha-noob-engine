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

/**
 *
 */
class GestureTap
{
public:
	GestureTap()
	{
	}
	
	GestureTap( const System::d3Math::d3Vector& pos ) :
		_position( pos )
	{
	}
	
	const System::d3Math::d3Vector& Position() const
	{
		return _position;
	}
	
private:	
	System::d3Math::d3Vector	_position;
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

	GestureEvent( Type type ) :
		_type( type )
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