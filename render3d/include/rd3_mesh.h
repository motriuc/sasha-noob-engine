/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_mesh.h
//	Created                 : 5 2 2012   21:56
//	File path               : SLibF\render3d\include 
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//	Library                 : 
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

#ifndef _RD3_MESH_INC_
#define _RD3_MESH_INC_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_resobj.h"
#include "rd3_indexbuffer.h"
#include "rd3_vertexbuffer.h"
#include "rd3_material.h"

namespace Rd3 
{
	
using namespace System;	

class Primitive3D;	
	
/**
 * Mesh
 */
class Mesh : public ResourceObject
{
private:
	typedef ResourceObject _BaseClass;
public:
	void LoadFromFile( const sString& path, const Def& def, const Streams::StreamArchive& archive ) throws_error;
	void LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error;

	const VertexBuffer& GetVb() const	{ return _vertexBuffer(); }
	const IndexBuffer& GetIb() const	{ return _indexBuffer(); }
	const Material& GetMaterial() const { return _material(); }

	PrimitiveType::PrimitiveType GetPrimitiveType() const { return _type; }
	
	void SetVb( VertexBuffer* pVertexBuffer )	{ _vertexBuffer = pVertexBuffer; }
	void SetIb( IndexBuffer* pIndexBuffer )		{ _indexBuffer = pIndexBuffer; }
	
	void SetVb( const sString& name );
	void SetIb( const sString& name );

	const Animation* GetAnimation() const { return _animation; }
public:
	void SetPrimitiveMesh( const Primitive3D& primitive ); 
	
	Mesh( Render* owner, const sString& objectName );
	virtual ~Mesh();
private:
	use_resource<VertexBuffer>	_vertexBuffer;
	use_resource<IndexBuffer>	_indexBuffer;
	use_resource<Material>		_material;
	PrimitiveType::PrimitiveType _type;

	Animation*					_animation;
};
	
}


#endif // _RD3_MESH_INC_