////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_obj_cam_gest.cpp
//  Created            : 2 2 2012   19:09
//  Author             : Alexandru Motriuc  
//  File Path          : SLibF\engine3d\cpp
//  System independent : 0%
//  Library            : 
//
//  Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////
#include "ed3afx.h"
#include "ed3_obj_cam_gest.h"
#include "ed3_obj_factory.h"
#include "rd3_msg_gesture.h"
#include "rd3_render.h"
#include "ed3_world.h"

namespace Ed3
{
	
//-----------------------------------------------------------------------	
d3CameraGestureObject::d3CameraGestureObject() :
	_move( 0.0f ),
	_lastPosition( 0.0f )
{
	RemoveState( OBS_VISIBLE );
}

//-------------------------------------------------------------------
void d3CameraGestureObject::Initialize( Rd3::Render& render ) throws_error
{
	render.MessageQueue_RegisterEvent(
		_S("engine.msg.gesture"), 
		Events::Event( this, &d3CameraGestureObject::OnGestureEvent )
	);
	
	_BaseClass::Initialize( render );
}
	
//-------------------------------------------------------------------
void d3CameraGestureObject::Uninitialize( Rd3::Render& render )
{
	render.MessageQueue_UnregisterEvent(
		_S("engine.msg.gesture"), 
		Events::Event( this, &d3CameraGestureObject::OnGestureEvent )
	);
	_BaseClass::Uninitialize( render );
}
	
//-------------------------------------------------------------------
void d3CameraGestureObject::LoadFromXML( const Xml::BaseDomNode& element, Ed3::LoadDataParams& loadParams ) throws_error
{
	_BaseClass::LoadFromXML( element, loadParams );
}

//-------------------------------------------------------------------
void d3CameraGestureObject::Render( const Ed3::d3RenderData& renderData )
{
}
	
//-------------------------------------------------------------------
void d3CameraGestureObject::AI( d3EngineData& edata )
{
	if( _move != d3Vector( 0.0f ) )
	{
		d3World* world = GetWorld();
		_move.x = -_move.x;
		_move *= 2.0f;
		
		world->GetCamera().Move( _move );
		_move = d3Vector( 0.0f );
	}
}
	
//-------------------------------------------------------------------
void d3CameraGestureObject::OnGestureEvent( Rd3::EngineData& edata, const Rd3::GestureEvent& event )
{
	switch ( event.GetType() )
	{
		case Rd3::GestureEvent::E_Begin:
			if( event.Taps().Size() == 1 )
				_lastPosition = event.Taps()[0].Position();
			break;
			
		case Rd3::GestureEvent::E_Move:
			if( event.Taps().Size() == 1 )
			{
				d3Vector delta = event.Taps()[0].Position() - _lastPosition;
				_lastPosition = event.Taps()[0].Position();
				_move += delta;
			}
			else 
			{
				_move = d3Vector( 0.0f );
			}
			break;
		
		case Rd3::GestureEvent::E_End:
			_move = d3Vector( 0.0f );
			break;
			
		default:
			break;
	}
}
	
	
}