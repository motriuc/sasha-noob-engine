////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_prerender.cpp
//  Created            : 15 02 2012   19:09
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
#include "ed3afx.h"
#include "ed3_prerender.h"
#include "rd3_render.h"
#include "rd3_rstate.h"
#include "rd3_edata.h"
#include "ed3_world.h"
#include "ed3_rdata.h"

namespace Ed3
{
	

//-----------------------------------------------------------------------
d3PreRender::d3PreRender() :
	_width( 0 ),
	_height( 0 )
{
}
	
//-----------------------------------------------------------------------
void d3PreRender::Initialize( Rd3::Render& render )
{
}

//-----------------------------------------------------------------------
void d3PreRender::Render( Rd3::WorldRenderState& rstate, Rd3::EngineDataForRender& edata, d3World& world )
{
	rstate.SetRenderTarget( _texture );
	rstate.SetCamera( world.GetCamera() );
	
	rstate.BeginWorldRender( edata );
	
	d3RenderData renderData( &rstate, _renderClass );
	world.DoRender( renderData );
	
	rstate.EndWorldRender();
	
	rstate.SetRenderTarget( NULL );
}
	
//-----------------------------------------------------------------------
void d3PreRender::LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	sString name = element.GetAttributes()[ATTR_NAME];
	_width = element.GetAttributes()[ATTR_WIDTH].ToInt();
	_height = element.GetAttributes()[ATTR_HEIGHT].ToInt();
	
	if( loadParams.pClassNames != NULL )
	{
		sString cls = element.GetAttributes()[ATTR_CLASS];
		_renderClass.Add( loadParams.pClassNames->GetClassFromString( cls ) );
	}
	
	
	if( _width == 0 || _height == 0 )
	{
		d2Vector size = loadParams.render.GetScreen_SizeInPixels();
		
		_width = (sInt)size.x;
		_height = (sInt)size.y;
	}
	
	_texture.ResourceCreate( 
		loadParams.render.CreateTexture( name, _width, _height, Rd3::TextureType::E_IMAGE )
	);
}

//-----------------------------------------------------------------------
void d3PreRenderList::Initialize( Rd3::Render& render )
{
	for( sInt i = 0; i < _preRenderList.Size(); ++i )
	{
		_preRenderList[i]->Initialize( render );
	}
}

//-----------------------------------------------------------------------
void d3PreRenderList::Render( Rd3::WorldRenderState& rstate, Rd3::EngineDataForRender& edata, d3World& world )
{
	for( sInt i = 0; i < _preRenderList.Size(); ++i )
	{
		_preRenderList[i]->Render( rstate, edata, world );
	}
}		
	
//-----------------------------------------------------------------------
void d3PreRenderList::LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{	
	for( sInt i = 0; i < element.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& childElement = element[i];
		
		if( !Rd3::XmlCheckDef( childElement, loadParams.def ) )
			continue;
		
		if( childElement.GetName() == ELEMENT_TEXTURE )
		{
			d3PreRender* preRender = new d3PreRender();
			_preRenderList.Add( preRender );
			
			preRender->LoadFromXML( childElement, loadParams );
		}
	}
}

//-----------------------------------------------------------------------
d3PreRenderList::~d3PreRenderList()
{
	for( sInt i = 0; i < _preRenderList.Size(); i++ )
	{
		delete _preRenderList[i];
	}
}
	
	
}
