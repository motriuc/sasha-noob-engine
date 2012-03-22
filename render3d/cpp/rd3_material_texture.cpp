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
	_co_ambient( 0.05f ),
	_numberOfLights( 1 )
{
	UpdateEffect();
}

//-------------------------------------------------------------------
void TextureMaterial::UpdateEffect()
{
	sString effectName = _S("system.texture.fx.0");
	
	if( _numberOfLights > 0 )
	{
		switch( _numberOfLights )
		{
			case 1:
				switch ( _quality )
				{
					case Rd3::Quality::E_Medium:
					case Rd3::Quality::E_High:
						effectName = _S("system.texture.fx.1.qh");						
						break;
					case Rd3::Quality::E_Low:
					default:
						effectName = _S("system.texture.fx.1");
				}
				break;
			case 2:
				effectName = _S("system.texture.fx.2");
				break;
			case 3:
				effectName = _S("system.texture.fx.3");
				break;
			case 4:
			default:
				effectName = _S("system.texture.fx.4");
				break;
		}
	}
	
	_effect = GetOwner()->UseEffect( effectName );	
}		

//-------------------------------------------------------------------
void TextureMaterial::SetQuality( Quality::Quality quality )
{
	if( _quality != quality )
	{
		_quality = quality;
		UpdateEffect();
	}
}		
	
//-------------------------------------------------------------------
void TextureMaterial::SetNumberOfLights( sInt num )
{
	if( _numberOfLights != num )
	{
		_numberOfLights = num;
		UpdateEffect();
	}
}

//-------------------------------------------------------------------
void TextureMaterial::Apply( RenderState& renderState ) const
{
	if( _numberOfLights > 0 )
	{
		_co_diffuse		.Apply( _effect, _S("material_coef_diffuse") );
		_co_phong		.Apply( _effect, _S("material_coef_phong") );
		_co_phong_exp	.Apply( _effect, _S("material_coef_phong_exp") );
	}
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
	Quality::Quality quality = Quality::GetType( node.GetAttributes()[ATTR_QUALITY] );
	if( quality != Quality::UNKNOWN )
		SetQuality( quality );
	   
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

