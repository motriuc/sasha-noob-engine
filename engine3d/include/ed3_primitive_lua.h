/////////////////////////////////////////////////////////////////////
//  File Name               : ed3_primitive_lua.h
//  Created                 : 5 2 2012   0:05
//  File path               : SLibF\engine3d\include
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

#ifndef _ED3_PRIMITIVE_LUA_INC_
#define _ED3_PRIMITIVE_LUA_INC_

#ifndef _ED3_CONF_H_
	#error ed3_conf.h must be included
#endif

#ifdef ED3_ENGINE_USE_LUA	

#include "rd3_primitive.h"
#include "ed3_lua.h"

namespace Ed3
{
	
class PrimitiveLua : public Rd3::Primitive3D
{
public:
	/**
	 *
	 */
	PrimitiveLua();
		
	/**
	 *
	 */
	virtual void GetMesh( Rd3::VertexPList& p, Rd3::IndexList& i, Rd3::VertexNList& n, Rd3::VertexTxCoord& t ) const;
	
	virtual sInt EstimateVertexCount() const;
	
	virtual sInt EstimateIndexCount() const;
	
	virtual void LoadFromXml( const Xml::BaseDomNode& node, const Rd3::Def& def, const Streams::StreamArchive& archive ) throws_error;
	
private:
	mutable LuaObject				_luaObject;
	
	mutable Rd3::VertexPList*		_p;
	mutable Rd3::IndexList*			_i;
	mutable Rd3::VertexNList*		_n;
	mutable Rd3::VertexTxCoord*		_t;
	
	static sInt AddPoint( const LuaFunctionState* state );
	static sInt AddNormal( const LuaFunctionState* state );
	static sInt AddTxCoord( const LuaFunctionState* state );
	static sInt AddIndex( const LuaFunctionState* state ); 
};
	
}

#endif // ED3_ENGINE_USE_LUA

#endif // _ED3_PRIMITIVE_LUA_INC_