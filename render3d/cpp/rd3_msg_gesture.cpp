/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_msg_gesture.cpp
//	Created                 : 10 2 2012   19:58
//	File path               : SLibF\render3d\include
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//	Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

#include "rd3afx.h"
#include "rd3_msg_gestureq.h"

namespace Rd3
{
//-------------------------------------------------------------------	
GestureMsgQueue::GestureMsgQueue( Render* owner, const sString& objectName ):
	_BaseClass( owner, objectName )
{	
}
	
//-------------------------------------------------------------------	
// GestureDetect
//-------------------------------------------------------------------	
GestureDetect::GestureDetect( sUInt gestures ) :
	_enabledGestures( gestures )
{
}

//-------------------------------------------------------------------	
void GestureDetect::Process( EngineData& edata, const GestureEvent& gestureEvent )
{
	switch( gestureEvent.GetType() )
	{
	case GestureEvent::E_Begin:
		ProcessBegin( edata, gestureEvent );
		break;
	case GestureEvent::E_Move:
		ProcessMove( edata, gestureEvent );
		break;
	case GestureEvent::E_End:
		ProcessEnd( edata, gestureEvent );
		break;
	}
}

//-------------------------------------------------------------------	
void GestureDetect::Idle( EngineData& edata )
{

}

//-------------------------------------------------------------------	
void GestureDetect::ProcessEnd( EngineData& edata, const GestureEvent& gestureEvent )
{
	// tap
	if( _inProgressGestures & eTap )
	{
		onTap( edata, gestureEvent.Taps()[0].Position() );

		_inProgressGestures &= ~( eTap );
	}

	// swipe
	if( _inProgressGestures & eSwipe )
	{
		d3Vector delta = gestureEvent.Taps()[0].Position() - _positions[0];
		onSwipe( edata, delta );
		_inProgressGestures &= ~( eSwipe );
	}

	_positions.RemoveAll();
}

//-------------------------------------------------------------------	
void GestureDetect::ProcessMove( EngineData& edata, const GestureEvent& gestureEvent )
{
	// remove tap gesture
	_inProgressGestures &= ~( eTap );

	// swipe
	if( _inProgressGestures & eSwipe )
	{
		d3Vector delta = gestureEvent.Taps()[0].Position() - _positions[0];
		onSwipe( edata, delta );
	}


	// fill move data
	_positions.RemoveAll();
	for( sInt i = 0; i < gestureEvent.Taps().Size(); ++i )
	{
		_positions.Add( gestureEvent.Taps()[i].Position() );
	}
}

//-------------------------------------------------------------------	
void GestureDetect::ProcessBegin( EngineData& edata, const GestureEvent& gestureEvent )
{
	_positions.RemoveAll();

	for( sInt i = 0; i < gestureEvent.Taps().Size(); ++i )
	{
		_positions.Add( gestureEvent.Taps()[i].Position() );
	}
	
	_inProgressGestures = _enabledGestures;

	if( _positions.Size() != 1 )
	{
		_inProgressGestures &= ~( eTap );
	}

	if( _positions.Size() != 2 )
	{
		_inProgressGestures &= ~( eZoom | eRotate );
	}
}

//-------------------------------------------------------------------	

}