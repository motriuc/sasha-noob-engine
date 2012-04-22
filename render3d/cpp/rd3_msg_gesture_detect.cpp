/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_msg_gesture_detect.cpp
//  Created                 : 10 2 2012   19:58
//  File path               : SLibF\render3d\cpp
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

#include "rd3afx.h"
#include "rd3_msg_gesture_detect.h"
#include "rd3_msg_gesture.h"
#include "rd3_edata.h"

namespace Rd3
{
	
/////////////////////////////////////////////////////////////////////
// GestureDetect
/////////////////////////////////////////////////////////////////////
	
//-------------------------------------------------------------------	
GestureDetect::GestureDetect( )
{
}

//-------------------------------------------------------------------	
void GestureDetect::Process( EngineData& edata, const GestureEvent& gestureEvent )
{
	if( Tap.IsEnabled() )
		Tap.Process( edata, gestureEvent );
	
	if( Swipe.IsEnabled() )
		Swipe.Process( edata, gestureEvent, _prevGestureEvent  );
	
	_prevGestureEvent = gestureEvent;
}
	
//-------------------------------------------------------------------	
void GestureDetect::Idle( EngineData& edata )
{
}

/////////////////////////////////////////////////////////////////////
// GestureDetect_Base
/////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------	
void GestureDetect_Base::SetBBox( const d2Rectangle& rc )
{
	_bbox = d3AABBox(
		d3Vector( rc.Min().x, rc.Min().y, -1.0f ),
		d3Vector( rc.Max().x, rc.Max().y, 1.0f )
	);
}

/////////////////////////////////////////////////////////////////////
// GestureDetect_Tap
/////////////////////////////////////////////////////////////////////
	
//-------------------------------------------------------------------	
GestureDetect_Tap::GestureDetect_Tap() :
	_bTap( sFalse )
{
}
	
//-------------------------------------------------------------------	
void GestureDetect_Tap::Process( EngineData& edata, const GestureEvent& gestureEvent )
{
	if( gestureEvent.Taps().Size() != 1 )
	{
		_bTap = sFalse;
	}
	else switch ( gestureEvent.GetType() )
	{
		case GestureEvent::E_Begin:
			_bTap = GetBBox().IsEmpty() || GetBBox().Intersect( gestureEvent.Taps()[0].Position() );
			break;
		case GestureEvent::E_Move:
			_bTap = sFalse;
			break;
		case GestureEvent::E_End:
			if( _bTap )
			{
				if( GetBBox().IsEmpty() || GetBBox().Intersect( gestureEvent.Taps()[0].Position() ) )
					onTap( edata, gestureEvent.Taps()[0].Position() );
				_bTap = sFalse;
			}
			break;
	}
}
	
/////////////////////////////////////////////////////////////////////
// GestureDetect_Swipe
/////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------	
GestureDetect_Swipe::GestureDetect_Swipe() :
	_bSwipe( sFalse )
{
}

//-------------------------------------------------------------------	
void GestureDetect_Swipe::Process( EngineData& edata, const GestureEvent& gestureEvent, const GestureEvent& prevGestureEvent )
{
	switch( gestureEvent.GetType() )
	{
	case GestureEvent::E_Move:
		{
			if( _bSwipe && gestureEvent.Taps().Size() == prevGestureEvent.Taps().Size() )
			{
				d3Vector move( 0.0f );
		
				for( sInt i = 0; i < gestureEvent.Taps().Size(); ++i )
				{
					d3Vector v =  gestureEvent.Taps()[i].Position() - prevGestureEvent.Taps()[i].Position();
			
					move.x = FMath::AbsMax( v.x, move.x );
					move.y = FMath::AbsMax( v.y, move.y );
					move.z = FMath::AbsMax( v.z, move.z );
				}

				if( !FMath::CloseToZero( move.Magnitude2() ) )
				{
					onSwipe( edata, move );
				}
			}
		}
		break;
	case GestureEvent::E_Begin:
		{
			if( GetBBox().IsEmpty() )
				_bSwipe = sTrue;
			else
			{
				_bSwipe = sFalse;
				for( sInt i = 0; i < gestureEvent.Taps().Size(); ++i )
				{
					_bSwipe = GetBBox().Intersect( gestureEvent.Taps()[i].Position() );
					if( _bSwipe )
						break;
				}
			}
		}
		break;
	}
}

//-------------------------------------------------------------------	

}