/////////////////////////////////////////////////////////////////////
//  File Name               : ed3_lua.cpp
//  Created                 : 18 2 2012   20:02
//  File path               : SLibF\engine3d\cpp
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
#include "ed3_lua.h"
#include "lua.hpp"

namespace Ed3  
{
/*******************************************************************/
/* LuaFunctionState                                                */
/*******************************************************************/

//------------------------------------------------------------------
void* LuaFunctionState::Me() const
{
	return ((lua_State*)this)->_me;
}

//------------------------------------------------------------------
void LuaFunctionState::Return( d3Float def ) const
{
	lua_pushnumber( ((lua_State*)this), def );	
}

//------------------------------------------------------------------
void LuaFunctionState::Return( sInt value ) const
{
	lua_pushinteger( ((lua_State*)this), value );
}
	
//------------------------------------------------------------------
d3Float LuaFunctionState::GetValue( sInt i, d3Float def ) const
{
	lua_State* p = (lua_State*)this;

	if( i < 0 || i >= lua_gettop( p ) )
		return def;

	i++;

	if( !lua_isnumber( p, i ) )
		return def;

	return (d3Float)lua_tonumber( p, i );
}

//------------------------------------------------------------------
sString LuaFunctionState::GetValue( sInt i, const sString& def ) const
{
	lua_State* p = (lua_State*)this;
	
	if( i < 0 || i >= lua_gettop( p ) )
		return def;
	
	i++;
	
	if( !lua_isstring( p, i ) )
		return def;
	
	return lua_tostring( p, i );	
}
	
//------------------------------------------------------------------
sInt LuaFunctionState::GetValue( sInt i, sInt def ) const
{
	lua_State* p = (lua_State*)this;
	
	if( i < 0 || i >= lua_gettop( p ) )
		return def;
	
	i++;
	
	if( !lua_isnumber( p, i ) )
		return def;
	
	return lua_tointeger( p, i );
}	

//------------------------------------------------------------------
void* LuaFunctionState::GetInstance() const
{
	// TO DO
	__S_ASSERT( sFalse );
	return NULL;
}

	
/*******************************************************************/
/* LuaObject                                                       */
/*******************************************************************/

//------------------------------------------------------------------
LuaObject::LuaObject( void* pUserPtr ) :
	_pLuaHandle( NULL ),
	_pUserPtr( pUserPtr )
{
}

//------------------------------------------------------------------
LuaObject::~LuaObject()
{
	if( _pLuaHandle != NULL )
		lua_close( reinterpret_cast<lua_State*>(_pLuaHandle) );
}

//------------------------------------------------------------------
void LuaObject::Register( const SBCHAR* funName, LuaFunction fn )
{	
	__S_ASSERT( funName != NULL );
	__S_ASSERT( fn != NULL );
	
	lua_State* state = reinterpret_cast<lua_State*>( _pLuaHandle );
	
	if( state != NULL )
	{
		lua_register( 
			state, 
			funName,
			reinterpret_cast<lua_CFunction>( fn )
		);
	}
}

//------------------------------------------------------------------
void LuaObject::Register( const SBCHAR* table, const SBCHAR* funName, LuaFunction fn )
{
	__S_ASSERT( table != NULL );
	__S_ASSERT( funName != NULL );
	__S_ASSERT( fn != NULL );
	
	lua_State* state = reinterpret_cast<lua_State*>( _pLuaHandle );

	if( state != NULL )
	{
		luaL_Reg functions[] = 
		{
			{ funName, reinterpret_cast<lua_CFunction>( fn ) },
			{ NULL, NULL }
		};
		
		luaL_register( state, table, functions );
	}
}
	
//------------------------------------------------------------------
void LuaObject::LoadFromFile( const sString& path, const Streams::StreamArchive& archive ) throws_error
{
	ptr_unique<const Streams::IInputStream> pStream( archive.Open( path ) );
	
	sUInt length = pStream().GetSize();
	
	ptr_array_unique<char> charBuffer ( new char[length+1] );
	pStream().Read( charBuffer, length );
	charBuffer[length] = 0;

	try
	{
		LoadFromString( charBuffer );
	}
	catch( Errors::Error* error )
	{
		error_throw_chain_arg( Errors::StringError )
			_S("Can't load Lua: ") + path
		);
	}
}
//------------------------------------------------------------------
void LuaObject::RegisterMathLib()
{
	lua_State* state = reinterpret_cast<lua_State*>( _pLuaHandle );
	
	if( state != NULL )
	{
		luaL_requiref( state, LUA_MATHLIBNAME, luaopen_math, 1 );
		lua_pop( state, 1 );
	}
}
	
//------------------------------------------------------------------
void LuaObject::LoadFromString( const char* code ) throws_error
{
	if( _pLuaHandle != NULL )
	{
		lua_close(  reinterpret_cast<lua_State*>( _pLuaHandle ) );
		_pLuaHandle = NULL;
	}
	
	_pLuaHandle = luaL_newstate();
	
	if( _pLuaHandle == NULL )
		error_throw_arg( Errors::StringError )
			_S("Can't create state")
		);
	
	lua_State* state = reinterpret_cast<lua_State*>( _pLuaHandle );
	
	state->_me = _pUserPtr;
	
	
	if( luaL_loadstring( state, code ) != 0 || 
	   lua_pcall( state, 0, 0, 0) != 0
	   )
	{
		sString error = lua_tostring( state ,-1 );
		lua_close( state );
		_pLuaHandle = NULL;
		
		error_throw_arg( Errors::StringError )
			_S("Error Lua: ") + error
		);
	}		
}

//------------------------------------------------------------------
void LuaObject::Exec( const SBCHAR* funName, void* pObject, LuaFunctions* pObjectFun ) throws_error
{
	if( _pLuaHandle == NULL )
		return;

	lua_State* state = reinterpret_cast<lua_State*>( _pLuaHandle );	
	lua_getglobal( state, funName );

	lua_newtable( state );

	lua_pushstring( state, "__object_instance" );
	lua_pushinteger( state, (lua_Integer)pObject );
    lua_settable( state, -3 );

	if( pObjectFun != NULL )
		luaL_register( state, 0, (luaL_Reg*)pObjectFun );

	if( lua_pcall( state, 1, 0, 0 ) != 0 )
	{
		sString error = lua_tostring( state, -1 );
		lua_close( state );
		_pLuaHandle = NULL;
		
		error_throw_arg( Errors::StringError )
			Format( _S("Can't execute Lua function: {1}. Error : {2}") ) % funName % error 
		);
	}	
}

//------------------------------------------------------------------
void LuaObject::Exec( const SBCHAR* funName, d3Float p ) throws_error
{
	if( _pLuaHandle == NULL )
		return;

	lua_State* state = reinterpret_cast<lua_State*>( _pLuaHandle );
	
	lua_getglobal( state, funName );
	lua_pushnumber( state, p );
	
	if( lua_pcall( state, 1, 0, 0 ) != 0 )
	{
		sString error = lua_tostring( state, -1 );
		lua_close( state );
		_pLuaHandle = NULL;
		
		error_throw_arg( Errors::StringError )
			Format( _S("Can't execute Lua function: {1}. Error : {2}") ) % funName % error 
		);
	}	
}
	
//------------------------------------------------------------------
void LuaObject::Exec( const SBCHAR* funName )
{
	if( _pLuaHandle == NULL )
		return;
	
	lua_State* state = reinterpret_cast<lua_State*>( _pLuaHandle );
	
	lua_getglobal( state, funName );

	if( lua_pcall( state, 0, 0, 0 ) != 0 )
	{
		sString error = lua_tostring( state, -1 );
		lua_close( state );
		_pLuaHandle = NULL;
		
		error_throw_arg( Errors::StringError )
			Format( _S("Can't execute Lua function: {1}. Error : {2}") ) % funName % error 
		);
	}
}

//------------------------------------------------------------------
sBool LuaObject::HasFunction( const SBCHAR* funName ) const
{
	if( _pLuaHandle == NULL )
		return sFalse;
	
	lua_State* state = reinterpret_cast<lua_State*>( _pLuaHandle );
	
	lua_getglobal( state, funName );
	
	return lua_isfunction( state, lua_gettop( state ) ); 
}
	
}

