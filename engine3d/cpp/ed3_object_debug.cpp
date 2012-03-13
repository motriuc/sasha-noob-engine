/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_object_debug.cpp
//  Created             : 13 3 2012
//  Author              : Motriuc Alexandru
//  File Path           : SLibF\engine3d\cpp
//  System independent  : 0%
//  Library             : 
//
//  Purpose:
//    
//
/////////////////////////////////////////////////////////////////////
//  Modification History :
//
/////////////////////////////////////////////////////////////////////
#include "ed3afx.h"
#include "ed3_object.h"
#include "rd3_render.h"
#include "ed3_rdata.h"
#include "rd3_rstate.h"

namespace Ed3
{

#ifdef _D3_DEBUG_RENDER

//--------------------------------------------------------------------------------------------------------
void d3Object::debug_InitResources( Rd3::Render& render )
{
	if( _debug_vb == NULL )
		_debug_vb = render.UseDynamicVertexBuffer( Rd3::VertexBufferStream::E_XYZ | Rd3::VertexBufferStream::E_COLOR_DIF );

	if( _debug_effect_solid == NULL )
		_debug_effect_solid = render.UseEffect( _S("system.debug.solid.color") );
}

//--------------------------------------------------------------------------------------------------------
void d3Object::debug_Render( const d3RenderData& renderData )
{
	if( HasState( OBS_BOUNDINGBOX ) && renderData.rstate().GetData().GetCommonData().debug_RenderObjectsBoundingBox() )
		debug_Draw( renderData, _boundingBox, RGBColor::Green );
}

//--------------------------------------------------------------------------------------------------------
void d3Object::debug_Draw( const d3RenderData& renderData, const d3LineSegment& segment, sRGBColor cl ) const
{
	d3Matrix i( 1.0f );

	const d3Matrix* pMatrix = renderData.rstate().SetTransformation( &i );
	_debug_vb().BeginAdd( 2 );

	_debug_vb().AddVertex( segment.Start(), cl );
	_debug_vb().AddVertex( segment.End(), cl );

	_debug_vb().EndAdd();

	renderData.rstate().BeginRenderObject();

	renderData.rstate().SetEffect( _debug_effect_solid );
	renderData.rstate().RenderPrimitive( _debug_vb, Rd3::PrimitiveType::E_LINE_LIST );
	renderData.rstate().EndRenderObject();

	renderData.rstate().SetTransformation(  pMatrix );
}

//--------------------------------------------------------------------------------------------------------
void d3Object::debug_Draw( const d3RenderData& renderData, const d3AABBox& b,  sRGBColor cl ) const
{
	d3Matrix i( 1.0f );
	const d3Matrix* pMatrix = renderData.rstate().SetTransformation( &i );

	d3AABBox bNew;
	d3AABBox::Mul( bNew, b, *pMatrix );

	_debug_vb().BeginAdd( 24 );

	_debug_vb().AddVertex( bNew.GetCorner( 0 ), cl );
	_debug_vb().AddVertex( bNew.GetCorner( 1 ), cl );

	_debug_vb().AddVertex( bNew.GetCorner( 0 ), cl );
	_debug_vb().AddVertex( bNew.GetCorner( 2 ), cl );

	_debug_vb().AddVertex( bNew.GetCorner( 2 ), cl );
	_debug_vb().AddVertex( bNew.GetCorner( 3 ), cl );

	_debug_vb().AddVertex( bNew.GetCorner( 3 ), cl );
	_debug_vb().AddVertex( bNew.GetCorner( 1 ), cl );

	_debug_vb().AddVertex( bNew.GetCorner( 0 ), cl );
	_debug_vb().AddVertex( bNew.GetCorner( 4 ), cl );

	_debug_vb().AddVertex( bNew.GetCorner( 2 ), cl );
	_debug_vb().AddVertex( bNew.GetCorner( 6 ), cl );

	_debug_vb().AddVertex( bNew.GetCorner( 3 ), cl );
	_debug_vb().AddVertex( bNew.GetCorner( 7 ), cl );

	_debug_vb().AddVertex( bNew.GetCorner( 1 ), cl );
	_debug_vb().AddVertex( bNew.GetCorner( 5 ), cl );

	_debug_vb().AddVertex( bNew.GetCorner( 6 ), cl );
	_debug_vb().AddVertex( bNew.GetCorner( 4 ), cl );

	_debug_vb().AddVertex( bNew.GetCorner( 6 ), cl );
	_debug_vb().AddVertex( bNew.GetCorner( 7 ), cl );

	_debug_vb().AddVertex( bNew.GetCorner( 7 ), cl );
	_debug_vb().AddVertex( bNew.GetCorner( 5 ), cl );

	_debug_vb().AddVertex( bNew.GetCorner( 4 ), cl );
	_debug_vb().AddVertex( bNew.GetCorner( 5 ), cl );

	_debug_vb().EndAdd();

	renderData.rstate().BeginRenderObject();

	renderData.rstate().SetEffect( _debug_effect_solid );
	renderData.rstate().RenderPrimitive( _debug_vb, Rd3::PrimitiveType::E_LINE_LIST );
	renderData.rstate().EndRenderObject();

	renderData.rstate().SetTransformation(  pMatrix );
}

#endif

}
