/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_object_d2.cpp
//  Created             : 20 3 2012
//  Author              : Motriuc Alexandru
//  File Path           : SLibF\engine3d\include
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
#include "ed3_object_d2.h"
#include "ed3_edata.h"
#include "ed3_rdata.h"

#include "rd3_rstate.h"
#include "rd3_render.h"
#include "rd3_xml_def.h"

using namespace Rd3;

namespace Ed3
{

//------------------------------------------------------------------
d2Object::d2Object( const sString& name, sBool listenGestureEvents ) :
	_BaseClass( ObjectType::E_OBJECT, name ),
	_listenGestureEvents( listenGestureEvents ),
	_d2Plane( d3Vector( 0.0f, 0.0f, 1.0f ), 0.0f ),
	_pRenderData( NULL ),
	_uiFontColor( RGBColor::White )
{
}

//------------------------------------------------------------------
d2Object::~d2Object()
{
}

//------------------------------------------------------------------
void d2Object::ComputeBoundingBox( d3AABBox& b )
{
	b = d3AABBox(
		d3Point( -1.0f, -1.0f, 0.0f ),
		d3Point( 1.0f, 1.0f, 0.0f ) 
	);
}

//------------------------------------------------------------------
void d2Object::Initialize( Rd3::Render& render ) throws_error
{
	_BaseClass::Initialize( render );

	_vb = render.UseDynamicVertexBuffer( VertexBufferStream::E_XYZ | VertexBufferStream::E_TX1 );

	if( _listenGestureEvents )
	{
		render.MessageQueue_RegisterEvent(
			_S("engine.msg.gesture"),
			Events::Event( this, &d2Object::internal_OnGestureEvent )
		);
	}

	_textureMaterial.ResourceCreate( new TextureMaterial( &render, _S("") ) );
	_textureMaterial().SetNumberOfLights( 0 );
	_textureMaterial().SetAmbient( 1.0f );
	_textureMaterial().SetDiffuze( 0.0f );
	_textureMaterial().SetSpecular( 0.0f );
}

//------------------------------------------------------------------
void d2Object::Uninitialize( Rd3::Render& render )
{
	_BaseClass::Uninitialize( render );

	if( _listenGestureEvents )
	{
		render.MessageQueue_UnregisterEvent(
			_S("engine.msg.gesture"),
			Events::Event( this, &d2Object::internal_OnGestureEvent )
		);
	}
}

//------------------------------------------------------------------
void d2Object::Render( const d3RenderData& renderData )
{
	_pRenderData = &renderData;
	RenderState& render = renderData.rstate();
	
	render.BeginRenderObject();
	Render2D( renderData );
	render.EndRenderObject();

	_pRenderData = NULL;
}

//------------------------------------------------------------------
void d2Object::AI( d3EngineData& edata )
{

}

//------------------------------------------------------------------
void d2Object::internal_OnGestureEvent( Rd3::EngineData& edata, const Rd3::GestureEvent& e )
{
	d3Matrix objectMatrix;
	GetAbsoluteTransformationMatrix( objectMatrix );
	objectMatrix.Invert();
	
	GestureEvent d2Event( e.GetType() );

	for( sInt i = 0; i < e.Taps().Size(); ++i )
	{
		const GestureTap& tap = e.Taps()[i];
		
		d3LineSegment ray;
		edata.GetRayForScreenPoint( tap.Position() , ray );

		ray.Apply( objectMatrix );

		d3Vector intPoint;
		if( _d2Plane.Intersect( ray.GetLine(), intPoint ) )
		{
			d2Event.Add( GestureTap( intPoint ) );
		}
	}

	OnGestureEvent( edata, d2Event );
}
	
//------------------------------------------------------------------
void d2Object::RenderTexture( const d2Point& posFrom, const d2Point& posTo, Rd3::Texture* pTexture, const d2Point& txFrom, const d2Point& txTo )
{
	__S_ASSERT( pTexture != NULL );
	__S_ASSERT( _pRenderData != NULL );

	d3Float width = static_cast<d3Float>( pTexture->GetWidth() );
	d3Float height = static_cast<d3Float>( pTexture->GetHeight() );

	_vb().BeginAdd( 6 );
	_vb().AddFaceZ(
		posFrom.x, posTo.x, posFrom.y, posTo.y, 
		txFrom.x / width, txTo.x / width,
		txFrom.y / height, txTo.y / height,
		0.0f
	);
	_vb().EndAdd();

	_textureMaterial().SetTexture( pTexture );
	_textureMaterial().Apply( _pRenderData->rstate() );

	_pRenderData->rstate().RenderPrimitive( _vb, Rd3::PrimitiveType::E_TRIANGLE_LIST );
}

//------------------------------------------------------------------
void d2Object::RenderText( const sString& text, const d2Point& pos, d3Float height, sRGBColor color )
{
	__S_ASSERT( _pRenderData != NULL );

	_uiFont().RenderText( _pRenderData->rstate(), text, pos, height, color );
}

//------------------------------------------------------------------
void d2Object::LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	{
		sString messageQ = element.GetAttributes()[ATTR_UI_MSGQ];
		if( messageQ.Length() > 0 )
			_uiQueue = loadParams.render.UseTypedMessageQueue<UiMsgQueue>( messageQ );
	}

	{
		sString fontName = element.GetAttributes()[ATTR_FONT];
		if( fontName.Length() > 0 )
			_uiFont = loadParams.render.UseFont( fontName );
	}

	_BaseClass::LoadFromXML( element, loadParams );
}


}
