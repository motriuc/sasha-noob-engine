////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_light.cpp
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
#include "rd3_light.h"
#include "rd3_xml_def.h"

using namespace System;

namespace Rd3
{
	
//-----------------------------------------------------------------------	
void Light::LoadFromXml( const Xml::BaseDomNode& node, const Def& def ) throws_error
{
	if( node.GetName() == ELEMENT_LIGHT_POINT )
	{
		LightPoint pointLight( RGBColor::White, d3Vector( 1.0f ) );
		
		pointLight.LoadFromXml( node, def );
		
		(*this) = pointLight;
	}
	else 
	{
		error_throw_arg( Errors::StringError )
			_S("Unknown light type: " ) + node.GetName()
		);
	}
}

//-----------------------------------------------------------------------	
d3Float Light::GetVisibilityFactor( const d3Vector& p ) const
{
	switch( _type )
	{
		case LightType::E_POINT:
			return lightPoint().GetVisibilityFactor( p );
	}
	
	return Limit::d3Float::Max;
}
	
//-----------------------------------------------------------------------	
LightList::LightList()	
{
}

	
//-----------------------------------------------------------------------	
void LightList::AddLight( const Light& light )
{
	_lightList.Add( light );
}
	
//-----------------------------------------------------------------------	
void LightList::LoadFromXml( const Xml::BaseDomNode& node, const Def& def ) throws_error
{
	for( sInt i = 0; i < node.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& child = node[i];
		
		if( !XmlCheckDef( child, def ) )
			continue;
		
		Light light;
		light.LoadFromXml( child, def );
		
		AddLight( light );
	}
}

	
}