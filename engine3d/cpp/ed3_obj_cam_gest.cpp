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
#include "ed3_world.h"
#include "ed3_edata.h"

#include "rd3_msg_gesture.h"
#include "rd3_render.h"

namespace Ed3
{
	
//-----------------------------------------------------------------------	
d3CameraGestureObject::d3CameraGestureObject() :
	_move( 0.0f )
{
	RemoveState( OBS_VISIBLE );

	_gestureDetect.Swipe.Enable();
	_gestureDetect.Swipe.onSwipe = Events::Event( this, &d3CameraGestureObject::OnGestureSwipe ); 

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
	_gestureDetect.Idle( edata );

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
d3Float GestureDistance( const d3Point& p1, const d3Point& p2, const d3Point& np1, const d3Point& np2 )
{
	d3Point center = ( p1 + p2 ) * 0.5f;
	
	d3Float d1 = (np1 - center).Magnitude() - (p1 - center).Magnitude();
	d3Float d2 = (np2 - center).Magnitude() - (p2 - center).Magnitude();
	
	return d1 + d2;
}

//-------------------------------------------------------------------
void d3CameraGestureObject::OnGestureTap( Rd3::EngineData& edata, const d3Point& position )
{
}

//-------------------------------------------------------------------
void d3CameraGestureObject::OnGestureSwipe( Rd3::EngineData& edata, const d3Vector& delta )
{
	_move = delta;
	_move.y = -_move.y;
}

//-------------------------------------------------------------------
void d3CameraGestureObject::OnGestureEvent( Rd3::EngineData& edata, const Rd3::GestureEvent& event )
{
	_gestureDetect.Process( edata, event );
}
	
}