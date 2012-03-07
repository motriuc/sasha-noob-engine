////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_obj_cam_key.cpp
//  Created            : 6 3 2012   19:09
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
#include "ed3_obj_cam_key.h"
#include "ed3_world.h"

#include "rd3_msg_keyboard.h"
#include "rd3_render.h"
#include "rd3_edata.h"

namespace Ed3
{
	
//-----------------------------------------------------------------------	
d3CameraKeyboardObject::d3CameraKeyboardObject():
	_moveStep( 0.8f ),
	_rotateStep( 0.5f )
{
	RemoveState( OBS_VISIBLE );
}

//-------------------------------------------------------------------
void d3CameraKeyboardObject::Initialize( Rd3::Render& render ) throws_error
{
	render.MessageQueue_RegisterEvent(
		_S("engine.msg.key"), 
		Events::Event( this, &d3CameraKeyboardObject::OnKeyboardMessage )
	);

	_BaseClass::Initialize( render );
}
	
//-------------------------------------------------------------------
void d3CameraKeyboardObject::Uninitialize( Rd3::Render& render )
{
	render.MessageQueue_UnregisterEvent(
		_S("engine.msg.key"), 
		Events::Event( this, &d3CameraKeyboardObject::OnKeyboardMessage )
	);

	_BaseClass::Uninitialize( render );
}
	
//-------------------------------------------------------------------
void d3CameraKeyboardObject::LoadFromXML( const Xml::BaseDomNode& element, Ed3::LoadDataParams& loadParams ) throws_error
{
	_BaseClass::LoadFromXML( element, loadParams );
}

//-------------------------------------------------------------------
void d3CameraKeyboardObject::Render( const Ed3::d3RenderData& renderData )
{
}
	
//-------------------------------------------------------------------
void d3CameraKeyboardObject::AI( d3EngineData& edata )
{
}	

//-------------------------------------------------------------------
void d3CameraKeyboardObject::OnKeyboardMessage( Rd3::EngineData& edata, const Rd3::KeyboardEvent& key )
{
	d3World* pWorld = GetWorld();

	if( key.IsKeyPressed( Rd3::KeyboardKeys::E_LEFT_ALT ) )
	{
		if( key.IsKeyPressed( Rd3::KeyboardKeys::E_LEFT ) )
		{
			pWorld->GetCamera().RotateView( _rotateStep * edata.GetDeltaTime() );
		}
		if( key.IsKeyPressed( Rd3::KeyboardKeys::E_RIGHT ) )
		{
			pWorld->GetCamera().RotateView( -_rotateStep * edata.GetDeltaTime() );
		}
	}
	else if( key.IsKeyPressed( Rd3::KeyboardKeys::E_LEFT_CONTROL ) )
	{
		if(  key.IsKeyPressed( Rd3::KeyboardKeys::E_LEFT ) )
		{
			pWorld->GetCamera().RotateLeft( _rotateStep * edata.GetDeltaTime() );
		}
		if(  key.IsKeyPressed( Rd3::KeyboardKeys::E_RIGHT ) )
		{
			pWorld->GetCamera().RotateLeft( -_rotateStep * edata.GetDeltaTime() );
		}
		if(  key.IsKeyPressed( Rd3::KeyboardKeys::E_UP ) )
		{
			pWorld->GetCamera().RotateUp( _rotateStep * edata.GetDeltaTime() );
		}
		if(  key.IsKeyPressed( Rd3::KeyboardKeys::E_DOWN ) )
		{
			pWorld->GetCamera().RotateUp( -_rotateStep * edata.GetDeltaTime() );
		}

#ifdef _D3_DEBUG_RENDER
		if(  key.IsKeyJustPressed( Rd3::KeyboardKeys::E_B ) )
		{
			edata.ModifyCommonData().debug_SetTestBoundingBox( !edata.ModifyCommonData().debug_TestBoundingBox() );
		}
#endif
	}
	else
	{
		if(  key.IsKeyPressed( Rd3::KeyboardKeys::E_UP ) )
		{
			pWorld->GetCamera().MoveForward( _moveStep * edata.GetDeltaTime() );
		}
		if(  key.IsKeyPressed( Rd3::KeyboardKeys::E_DOWN ) )
		{
			pWorld->GetCamera().MoveForward( -_moveStep * edata.GetDeltaTime() );
		}
		if(  key.IsKeyPressed( Rd3::KeyboardKeys::E_PAGE_UP ) )
		{
			pWorld->GetCamera().MoveUp( _moveStep * edata.GetDeltaTime() );
		}
		if(  key.IsKeyPressed( Rd3::KeyboardKeys::E_PAGE_DOWN ) )
		{
			pWorld->GetCamera().MoveUp( -_moveStep * edata.GetDeltaTime() );
		}
		if(  key.IsKeyPressed( Rd3::KeyboardKeys::E_LEFT ) )
		{
			pWorld->GetCamera().MoveLeft( _moveStep * edata.GetDeltaTime() );
		}
		if(  key.IsKeyPressed( Rd3::KeyboardKeys::E_RIGHT ) )
		{
			pWorld->GetCamera().MoveLeft( -_moveStep * edata.GetDeltaTime() );
		}
		if(  key.IsKeyJustPressed( Rd3::KeyboardKeys::E_W ) )
		{
			edata.ModifyCommonData().SetRenderWireframe( !edata.ModifyCommonData().RenderWireframe() );
		}

#ifdef _D3_DEBUG_RENDER
		if(  key.IsKeyJustPressed( Rd3::KeyboardKeys::E_B ) )
		{
			edata.ModifyCommonData().debug_SetRenderObjectsBoundingBox( !edata.ModifyCommonData().debug_RenderObjectsBoundingBox() );
		}
		if(  key.IsKeyJustPressed( Rd3::KeyboardKeys::E_C ) )
		{
			edata.ModifyCommonData().debug_SetRenderCulling( !edata.ModifyCommonData().debug_RenderCulling() );
		}
#endif
	}
}
}