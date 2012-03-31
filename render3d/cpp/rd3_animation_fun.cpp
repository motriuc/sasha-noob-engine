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
void AnimateValue::AddLine( sUInt frame, d3Float value )
{
	KeyFrame keyFrame = { frame, value, Linear };
	_keyframes.Add( keyFrame );

	_maxFrame = System::FMath::Max( _maxFrame, frame );
}

//-------------------------------------------------------------------
void AnimateValue::AddPoint( sUInt frame, d3Float value )
{
	KeyFrame keyFrame = { frame, value, Point };
	_keyframes.Add( keyFrame );

	_maxFrame = System::FMath::Max( _maxFrame, frame );
}

//-------------------------------------------------------------------
void AnimateValue::RemoveFrames( sUInt from, sUInt to )
{
	if( _keyframes.Size() <= 0 )
		return;

	KeyFrame keyFrame = { from, 0.0f, Point };

	sInt ifrom = _keyframes.FindUpperBound( keyFrame );

	if( ifrom <= 0 )
		ifrom = 0;

	if( ifrom >= _keyframes.Size() )
		return;

	sInt ito = ifrom;

	while( ito < _keyframes.Size() && _keyframes[ito].frame <= to )
		++ito;

	_keyframes.Remove( ifrom, ito );
}

//-------------------------------------------------------------------
d3Float AnimateValue::GetValue( sUInt frame ) const
{
	KeyFrame keyFrame = { frame, 0.0f, Point };

	sInt k = _keyframes.FindUpperBound( keyFrame );

	if( k <= 0 )
		return _keyframes[0].value;

	if( k >= _keyframes.Size() )
		return _keyframes[_keyframes.Size()-1].value;


	sUInt f1 = _keyframes[k-1].frame;
	d3Float v1 = _keyframes[k-1].value;

	sUInt f2 = _keyframes[k].frame;
	d3Float v2 = _keyframes[k].value;
	Type type = _keyframes[k].type;

	__S_ASSERT( f1 <= frame );
	__S_ASSERT( frame <= f2 );

	d3Float result = v1;

	switch( type )
	{
	case Point:
		break;
	case Linear:
		{
			sInt df = f2 - f1;
			if( df == 0 )
				break;

			d3Float dv = v2 - v1;
			result = v1 + dv / df * ( frame - f1 ); 
		}
		break;
	case Bezier:
	default:
		__S_ASSERT( sFalse );
	}

	return result;
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
			sString type = child.GetAttributes()[ATTR_TYPE];

			if( type.Length() <= 0 || type == _S("line") )
			{
				AddLine( (sUInt) key, value );
			}
			else if( type == _S("point") )
			{
				AddPoint( (sUInt) key, value );
			}
		}
	}
}

}

