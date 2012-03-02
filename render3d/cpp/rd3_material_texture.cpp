/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_material_texture.cpp
//	Created                 : 5 2 2012   19:58
//	File path               : SLibF\render3d\cpp
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

#include "rd3afx.h"
#include "rd3_material_texture.h"
#include "rd3_render.h"
#include "rd3_xml_def.h"
#include "rd3_rstate.h"

using namespace System;


namespace Rd3
{	
//-------------------------------------------------------------------
TextureMaterial::TextureMaterial( Render* owner, const sString& objectName ) :
	_BaseClass( owner, objectName ),
	_co_diffuse( 0.5f ),
	_co_phong( 0.5f ),
	_co_phong_exp( 5.0f ),
	_co_ambient( 0.05f )
{
	_effect = owner->UseEffect( _S("system.texture.fx.1") );
}
	
//-------------------------------------------------------------------
void TextureMaterial::Apply( RenderState& renderState ) const
{
	_co_diffuse			.Apply( _effect, _S("material_coef_diffuse") );
	_co_phong			.Apply( _effect, _S("material_coef_phong") );
	_co_phong_exp		.Apply( _effect, _S("material_coef_phong_exp") );
	_co_ambient			.Apply( _effect, _S("material_coef_ambient") );
	
	renderState.SetTexture( TextureParameter::E_TEX1, _texture );
	renderState.SetEffect( _effect );
}

//-------------------------------------------------------------------
void TextureMaterial::SetTexture( const sString& name )
{
	_texture = GetOwner()->UseTexture( name );
}
	
//-------------------------------------------------------------------
void TextureMaterial::LoadFromXml( const Xml::BaseDomNode& node, const Def& def ) throws_error
{
	
	for( sInt i = 0; i < node.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& child = node[i];
		
		if( !XmlCheckDef( child, def ) )
			continue;
		
		if( child.GetName() == ELEMENT_TEXTURE )
		{
			SetTexture( child.GetAttributes()[ATTR_NAME] );
		}
	}
	
	if( _texture == NULL )
	{
		error_throw_arg( Errors::StringError )
			_S("Texture not set for material : " ) + GetObjectName()
		);
	}
}	
	
}

