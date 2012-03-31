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
	_BaseClass( owner, objectName, ResourceType::E_ANIMATION )
{
}

//-------------------------------------------------------------------
void Animation::Animate( sDouble time, State& state, Result& result ) const
{
	if( state._startTime == 0.0 )
	{
		state._startTime = time;
		state._cFrame = 0;
		Animate( state._cFrame + state._beginAnimateFrame , state._cResult );
	}
	else
	{
		sUInt frame = static_cast<sUInt>( ( time - state._startTime ) * state._fps );

		if( frame != state._cFrame )
		{
			state._cFrame = frame;

			frame += state._beginAnimateFrame;
			if( frame >= state._endAnimateFrame )
			{
				state.onAnimationEnd( *this, state );
				state._startTime = 0.0;
				state._cFrame = 0;
			}
			else
				Animate( frame, state._cResult );
		}
	}

	result = state._cResult;
}

//-------------------------------------------------------------------
void Animation::Animate( sUInt frame, Result& result ) const
{
	result._scale.x = _scaleX.HasAnimation() ? _scaleX.GetValue( frame ) : 1.0f;
	result._scale.y = _scaleY.HasAnimation() ? _scaleY.GetValue( frame ) : 1.0f;
	result._scale.z = _scaleZ.HasAnimation() ? _scaleZ.GetValue( frame ) : 1.0f;

	result._rotate.x = _rotateX.HasAnimation() ? _rotateX.GetValue( frame ) : 0.0f;
	result._rotate.y = _rotateY.HasAnimation() ? _rotateY.GetValue( frame ) : 0.0f;
	result._rotate.z = _rotateZ.HasAnimation() ? _rotateZ.GetValue( frame ) : 0.0f;

	result._move.x = _moveX.HasAnimation() ? _moveX.GetValue( frame ) : 0.0f;
	result._move.y = _moveY.HasAnimation() ? _moveY.GetValue( frame ) : 0.0f;
	result._move.z = _moveZ.HasAnimation() ? _moveZ.GetValue( frame ) : 0.0f;

	result._tx.x = _textureX.HasAnimation() ? _textureX.GetValue( frame ) : 0.0f;
	result._tx.y = _textureY.HasAnimation() ? _textureY.GetValue( frame ) : 0.0f;
}

//-------------------------------------------------------------------
void Animation::Move( sInt frame, const d3Point& pos )
{
	_moveX.AddLine( frame, pos.x );
	_moveY.AddLine( frame, pos.y );
	_moveZ.AddLine( frame, pos.z );
}

//-------------------------------------------------------------------
void Animation::RemoveFrames( sInt from, sInt to )
{
	_moveX.RemoveFrames( from, to );
	_moveY.RemoveFrames( from, to );
	_moveZ.RemoveFrames( from, to );

	_rotateX.RemoveFrames( from, to );
	_rotateY.RemoveFrames( from, to );
	_rotateZ.RemoveFrames( from, to );

	_scaleX.RemoveFrames( from, to );
	_scaleY.RemoveFrames( from, to );
	_scaleZ.RemoveFrames( from, to );

	_textureX.RemoveFrames( from, to );
	_textureY.RemoveFrames( from, to );
}

//-------------------------------------------------------------------
void Animation::AddAnimationSequence( const sString& name, sInt beginFrame, sInt endFrame )
{
	AnimationSequence seq = { beginFrame, endFrame };
	_animationSequences.Add( name, seq );
}

//-------------------------------------------------------------------
void Animation::SetAnimationSequence( const sString& name, sUInt beginFrame, sUInt endFrame, State& state ) const
{
	state._beginAnimateFrame = beginFrame;
	state._endAnimateFrame = endFrame;

	state._currentSequence = name;
	state._startTime = 0.0;
	state._cFrame = 0;
}

//-------------------------------------------------------------------
void Animation::SetAnimationSequence( const sString& name, State& state ) const
{
	AnimationSequence seq;

	if( _animationSequences.Lookup( name, seq ) )
	{
		state._beginAnimateFrame = seq.beginFrame;
		state._endAnimateFrame = seq.endFrame;

		state._currentSequence = name;
		state._startTime = 0.0;
		state._cFrame = 0;
	}
	else
	{
		state._beginAnimateFrame = 0;
		state._endAnimateFrame = Limit::sUInt::Max;

		state._currentSequence = _S("");
		state._startTime = 0.0;
		state._cFrame = 0;
	}
}

//-------------------------------------------------------------------
void Animation::LoadFromXml( const Xml::BaseDomNode& node, const Def& def )
{
	for( sInt i = 0; i < node.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& child = node[i];
		
		if( !XmlCheckDef( child, def ) )
			continue;

		if( child.GetName() == ELEMENT_SEQUENCE )
		{
			sString name = child.GetAttributes()[ATTR_NAME];
			AnimationSequence seq = {
				child.GetAttributeValue( ATTR_FRAME_BEGIN, 0 ),
				child.GetAttributeValue( ATTR_FRAME_END, 0 )
			};
			_animationSequences.Add( name, seq );
		}
		else if( child.GetName() == ELEMENT_ANIMATION )
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

//-------------------------------------------------------------------
void Animation::Result::GetTransformation( d3Matrix& transformation ) const
{
	transformation = d3Matrix( 1.0 );

	d3Matrix tmp;
	
	if( _scale.x != 1.0f || _scale.y != 1.0f || _scale.z != 1.0f )
	{
		tmp.SetScale( _scale.x, _scale.y, _scale.z );
		transformation *= tmp;
	}

	if( _rotate.x != 0.0f || _rotate.y != 0.0f || _rotate.z != 0.0f )
	{
		tmp.SetRotateEuler( _rotate.x, _rotate.y, _rotate.z );
		transformation *= tmp;
	}
	
	if( _move.x != 0.0f || _move.y != 0.0f || _move.z != 0.0f )
	{
		tmp.SetTranslation( d3Vector( _move.x, _move.y, _move.z ) );
		transformation *= tmp;
	}
}

}