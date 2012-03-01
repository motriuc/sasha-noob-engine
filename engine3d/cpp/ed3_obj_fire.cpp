////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_obj_fire.cpp
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
#include "ed3_obj_fire.h"
#include "ed3_obj_factory.h"
#include "ed3_rdata.h"

#include "rd3_texture.h"
#include "rd3_vertexbuffer.h"
#include "rd3_effect.h"
#include "rd3_render.h"
#include "rd3_rstate.h"


namespace Ed3
{

AUTO_REGISTER_D3OBJECT_FACTORY( _S("engine.object.fire") , d3FireObject )	
	
//-----------------------------------------------------------------------	
d3FireObject::d3FireObject() :
	sideFade( 50.0f ),
	xScale( 0.4f),
	yScale( 0.6f ),
	yFade( 0.7f ),
	burnSpeed( 0.9f ),
	wobbleScale( 0.03f ),
	sideFadeSharpness( 0.03f )
{
}

//-------------------------------------------------------------------
void d3FireObject::Initialize( Rd3::Render& render ) throws_error
{
	_BaseClass::Initialize( render );
	
	Rd3::VertexPList pointList;
	Rd3::VertexTxCoord txCoord;
	
	sFloat x1 = 0.0f;
	sFloat y1 = 0.0f;
	
	sFloat x2 = 0.5f;
	sFloat y2 = 0.5f;
	
	pointList.Add( d3Vector( x1, y1, 0.0f ) );
	pointList.Add( d3Vector( x2, y2, 0.0f ) );
	pointList.Add( d3Vector( x1, y2, 0.0f ) );
	
	pointList.Add( d3Vector( x1, y1, 0.0f ) );
	pointList.Add( d3Vector( x2, y1, 0.0f ) );
	pointList.Add( d3Vector( x2, y2, 0.0f ) );
		
	sFloat tx1 = 1.0f;
	sFloat ty1 = 1.0f; 
	sFloat tx2 = -1.0f;
	sFloat ty2 = -1.0f; 
	
	txCoord.Add( d2Vector( tx1, ty1 ) );
	txCoord.Add( d2Vector( tx2, ty2 ) );
	txCoord.Add( d2Vector( tx1, ty2 ) );
	
	txCoord.Add( d2Vector( tx1, ty1 ) );
	txCoord.Add( d2Vector( tx2, ty1 ) );
	txCoord.Add( d2Vector( tx2, ty2 ) );
		
	_vertexBuffer.ResourceCreate( render.CreateVertexBuffer( _S(""), pointList, txCoord ) );
	
	
	_noiseTexture = render.UseTexture( _S("engine.obj.fire.noise.2") );
	_flameTexture = render.UseTexture( _S("engine.obj.fire.flame") );
	_fireEffect = render.UseEffect( _S("engine.obj.fire") );
}	
	
//-------------------------------------------------------------------
void d3FireObject::Render( const Ed3::d3RenderData& renderData )
{
	Rd3::RenderState& render = renderData.rstate();
		
	render.BeginRenderObject();
		
	render.SetEffect( _fireEffect );
	
	sideFade			.Apply( _fireEffect, _S("sideFade") );
	xScale				.Apply( _fireEffect, _S("xScale") );
	yScale				.Apply( _fireEffect, _S("yScale") );
	yFade				.Apply( _fireEffect, _S("yFade") );
	burnSpeed			.Apply( _fireEffect, _S("burnSpeed") );
	wobbleScale			.Apply( _fireEffect, _S("wobbleScale") );
	sideFadeSharpness	.Apply( _fireEffect, _S("sideFadeSharpness") );
	
	render.SetTexture( Rd3::TextureParameter::E_TEX1, _noiseTexture );
	render.SetTexture( Rd3::TextureParameter::E_TEX2, _flameTexture );
	
	render.RenderPrimitive( _vertexBuffer, Rd3::PrimitiveType::E_TRIANGLE_LIST );
		
	render.EndRenderObject();
}
	
	
}