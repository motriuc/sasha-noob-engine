/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_animation_fun.cpp
//  Created                 : 9 3 2012
//  File path               : SLibF\render3d\include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

#include "rd3afx.h"
#include "rd3_animation_fun.h"
#include "rd3_xml_def.h"

namespace Rd3
{

//-------------------------------------------------------------------
AnimateValue::AnimateValue() :
	_maxFrame( 0 )
{
}

//-------------------------------------------------------------------
void AnimateValue::Add( sUInt frame, d3Float value )
{
	KeyFrame keyFrame = { frame, value };
	_keyframes.Add( keyFrame );

	_maxFrame = System::FMath::Max( _maxFrame, frame );
}

//-------------------------------------------------------------------
d3Float AnimateValue::GetValue( sUInt frame ) const
{
	KeyFrame keyFrame = { frame, 0.0f };

	sInt k = _keyframes.FindUpperBound( keyFrame );

	if( k <= 0 )
		return _keyframes[0].value;

	if( k >= _keyframes.Size() )
		return _keyframes[_keyframes.Size()-1].value;

	sUInt f1 = _keyframes[k-1].frame;
	d3Float v1 = _keyframes[k-1].value;

	sUInt f2 = _keyframes[k].frame;
	d3Float v2 = _keyframes[k].value;

	__S_ASSERT( f1 <= frame );
	__S_ASSERT( frame <= f2 );

	sInt df = f2 - f1;
	if( df == 0 )
		return v1;

	d3Float dv = v2 - v1;

	return v1 + dv / df * ( frame - f1 ); 
}

//-------------------------------------------------------------------
void AnimateValue::LoadFromXml( const Xml::BaseDomNode& node, const Def& def )
{
	for( sInt i = 0; i < node.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& child = node[i];
		
		if( !XmlCheckDef( child, def ) )
			continue;

		if( child.GetName() == ELEMENT_KEYFRAME )
		{
			sInt key = child.GetAttributeValue( ATTR_ID, -1 );
			d3Float value = child.GetAttributeValue( ATTR_VALUE, 0.0f );

			if( key >= 0 )
			{
				Add( (sUInt) key, value );
			}
		}
	}
}

}

