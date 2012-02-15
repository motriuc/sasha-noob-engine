////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_lightpoint.cpp
//	Created            : 5 2 2012   21:53
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\render3d\cpp
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
#include "rd3afx.h"
#include "rd3_lightpoint.h"
#include "rd3_xml_def.h"

using namespace System;

namespace Rd3
{
	
//-----------------------------------------------------------------------	
void LightPoint::LoadFromXml( const Xml::BaseDomNode& node, const Def& def )
{
	for( sInt i = 0; i < node.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& child = node[i];
		
		if( !XmlCheckDef( child, def ) )
			continue;
		
		if( child.GetName() == ELEMENT_COLOR )
		{
			XmlLoad_ColorF( _diffuseColor, child, def );
			
			_specularColor = _diffuseColor;
			_ambientColor = _diffuseColor;
			
		} else if( child.GetName() == ELEMENT_COLOR_DIFFUSE )
		{
			XmlLoad_ColorF( _diffuseColor, child, def );
		}
		else if( child.GetName() == ELEMENT_COLOR_SPECULAR )
		{
			XmlLoad_ColorF( _specularColor, child, def );
		}
		else if( child.GetName() == ELEMENT_COLOR_AMBIENT )
		{
			XmlLoad_ColorF( _ambientColor, child, def );
		}
		else if( child.GetName() == ELEMENT_POSITION )
		{
			XmlLoad_VectorF( _position.v, child, def );
		}
		else if( child.GetName() == ELEMENT_ATTENUATION )
		{
			_attenuation = child.GetAttributes()[ATTR_VALUE].ToFloat();
		}
		else if( child.GetName() == ELEMENT_MAXDISTANCE )
		{
			_maxLigtiningDistance = child.GetAttributes()[ATTR_VALUE].ToFloat();
		}
	}
}

//-----------------------------------------------------------------------		
d3Float LightPoint::GetVisibilityFactor( const d3Vector& p ) const
{
	d3Float dist = d3Vector::Distance( _position, p );
	
	if( _maxLigtiningDistance == 0.0f )
	{
		return dist * _attenuation;
	}
	
	if( _maxLigtiningDistance <= dist )
		return Limit::d3Float::Max;
	
	return dist * _attenuation;
}	
	
		
}