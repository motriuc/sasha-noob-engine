/////////////////////////////////////////////////////////////////////
//  File Name				: ed3_object_lua.cpp
//  Created					: 18 2 2012   20:02
//  File path				: SLibF\engine3d\cpp
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

#include "ed3afx.h"
#include "ed3_object.h"
#include "ed3_edata.h"
#include "rd3_perf_counters.h"
#include "ed3_world.h"

#ifdef ED3_ENGINE_USE_PHYSICS
#include "ed3_physics_world.h"
#include "ed3_physics_shape.h"
#include "ed3_physics_shapes.h"
#endif 

#define LUA_FUNCTION_AI				_S("d3Object_AI")
#define LUA_FUNCTION_INIT			_S("d3Object_Init")
#define LUA_FUNCTION_KEYBOARD		_S("d3Object_Keyboard")

//--------------------------------------------------------------------------------------------------------
COUNTER_USE( rd3_render_time_lua )
//--------------------------------------------------------------------------------------------------------

namespace Ed3 
{

#ifdef ED3_ENGINE_USE_LUA

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// self.
//////////////////////////////////////////////////////////////////////////////////////////////////////////
	
//--------------------------------------------------------------------------------------------------------
static int d3Object_Move( const LuaFunctionState* s )
{	
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
	
	if( me != NULL )
	{
		d3Float dx = s->GetValue( 0, 0.0f );
		d3Float dy = s->GetValue( 1, 0.0f );
		d3Float dz = s->GetValue( 2, 0.0f );

		d3Matrix move;
		move.SetTranslation( d3Vector( dx, dy, dz ) );
		
		me->ApplyTranformation( move );
	}
	
	return 0;
}
	
//--------------------------------------------------------------------------------------------------------
static int d3Object_RotateX( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
	
	if( me != NULL )
	{
		d3Float al = s->GetValue( 0, 0.0f );
		
		d3Matrix rot;
		rot.SetRotateX( al );

		me->ApplyTranformation( rot );
	}
	
	return 0;
}

//--------------------------------------------------------------------------------------------------------
static int d3Object_RotateY( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
		
	if( me != NULL )
	{
		d3Float al = s->GetValue( 0, 0.0f );
			
		d3Matrix rot;
		rot.SetRotateY( al );
			
		me->ApplyTranformation( rot );
	}
		
	return 0;
}


//--------------------------------------------------------------------------------------------------------
static int d3Object_RotateZ( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
		
	if( me != NULL )
	{
		d3Float al = s->GetValue( 0, 0.0f );
			
		d3Matrix rot;
		rot.SetRotateZ( al );
			
		me->ApplyTranformation( rot );
	}
		
	return 0;
}

//--------------------------------------------------------------------------------------------------------
static int d3Object_Scale( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
		
	if( me != NULL )
	{
		d3Float sx = s->GetValue( 0, 1.0f );
		d3Float sy = s->GetValue( 1, 1.0f );
		d3Float sz = s->GetValue( 2, 1.0f );
		
		d3Matrix scale;
		scale.SetScale( sx,sy,sz );
		
		me->ApplyTranformation( scale );
	}
		
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// world.camera
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------------
static int d3World_CameraMove( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
	
	if( me != NULL )
	{
		d3World* world = me->GetWorld();
		if( world != NULL )
		{
			d3Float dx = s->GetValue( 0, 0.0f );
			d3Float dy = s->GetValue( 1, 0.0f );
			d3Float dz = s->GetValue( 2, 0.0f );
			
			world->GetCamera().Move( d3Vector( dx, dy, dz ) );
		}
	}
	
	return 0;
}
//--------------------------------------------------------------------------------------------------------
static int d3World_CameraMoveForward( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
		
	if( me != NULL )
	{
		d3World* world = me->GetWorld();
		if( world != NULL )
		{
			d3Float distance = s->GetValue( 0, 0.0f );
				
			world->GetCamera().MoveForward( distance );
		}
	}
		
	return 0;
}

//--------------------------------------------------------------------------------------------------------
static int d3World_CameraMoveUp( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
		
	if( me != NULL )
	{
		d3World* world = me->GetWorld();
		if( world != NULL )
		{
			d3Float distance = s->GetValue( 0, 0.0f );
				
			world->GetCamera().MoveUp( distance );
		}
	}
		
	return 0;
}

//--------------------------------------------------------------------------------------------------------
static int d3World_CameraRotateUp( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
		
	if( me != NULL )
	{
		d3World* world = me->GetWorld();
		if( world != NULL )
		{
			d3Float angle = s->GetValue( 0, 0.0f );
				
			world->GetCamera().RotateUp( angle );
		}
	}
		
	return 0;
}

//--------------------------------------------------------------------------------------------------------
static int d3World_CameraRotateLeft( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
		
	if( me != NULL )
	{
		d3World* world = me->GetWorld();
		if( world != NULL )
		{
			d3Float angle = s->GetValue( 0, 0.0f );
				
			world->GetCamera().RotateLeft( angle );
		}
	}
		
	return 0;
}

//--------------------------------------------------------------------------------------------------------
static int d3World_CameraLookAt( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
		
	if( me != NULL )
	{
		d3World* world = me->GetWorld();
		if( world != NULL )
		{
			d3Float x = s->GetValue( 0, 0.0f );
			d3Float y = s->GetValue( 1, 0.0f );
			d3Float z = s->GetValue( 2, 0.0f );
			
			world->GetCamera().SetLookAt( d3Vector( x, y, z ) );
		}
	}
		
	return 0;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// world.physics.
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ED3_ENGINE_USE_PHYSICS	
	
//--------------------------------------------------------------------------------------------------------
static int d3World_Physics_SetGravity( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
		
	if( me == NULL )
		return 0;
		
	d3World* world = me->GetWorld();
		
	if( world != NULL )
	{
		d3Float x = s->GetValue( 0, 0.0f );
		d3Float y = s->GetValue( 1, 0.0f );
		d3Float z = s->GetValue( 2, 0.0f );
		
		world->Physics().SetGravityVector( d3Vector( x, y, z ) );
	}
	
	return 0;
}

//--------------------------------------------------------------------------------------------------------
static int d3World_Physics_RigidBody_AddPlane( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
		
	if( me == NULL )
			return 0;
		
	d3World* world = me->GetWorld();
		
	if( world != NULL )
	{
		d3Float nx = s->GetValue( 0, 0.0f );
		d3Float ny = s->GetValue( 1, 0.0f );
		d3Float nz = s->GetValue( 2, 0.0f );
		
		d3Float pc = s->GetValue( 3, 0.0f );
		
		phStaticPlane* plane = new phStaticPlane( 
			me,
			d3Plane( d3Vector( nx, ny, nz ), pc )
		);
		
		s->Return( world->Physics().AddShape( plane ) );
	}
		
	return 0;
}

//--------------------------------------------------------------------------------------------------------
static int d3World_Physics_RigidBody_AddSphere( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
		
	if( me == NULL )
		return 0;
		
	d3World* world = me->GetWorld();
		
	if( world != NULL )
	{
		d3Float r = s->GetValue( 0, 0.0f );
		d3Float mass = s->GetValue( 1, 0.0f );
			
		phSphere* sphere = new phSphere( me, r, mass );
		s->Return( world->Physics().AddShape( sphere ) );
	}
		
	return 0;
}

//--------------------------------------------------------------------------------------------------------
static int d3World_Physics_Move( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
		
	if( me == NULL )
		return 0;
		
	d3World* world = me->GetWorld();
		
	if( world != NULL )
	{
		sInt id = s->GetValue( 0, -1 );
		d3Float nx = s->GetValue( 1, 0.0f );
		d3Float ny = s->GetValue( 2, 0.0f );
		d3Float nz = s->GetValue( 3, 0.0f );
		
		phShape* pShape = world->Physics().GetShape( id );
		
		if( pShape != NULL )
		{
			pShape->Move( d3Vector( nx, ny, nz ) );
		}
	}
		
	return 0;
}


#endif
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// render.afterEffect.
//////////////////////////////////////////////////////////////////////////////////////////////////////////
	
//--------------------------------------------------------------------------------------------------------
static int d3World_AfterEffect_SetParam( const LuaFunctionState* s )
{
	d3Object* me = reinterpret_cast<d3Object*> ( s->Me() );
	
	if( me == NULL )
		return 0;
	
	d3World* world = me->GetWorld();
		
	if( world != NULL )
	{
		Rd3::AfterEffect* effect = world->GetAfterEffect();
			
		if( effect != NULL )
		{
			sInt i = s->GetValue( 0, -1 );
			sString name = s->GetValue( 1, _S("") );
			d3Float v = s->GetValue( 2, 0.0f );
				
			if( i >= 0 && i < effect->ElementCount() )
			{
				effect->GetElement( i ).SetParam( name, v );
			}
		}
	}
		
	return 0;
}

//--------------------------------------------------------------------------------------------------------
void d3Object::LuaKeyboardMessage( Rd3::EngineData& edata, const Rd3::KeyboardEvent& key )
{
/*	static LuaFunctions fun[] = 
	{
		{ NULL, NULL }
	};
*/
	COUNTER_TIME_START( rd3_render_time_lua );
	_luaObject.Exec( LUA_FUNCTION_KEYBOARD, (void*)&key, NULL );
	COUNTER_TIME_STOP( rd3_render_time_lua );
}

//--------------------------------------------------------------------------------------------------------
void d3Object::InitLuaFunctions()
{	
	_luaObject.RegisterMathLib();
	_luaObject.Register( _S("self"), _S("RotateX"), d3Object_RotateX );
	_luaObject.Register( _S("self"), _S("RotateY"), d3Object_RotateY );
	_luaObject.Register( _S("self"), _S("RotateZ"), d3Object_RotateZ );
	_luaObject.Register( _S("self"), _S("Move"),    d3Object_Move );
	_luaObject.Register( _S("self"), _S("Scale"),   d3Object_Scale );
	
	// regirster world camera functions
	_luaObject.Register( _S("world.camera"), _S("Move"),		d3World_CameraMove );
	_luaObject.Register( _S("world.camera"), _S("MoveForward"),	d3World_CameraMoveForward );
	_luaObject.Register( _S("world.camera"), _S("MoveUp"),		d3World_CameraMoveUp );
	_luaObject.Register( _S("world.camera"), _S("RotateUp"),	d3World_CameraRotateUp );
	_luaObject.Register( _S("world.camera"), _S("RotateLeft"),	d3World_CameraRotateLeft );
	_luaObject.Register( _S("world.camera"), _S("LookAt"),		d3World_CameraLookAt );
	
	// physics
#ifdef ED3_ENGINE_USE_PHYSICS	
	_luaObject.Register( _S("world.physics"),			_S("SetGravity"),		d3World_Physics_SetGravity );

	_luaObject.Register( _S("world.physics.static"),	_S("AddPlane"),			d3World_Physics_RigidBody_AddPlane );
	_luaObject.Register( _S("world.physics.rbody"),		_S("AddSphere"),		d3World_Physics_RigidBody_AddSphere );
	_luaObject.Register( _S("world.physics"),			_S("Move"),				d3World_Physics_Move );
	
#endif // ED3_ENGINE_USE_PHYSICS
	
	
	//
	_luaObject.Register( _S("render.afterEffect"), _S("SetParam"), d3World_AfterEffect_SetParam );
	
}
	
//--------------------------------------------------------------------------------------------------------
void d3Object::LuaCallInit( Rd3::Render& render )
{
	if( _luaHasInit )
	{
		_luaObject.Exec( LUA_FUNCTION_INIT );
	}
}

//--------------------------------------------------------------------------------------------------------
void d3Object::LuaCallAI( d3EngineData& edata )
{
	if( _luaHasAI )
	{
		COUNTER_TIME_START( rd3_render_time_lua );
		
		_luaObject.Exec( LUA_FUNCTION_AI, edata.GetDeltaTime() );
		
		COUNTER_TIME_STOP( rd3_render_time_lua );
	}
}
	
//--------------------------------------------------------------------------------------------------------
void d3Object::LoadLua( const sString& path, LoadDataParams& loadParams ) throws_error
{
	if( path.Length() <= 0 )
		return;
	
	_luaObject.LoadFromFile( path, loadParams.archive );
	
	_luaHasAI = _luaObject.HasFunction( LUA_FUNCTION_AI );
	_luaHasInit = _luaObject.HasFunction( LUA_FUNCTION_INIT );
	_luaHasKeyboardEvent = _luaObject.HasFunction( LUA_FUNCTION_KEYBOARD );
	
	InitLuaFunctions();
}

#endif // ED3_ENGINE_USE_LUA	
	
	
}
