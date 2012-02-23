/////////////////////////////////////////////////////////////////////
//	File Name				: ed3_object_lua.cpp
//	Created					: 18 2 2012   20:02
//	File path				: SLibF\engine3d\cpp
//	Author                  : Alexandru Motriuc
//	Platform Independentsy  : 0%
//	Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//	Modification History:
//      
/////////////////////////////////////////////////////////////////////

#include "ed3afx.h"
#include "ed3_object.h"
#include "ed3_edata.h"
#include "rd3_perf_counters.h"

#define LUA_FUNCTION_AI				_S("d3Object_AI")
#define LUA_FUNCTION_INIT			_S("d3Object_Init")
#define LUA_OBJ						_S("self")

#define LUA_STATIC					_S("hobj")


//--------------------------------------------------------------------------------------------------------
COUNTER_USE( rd3_render_time_lua )
//--------------------------------------------------------------------------------------------------------

namespace Ed3 
{

#ifdef ED3_ENGINE_USE_LUA


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
void d3Object::InitLuaFunctions()
{	
	_luaObject.RegisterMathLib();
	_luaObject.Register( LUA_OBJ, _S("RotateX"), d3Object_RotateX );
	_luaObject.Register( LUA_OBJ, _S("RotateY"), d3Object_RotateY );
	_luaObject.Register( LUA_OBJ, _S("RotateZ"), d3Object_RotateZ );
	_luaObject.Register( LUA_OBJ, _S("Move"), d3Object_Move );
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
	
	InitLuaFunctions();
}

#endif // ED3_ENGINE_USE_LUA	
	
	
}
