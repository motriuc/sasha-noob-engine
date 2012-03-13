/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_animation_fun.h
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
#ifndef _RD3_ANIMATION_FUN_INC_
#define _RD3_ANIMATION_FUN_INC_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

namespace Rd3
{

using namespace System;

/**
 * AnimateValue
 */
class AnimateValue
{
public:
	enum Type
	{
		Point,
		Linear,
		Bezier // to do
	};

	/**
	 *
	 */
	AnimateValue();

	/**
	 *
	 */
	void AddLine( sUInt frame, d3Float value );

	/**
	 *
	 */
	void AddPoint( sUInt frame, d3Float value );

	/**
	 *
	 */
	d3Float GetValue( sUInt frame ) const;

	/**
	 *
	 */
	sBool HasAnimation() const { return _keyframes.Size() > 0; }

	/**
	 *
	 */
	void LoadFromXml( const Xml::BaseDomNode& node, const Def& def );

private:
	typedef struct
	{
		sUInt			frame;
		d3Float			value;
		Type			type;
	} KeyFrame;

	class Cmp_KeyFrame
	{
	public:
		inline static sBool Big( const KeyFrame& a, const KeyFrame& b )
		{
			return a.frame > b.frame;
		}
		
		inline static sBool Equal( const KeyFrame& a, const KeyFrame& b )
		{
			return a.frame == b.frame;
		}
		
		inline static sBool Small( const KeyFrame& a, const KeyFrame& b )
		{
			return a.frame < b.frame;
		}
	};

	sSorted<KeyFrame,Cmp_KeyFrame>	_keyframes;
	sUInt							_maxFrame;
};

}

#endif // _RD3_ANIMATION_FUN_INC_