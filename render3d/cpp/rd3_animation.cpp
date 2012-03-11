/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_animation.cpp
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
#include "rd3_animation.h"
#include "rd3_xml_def.h"

namespace Rd3
{

//-------------------------------------------------------------------
Animation::Animation( Render* owner, const sString& objectName ):
	_BaseClass( owner, objectName, ResourceType::E_ANIMATION ),
	_maxFrames( 0 )
{
}

//-------------------------------------------------------------------
void Animation::Animate( sDouble time, State& state, Result& result ) const
{
	if( state._startTime == 0.0 )
	{
		state._startTime = time;
		state._cFrame = 0;
		Animate( state._cFrame, state._cResult );
	}
	else
	{
		sUInt frame = static_cast<sUInt>( ( time - state._startTime ) * state._fps );

		if( frame != state._cFrame )
		{
			state._cFrame = frame;
			Animate( state._cFrame, state._cResult );
		}
	}

	result = state._cResult;
}

//-------------------------------------------------------------------
void Animation::Animate( sUInt frame, Result& result ) const
{
	d3Matrix transformation( 1.0f );
	d3Matrix tmp;
	{
		d3Float sx = _scaleX.HasAnimation() ? _scaleX.GetValue( frame ) : 1.0f;
		d3Float sy = _scaleY.HasAnimation() ? _scaleY.GetValue( frame ) : 1.0f;
		d3Float sz = _scaleZ.HasAnimation() ? _scaleZ.GetValue( frame ) : 1.0f;

		if( sx != 1.0f || sy != 1.0f || sz != 1.0f )
		{
			tmp.SetScale( sx, sy, sz );
			transformation *= tmp;
		}
	}
	
	{
		d3Float ax = _rotateX.HasAnimation() ? _rotateX.GetValue( frame ) : 0.0f;
		d3Float ay = _rotateY.HasAnimation() ? _rotateY.GetValue( frame ) : 0.0f;
		d3Float az = _rotateZ.HasAnimation() ? _rotateZ.GetValue( frame ) : 0.0f;

		if( ax != 0.0f || ay != 0.0f || az != 0.0f )
		{
			tmp.SetRotateEuler( ax, ay, az );
			transformation *= tmp;
		}
	}
	
	{
		d3Float dx = _moveX.HasAnimation() ? _moveX.GetValue( frame ) : 0.0f;
		d3Float dy = _moveY.HasAnimation() ? _moveY.GetValue( frame ) : 0.0f;
		d3Float dz = _moveZ.HasAnimation() ? _moveZ.GetValue( frame ) : 0.0f;

		if( dx != 0.0f || dy != 0.0f || dz != 0.0f )
		{
			tmp.SetTranslation( d3Vector( dx, dy, dz ) );
			transformation *= tmp;
		}
	}

	d3Float tx;
	d3Float ty;

	{
		tx = _textureX.HasAnimation() ? _textureX.GetValue( frame ) : 0.0f;
		ty = _textureY.HasAnimation() ? _textureY.GetValue( frame ) : 0.0f;
	}

	result._tx = d2Vector( tx, ty );
	result._transformation = transformation;
}

//-------------------------------------------------------------------
void Animation::LoadFromXml( const Xml::BaseDomNode& node, const Def& def )
{
	for( sInt i = 0; i < node.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& child = node[i];
		
		if( !XmlCheckDef( child, def ) )
			continue;

		if( child.GetName() == ELEMENT_ANIMATION )
		{
			sString type = child.GetAttributes()[ATTR_TYPE];
			sString what = child.GetAttributes()[ATTR_WHAT];

			AnimateValue* pAnimValue = NULL;

			if( type == _S("move") )
			{
				if( what == _S("X") )
					pAnimValue = &_moveX;
				else if( what == _S("Y") )
					pAnimValue = &_moveY;
				else if( what == _S("Z") )
					pAnimValue = &_moveZ;	
			}
			else if( type == _S("rotate") )
			{
				if( what == _S("X") )
					pAnimValue = &_rotateX;
				else if( what == _S("Y") )
					pAnimValue = &_rotateY;
				else if( what == _S("Z") )
					pAnimValue = &_rotateZ;
			}
			else if( type == _S("scale") )
			{
				if( what == _S("X") )
					pAnimValue = &_scaleX;
				else if( what == _S("Y") )
					pAnimValue = &_scaleY;
				else if( what == _S("Z") )
					pAnimValue = &_scaleZ;
			}
			else if( type == _S("texture") )
			{
				if( what == _S("X") )
					pAnimValue = &_textureX;
				else if( what == _S("Y") )
					pAnimValue = &_textureY;
			}

			if( pAnimValue != NULL )
			{
				pAnimValue->LoadFromXml( child, def );
			}
		}
	}
}

}