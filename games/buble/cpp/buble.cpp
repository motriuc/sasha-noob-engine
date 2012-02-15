/////////////////////////////////////////////////////////////////////
//  File Name               : buble.cpp
//	Created                 : 30 1 2012   0:05
//	File path               : games/buble/cpp
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

#include "bubleafx.h"
#include "buble.h"
#include "ed3_obj_factory.h"
#include "ed3_rdata.h"

#include "rd3_texture.h"
#include "rd3_mesh.h"
#include "rd3_effect.h"
#include "rd3_render.h"
#include "rd3_rstate.h"


#define MAX_FIELD_SIZE 128

AUTO_REGISTER_D3OBJECT_FACTORY( _S("game.buble") , Buble )

using namespace Streams;
using namespace Rd3;

//-------------------------------------------------------------------
Buble::Buble() :
	_radius( 1.0f )
{
	
}
//-------------------------------------------------------------------
void Buble::LoadFromXML( const Xml::BaseDomNode& element, Ed3::LoadDataParams& loadParams ) throws_error
{
	_BaseClass::LoadFromXML( element, loadParams );
	
}

//-------------------------------------------------------------------
void Buble::Render( const Ed3::d3RenderData& renderData )
{
	Rd3::RenderState& render = renderData.rstate();
	
	render.BeginRenderObject();
	
//	render.SetEffect( _effect );
//	render.SetTexture( Rd3::TextureParameter::E_TEX1, _tileTexture );
//	render.RenderPrimitive( _vb, Rd3::PrimitiveType::E_TRIANGLE_LIST );
	
	render.EndRenderObject();
}

//-------------------------------------------------------------------
void Buble::Initialize( Rd3::Render& render ) throws_error
{
	_BaseClass::Initialize( render );
		
}
