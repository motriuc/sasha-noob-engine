////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_obj_mesh.h
//  Created            : 2 2 2012   19:09
//  Author             : Alexandru Motriuc  
//  File Path          : SLibF\engine3d\include
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

#ifndef _ED3_OBJ_MESH_INC_
#define _ED3_OBJ_MESH_INC_


#include "ed3_object.h"
#include "rd3_resobj.h"
#include "rd3_mesh.h"
#include "rd3_animation.h"

namespace Ed3
{
	
/**
 * d3MeshObject
 */
class d3MeshObject : public d3Object
{
private:
	typedef d3Object _BaseClass;
public:
	d3MeshObject();
	
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
	virtual void ComputeBoundingBox( d3AABBox& b );
	
	/**
	 *
	 */
	virtual void LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;	
private:
	Rd3::use_resource<Rd3::Mesh>	_mesh;
	Rd3::Animation::State			_animState;
	d3Matrix						_initialTransformation;
};
	
	
}

#endif // _ED3_OBJ_MESH_INC_