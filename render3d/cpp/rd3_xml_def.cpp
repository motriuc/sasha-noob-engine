////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_xml_def.cpp
//	Created            : 19 1 2012   21:53
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
#include "rd3_xml_def.h"

using namespace System::Errors;

namespace Rd3 
{

//-------------------------------------------------------------------------------------
void XmlLoad_ColorF( d3Float* pColor, const Xml::BaseDomNode& node, const Def& def )
{
	pColor[0] = node.GetAttributeValue(ATTR_R, 0.0f );
	pColor[1] = node.GetAttributeValue(ATTR_G, 0.0f );
	pColor[2] = node.GetAttributeValue(ATTR_B, 0.0f );
	pColor[3] = node.GetAttributeValue(ATTR_A, 1.0f );
}

//-------------------------------------------------------------------------------------
void XmlLoad_VectorF( d3Float* pVector, const Xml::BaseDomNode& node, const Def& def )
{
	pVector[0] = node.GetAttributes()[ATTR_X].ToFloat();
	pVector[1] = node.GetAttributes()[ATTR_Y].ToFloat();
	pVector[2] = node.GetAttributes()[ATTR_Z].ToFloat();
}
	
//-------------------------------------------------------------------------------------
void XmlLoad_ColorF( sRGBColor& color, const Xml::BaseDomNode& node, const Def& def )
{
	color = RGBColor::FromFloatRGBA(
		node.GetAttributes()[ATTR_R].ToFloat(),
		node.GetAttributes()[ATTR_G].ToFloat(),
		node.GetAttributes()[ATTR_B].ToFloat(),
		node.GetAttributes()[ATTR_A].ToFloat()
	);
}
	

//-------------------------------------------------------------------------------------
void XmlLoad_TransformationMatrix( d3Matrix& m, const Xml::BaseDomNode& node, const Def& def )
{
	m._11 = node.GetAttributeValue( _S("_11"), 0.1f );
	m._12 = node.GetAttributeValue( _S("_12"), 0.0f );
	m._13 = node.GetAttributeValue( _S("_13"), 0.0f );
	m._14 = node.GetAttributeValue( _S("_14"), 0.0f );
	
	m._22 = node.GetAttributeValue( _S("_22"), 0.1f );
	m._22 = node.GetAttributeValue( _S("_22"), 0.0f );
	m._23 = node.GetAttributeValue( _S("_23"), 0.0f );
	m._24 = node.GetAttributeValue( _S("_24"), 0.0f );
	
	m._33 = node.GetAttributeValue( _S("_33"), 0.1f );
	m._32 = node.GetAttributeValue( _S("_32"), 0.0f );
	m._33 = node.GetAttributeValue( _S("_33"), 0.0f );
	m._34 = node.GetAttributeValue( _S("_34"), 0.0f );
	
	m._44 = node.GetAttributeValue( _S("_44"), 0.1f );
	m._42 = node.GetAttributeValue( _S("_42"), 0.0f );
	m._43 = node.GetAttributeValue( _S("_43"), 0.0f );
	m._44 = node.GetAttributeValue( _S("_44"), 0.0f );	
}

//-------------------------------------------------------------------------------------
void XmlLoad_TransformationCmd( d3Matrix& m, const Xml::BaseDomNode& node, const Def& def )
{
	for( sInt i = 0; i < node.GetChildCount(); i++ )
	{
		const Xml::BaseDomNode& childNode = node[i];
		
		if( !XmlCheckDef( childNode, def ) )
			continue;
		
		if( childNode.GetName() == ELEMENT_MOVE )
		{
			d3Vector v(
				childNode.GetAttributes()[ATTR_X].ToFloat(),
				childNode.GetAttributes()[ATTR_Y].ToFloat(),
				childNode.GetAttributes()[ATTR_Z].ToFloat()
			);
			
			d3Matrix mt;
			mt.SetTranslation( v );
				
			m *= mt;
		}
		else if( childNode.GetName() == ELEMENT_ROTATE )
		{
			d3Matrix r;
			
			r.SetRotateX( FMath::DegreeToRad( childNode.GetAttributes()[ATTR_AX].ToFloat() ) );
			m *= r;
			
			r.SetRotateY( FMath::DegreeToRad( childNode.GetAttributes()[ATTR_AY].ToFloat() ) );
			m *= r;

			r.SetRotateZ( FMath::DegreeToRad( childNode.GetAttributes()[ATTR_AZ].ToFloat() ) );
			m *= r;
		}
		else if( childNode.GetName() == ELEMENT_SCALE )
		{
			d3Matrix mt;
			
			sString scale = childNode.GetAttributes()[ATTR_A];
			
			if( scale.Length() > 0 )
			{
				d3Float fScale = scale.ToFloat();
				mt.SetScale( fScale, fScale, fScale );
			}
			else
			{
				d3Vector v(
					childNode.GetAttributes()[ATTR_AX].ToFloat(),
					childNode.GetAttributes()[ATTR_AY].ToFloat(),
					childNode.GetAttributes()[ATTR_AZ].ToFloat()
				);
				
				mt.SetScale( v.x, v.y, v.z );
			}
			m *= mt;
		}
		else {
			error_throw_arg( StringError )
				_S("[XmlLoadTransformation] unknow element :") + childNode.GetName()
			);
		}

	}
}
	
//-------------------------------------------------------------------------------------
void XmlLoad_Transformation( d3Matrix& m, const Xml::BaseDomNode& node, const Def& def )
{
	m = d3Matrix( 1.0f );
	
	if( node.GetName() != ELEMENT_TRANSFORMATION )
		error_throw_arg( StringError )
			_S("[XmlLoadTransformation] node '") + node.GetName() + _S("' must be :") + ELEMENT_TRANSFORMATION
		);
		
	if( node.GetAttributes()[ATTR_TYPE] == _S("cmd") )
		XmlLoad_TransformationCmd( m, node, def );
	
	else if( node.GetAttributes()[ATTR_TYPE] == _S("matrix") )
		XmlLoad_TransformationMatrix( m, node, def );
	else
		error_throw_arg( StringError )
			_S("[XmlLoad_Transformation] Unknown transformation type :") + node.GetAttributes()[ATTR_TYPE] 
		);
}

//-------------------------------------------------------------------------------------
void XmlLoad_Camera( d3Camera& c, const Xml::BaseDomNode& node, const Def& def )
{
	if( node.GetName() != ELEMENT_CAMERA )
		error_throw_arg( StringError )
			_S("[XmlLoad_Camera] node '") + node.GetName() + _S("' must be :") + ELEMENT_CAMERA
		);
	
	for( sInt i = 0; i < node.GetChildCount(); i++ )
	{
		const Xml::BaseDomNode& childNode = node[i];
		
		if( !XmlCheckDef( childNode, def ) )
			continue;
		
		if( childNode.GetName() == _S("set2D") )
		{
			c.SetCamera2D();
		}
	
	}
}

//-------------------------------------------------------------------------------------
void XmlLoad_TextureParams( TextureParams& p, const Xml::BaseDomNode& node, const Def& def )
{
	TextureFilteringType::TextureFilteringType minFilter = TextureFilteringType::GetType(
		node.GetAttributes()[ATTR_FILTER_MIN]
	);
	
	TextureFilteringType::TextureFilteringType magFilter = TextureFilteringType::GetType(
		node.GetAttributes()[ATTR_FILTER_MAG]
	);
	
	TextureAddressingType::TextureAddressingType addressU = TextureAddressingType::GetType(
		node.GetAttributes()[ATTR_ADDRESS_U]
	);
	
	TextureAddressingType::TextureAddressingType addressV = TextureAddressingType::GetType(
		node.GetAttributes()[ATTR_ADDRESS_V]
	);
	
	if( minFilter != TextureFilteringType::UNKNOWN )
		p.SetMinFilter( minFilter );

	if( magFilter != TextureFilteringType::UNKNOWN )
		p.SetMaxFilter( magFilter );
	
	if( addressU != TextureAddressingType::UNKNOWN )
		p.SetAddressU( addressU );

	if( addressV != TextureAddressingType::UNKNOWN )
		p.SetAddressV( addressV );
}	
	

}
