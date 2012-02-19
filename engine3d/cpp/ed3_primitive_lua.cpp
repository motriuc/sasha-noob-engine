/////////////////////////////////////////////////////////////////////
//  File Name               : ed3_primitive_lua.cpp
//  Created                 : 5 2 2012   0:05
//  File path               : SLibF\engine3d\cpp
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
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

#include "ed3afx.h"
#include "ed3_primitive_lua.h"

#ifdef ED3_ENGINE_USE_LUA	

using namespace System;
using namespace System::d3Math;
using namespace System::d2Math;
using namespace Rd3;

#define LUA_CREATE_MESH	_S("Primitive_CreateMesh")
#define LUA_ESTIMATE_VC	_S("Primitive_EstimateVertexCount")
#define LUA_ESTIMATE_IC	_S("Primitive_EstimateIndexCount")

namespace Ed3
{
	
AUTO_REGISTER_PRIMITIVE_FACTORY( _S("lua"), PrimitiveLua )

//------------------------------------------------------------------
PrimitiveLua::PrimitiveLua() :
	_luaObject( this ),
	_p( NULL ),
	_i( NULL ),
	_n( NULL ),
	_t( NULL )
{
}
	
//------------------------------------------------------------------
void PrimitiveLua::LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error
{
	sString luaPath = node.GetAttributes()[_S("path")];
	
	_luaObject.LoadFromFile( luaPath, archive );

	if( !_luaObject.HasFunction( LUA_CREATE_MESH ) )
		error_throw_arg( Errors::StringError )
			sString( _S("Need function : ") ) + LUA_CREATE_MESH + _S(" in : ") + luaPath
		);

	if( !_luaObject.HasFunction( LUA_ESTIMATE_VC ) )
		error_throw_arg( Errors::StringError )
			sString( _S("Need function : ") ) + LUA_ESTIMATE_VC + _S(" in : ") + luaPath
		);
	
	if( !_luaObject.HasFunction( LUA_ESTIMATE_IC ) )
		error_throw_arg( Errors::StringError )
			sString( _S("Need function : ") ) + LUA_ESTIMATE_IC + _S(" in : ") + luaPath
		);
	
	_luaObject.RegisterMathLib();
	_luaObject.Register( _S("self"), _S("AddPoint") , AddPoint );
	_luaObject.Register( _S("self"), _S("AddNormal") , AddNormal );
	_luaObject.Register( _S("self"), _S("AddTexCoord") , AddTxCoord );
	_luaObject.Register( _S("self"), _S("AddIndex") , AddIndex );
}
	
//------------------------------------------------------------------
void PrimitiveLua::GetMesh( VertexPList& p, IndexList& i, VertexNList& n, VertexTxCoord& t ) const
{
	_p = &p;
	_i = &i;
	_n = &n;
	_t = &t;
	
	_luaObject.Exec( LUA_CREATE_MESH );
	
	_p = NULL;
	_i = NULL;
	_n = NULL;
	_t = NULL;
}
		
//------------------------------------------------------------------	
sInt PrimitiveLua::EstimateVertexCount() const
{
	return 0;
}
	
//------------------------------------------------------------------	
sInt PrimitiveLua::EstimateIndexCount() const
{
	return 0;
}

//------------------------------------------------------------------	
sInt PrimitiveLua::AddPoint( const LuaFunctionState* state )
{
	__S_ASSERT( state->Me() != NULL );

	PrimitiveLua* me = reinterpret_cast<PrimitiveLua*> ( state->Me() );
	
	d3Float x = state->GetValue( 0, 0.0f );
	d3Float y = state->GetValue( 1, 0.0f );
	d3Float z = state->GetValue( 2, 0.0f );
		
	me->_p->Add( d3Vector( x, y, z ) );
	
	return 0;
}
	
//------------------------------------------------------------------	
sInt PrimitiveLua::AddNormal( const LuaFunctionState* state )
{
	__S_ASSERT( state->Me() != NULL );

	PrimitiveLua* me = reinterpret_cast<PrimitiveLua*> ( state->Me() );
	
	d3Float x = state->GetValue( 0, 0.0f );
	d3Float y = state->GetValue( 1, 0.0f );
	d3Float z = state->GetValue( 2, 0.0f );
	
	
	me->_n->Add( d3Vector( x, y, z ) );
	
	return 0;
}

//------------------------------------------------------------------		
sInt PrimitiveLua::AddTxCoord( const LuaFunctionState* state )
{
	__S_ASSERT( state->Me() != NULL );

	PrimitiveLua* me = reinterpret_cast<PrimitiveLua*> ( state->Me() );
	
	d3Float x = state->GetValue( 0, 0.0f );
	d3Float y = state->GetValue( 1, 0.0f );

	me->_t->Add( d2Vector( x, y ) );
	
	return 0;
}

//------------------------------------------------------------------		
sInt PrimitiveLua::AddIndex( const LuaFunctionState* state )
{
	__S_ASSERT( state->Me() != NULL );
	
	PrimitiveLua* me = reinterpret_cast<PrimitiveLua*> ( state->Me() );

	sInt ind1 = state->GetValue( 0, 0 );
	sInt ind2 = state->GetValue( 1, 0 );
	sInt ind3 = state->GetValue( 2, 0 );
	
	me->_i->Add( ind1, ind2, ind3 );
	
	return 0;
}
	
	
}

#endif // ED3_ENGINE_USE_LUA
