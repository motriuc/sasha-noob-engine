////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_obj_texture.h
//	Created            : 2 2 2012   19:09
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\engine3d\include
//  System independent : 0%
//  Library            : 
//
//	Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////

#ifndef _ED3_OBJ_TEXTURE_INC_
#define _ED3_OBJ_TEXTURE_INC_


#include "ed3_object.h"
#include "rd3_resobj.h"
#include "rd3_vertexbuffer.h"
#include "rd3_texture.h"
#include "rd3_material_texture.h"

namespace Ed3
{
	
/**
 * d3MeshObject
 */
class d3TextureObject : public d3Object
{
private:
	typedef d3Object _BaseClass;
public:
	d3TextureObject();
	
protected:
	/**
	 *
	 */
	virtual void Initialize( Rd3::Render& render ) throws_error;
	
	/**
	 *
	 */
	virtual void Render( const d3RenderData& renderData );
	
	/**
	 *
	 */
	virtual void AI( d3EngineData& edata );
	
	/**
	 *
	 */
	virtual void LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	
private:
	d3Float _width;
	d3Float _height;
	
	Rd3::use_resource<Rd3::VertexBuffer>		_vb;
	Rd3::use_resource<Rd3::Texture>				_texture;
	Rd3::use_resource<Rd3::TextureMaterial>		_material;
};
	
	
}

#endif // _ED3_OBJ_TEXTURE_INC_