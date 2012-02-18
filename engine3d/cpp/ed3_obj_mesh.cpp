////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_obj_mesh.cpp
//	Created            : 2 2 2012   19:09
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\engine3d\cpp
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
#include "ed3afx.h"
#include "ed3_obj_mesh.h"
#include "ed3_obj_factory.h"
#include "ed3_rdata.h"
#include "rd3_render.h"
#include "rd3_rstate.h"
#include "ed3_edata.h"

namespace Ed3
{

AUTO_REGISTER_D3OBJECT_FACTORY( _S("engine.object.mesh") , d3MeshObject )	
	
//-----------------------------------------------------------------------	
d3MeshObject::d3MeshObject()
{
}

//-------------------------------------------------------------------
void d3MeshObject::Initialize( Rd3::Render& render ) throws_error
{
	_BaseClass::Initialize( render );
	
}
	
//-------------------------------------------------------------------
void d3MeshObject::LoadFromXML( const Xml::BaseDomNode& element, Ed3::LoadDataParams& loadParams ) throws_error
{
	_BaseClass::LoadFromXML( element, loadParams );
	sString mesh = element.GetAttributes()[ATTR_MESH];
	
	_mesh = loadParams.render.UseMesh( mesh );
}

//-------------------------------------------------------------------
void d3MeshObject::Render( const Ed3::d3RenderData& renderData )
{
	Rd3::RenderState& render = renderData.rstate();
		
	render.BeginRenderObject();
	render.RenderMesh( &_mesh() );
	render.EndRenderObject();
}
	
//-------------------------------------------------------------------
void d3MeshObject::AI( d3EngineData& edata )
{
}
	
	
}