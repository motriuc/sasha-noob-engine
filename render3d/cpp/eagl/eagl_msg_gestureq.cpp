//  File Name               : eagl_msg_keyboardq.cpp
//  Created                 : 14 3 2012   19:58
//  File path               : SLibF\render3d\cpp\dx9
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
#include "rd3_edata.h"
#include "eagl_conf.h"
#include "eagl_msg_gestureq.h"

//------------------------------------------------------------------
EaglGestureMsgQueue::EaglGestureMsgQueue( Rd3::Render* owner, const sString& objectName ) :
	_BaseClass( owner, objectName )
{
}

//------------------------------------------------------------------
void EaglGestureMsgQueue::PostMessage( const Rd3::GestureEvent& event )
{
	_events.Add( event );
}

//------------------------------------------------------------------
void EaglGestureMsgQueue::ProcessMessages( Rd3::EngineData& edata )
{
	if( _events.Size() > 0 )
	{
		SendMessage( edata, _events[0] );
		_events.RemoveAt( 0 );
	}
}

//------------------------------------------------------------------
EaglGestureMsgQueue::~EaglGestureMsgQueue()
{
}

