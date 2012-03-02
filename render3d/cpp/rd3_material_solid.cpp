/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_material_solis.cpp
//	Created                 : 24 2 2012   19:58
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
#include "rd3_material_solid.h"
#include "rd3_render.h"
#include "rd3_xml_def.h"
#include "rd3_rstate.h"

using namespace System;


namespace Rd3
{
//-------------------------------------------------------------------
SolidMaterial::SolidMaterial( Render* owner, const sString& objectName ) :
	_BaseClass( owner, objectName ),
	_co_diffuse( 0.5f ),
	_co_phong( 0.5f ),
	_co_phong_exp( 5.0f ),
	_difColor( 1.0f ),
	_specularColor( 1.0f )
{
	_effect = owner->UseEffect( _S("system.solid.fx.1") );
}
	
//-------------------------------------------------------------------
void SolidMaterial::Apply( RenderState& renderState ) const
{
	__S_ASSERT( _effect != NULL );
	
	_co_diffuse		.Apply( _effect, _S("material_coef_diffuse") );
	_co_phong		.Apply( _effect, _S("material_coef_phong") );
	_co_phong_exp	.Apply( _effect, _S("material_coef_phong_exp") );
	
	renderState.SetParam_ColorDiffuse( _difColor );
	renderState.SetParam_ColorSpecular( _specularColor );
	renderState.SetParam_ColorAmbient( _ambientColor );
	renderState.SetEffect( _effect );
}

//-------------------------------------------------------------------
void SolidMaterial::LoadFromXml( const Xml::BaseDomNode& node, const Def& def ) throws_error
{
	for( sInt i = 0; i < node.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& child = node[i];
		
		if( !XmlCheckDef( child, def ) )
			continue;
		
		if( child.GetName() == ELEMENT_COLOR_DIFFUSE )
		{
			_co_diffuse = child.GetAttributeValue( ATTR_INTENSITY, 0.5f );
			
			XmlLoad_ColorF( _difColor.v, child, def );
		}
		else if( child.GetName() == ELEMENT_COLOR_SPECULAR )
		{
			_co_phong = child.GetAttributeValue( ATTR_INTENSITY, 0.5f );
			_co_phong_exp = child.GetAttributeValue( ATTR_HARDNESS, 5.0f );
			
			XmlLoad_ColorF( _specularColor.v, child, def );			
		}
		else if( child.GetName() == ELEMENT_COLOR_AMBIENT )
		{
			d3Float intensity = child.GetAttributeValue( ATTR_INTENSITY, 0.3f );

			XmlLoad_ColorF( _ambientColor.v, child, def );
			_ambientColor *= intensity;
		}
	}
}	
	
}

