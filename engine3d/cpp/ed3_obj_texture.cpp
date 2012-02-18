////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_obj_texture.cpp
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
#include "ed3_obj_texture.h"
#include "ed3_obj_factory.h"
#include "ed3_rdata.h"
#include "rd3_render.h"
#include "rd3_rstate.h"
#include "ed3_edata.h"

using namespace Rd3;

namespace Ed3
{

AUTO_REGISTER_D3OBJECT_FACTORY( _S("engine.object.texture") , d3TextureObject )	
	
//-----------------------------------------------------------------------	
d3TextureObject::d3TextureObject():
	_width( 1.0f ),
	_height( 1.0f )
{
}

//-------------------------------------------------------------------
void d3TextureObject::Initialize( Rd3::Render& render ) throws_error
{
	_BaseClass::Initialize( render );
	
	_material.ResourceCreate( new TextureMaterial( &render, _S("") ) );
	_material().SetTexture( _texture );
	
	VertexPList points;
	VertexPList nornals;
	VertexTxCoord txc;
	
	
	d3Float hw = _width / 2.0f;
	d3Float hh = _height / 2.0f;
	
	points.Add( d3Vector( -hw, hh, 0.0f ) );
	points.Add( d3Vector( hw, -hh, 0.0f ) );
	points.Add( d3Vector( -hw, -hh, 0.0f ) );

	points.Add( d3Vector( hw, hh, 0.0f ) );
	points.Add( d3Vector( hw, -hh, 0.0f ) );
	points.Add( d3Vector( -hw, hh, 0.0f ) );
	
	nornals.AddCount( d3Vector( 0.0f, 0.0f, -1.0f ), 6 );
	
	txc.Add( d2Vector( 0.0f, 0.0f ) );
	txc.Add( d2Vector( 1.0f, 1.0f ) );
	txc.Add( d2Vector( 0.0f, 1.0f ) );

	txc.Add( d2Vector( 1.0f, 0.0f ) );
	txc.Add( d2Vector( 1.0f, 1.0f ) );
	txc.Add( d2Vector( 0.0f, 0.0f ) );
	
	_vb.ResourceCreate( render.CreateVertexBuffer( _S(""), points, nornals, txc ) );
}
	
//-------------------------------------------------------------------
void d3TextureObject::LoadFromXML( const Xml::BaseDomNode& element, Ed3::LoadDataParams& loadParams ) throws_error
{
	_BaseClass::LoadFromXML( element, loadParams );
	
	_width = element.GetAttributes()[ATTR_WIDTH].ToFloat();
	_height = element.GetAttributes()[ATTR_HEIGHT].ToFloat(); 

	sString textureName = element.GetAttributes()[ATTR_TEXTURE];
	_texture = loadParams.render.UseTexture( textureName );
}

//-------------------------------------------------------------------
void d3TextureObject::Render( const Ed3::d3RenderData& renderData )
{
	Rd3::RenderState& render = renderData.rstate();
		
	render.BeginRenderObject();
	_material().Apply( render );
	render.RenderPrimitive( _vb, PrimitiveType::E_TRIANGLE_LIST );
	render.EndRenderObject();
}
	
//-------------------------------------------------------------------
void d3TextureObject::AI( d3EngineData& edata )
{
}
	
	
}