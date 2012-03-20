////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_obj_mesh.cpp
//  Created            : 2 2 2012   19:09
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
#include "ed3_obj_mesh.h"
#include "ed3_obj_factory.h"
#include "ed3_rdata.h"
#include "rd3_render.h"
#include "rd3_rstate.h"
#include "ed3_edata.h"

namespace Ed3
{
	
//-----------------------------------------------------------------------	
d3MeshObject::d3MeshObject()
{
}

//-------------------------------------------------------------------
void d3MeshObject::Initialize( Rd3::Render& render ) throws_error
{
	_BaseClass::Initialize( render );
	_initialTransformation = GetTransformationMatrix();
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
	render.RenderMesh( _mesh );
	render.EndRenderObject();
}

//-------------------------------------------------------------------
void d3MeshObject::ComputeBoundingBox( d3AABBox& bbox )
{
	_mesh().GetVb().ComputeBoundingBox( bbox );
}
	
//-------------------------------------------------------------------
void d3MeshObject::AI( d3EngineData& edata )
{
	if( _mesh )
	{
		if( _mesh().GetAnimation() )
		{
			Rd3::Animation::Result result;
			_mesh().GetAnimation()->Animate( edata.GetTime(), _animState, result );

			 d3Matrix m;
			 d3Matrix animTran;
			 result.GetTransformation( animTran );
			 d3Matrix::Mul( m, animTran, _initialTransformation );

			 SetTransformationMatrix( m );
		}
	}
}
	
	
}