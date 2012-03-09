/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_animation.h
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
#ifndef _RD3_ANIMATION_INC_
#define _RD3_ANIMATION_INC_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_animation_fun.h"

namespace Rd3
{

using namespace System::d3Math;
using namespace System;

/**
 * Animation
 */
class Animation
{
public:
	/**
	 * Result
	 */
	class Result
	{
	public:
		const d3Matrix& GetTransformation() const { return _transformation; }
	private:
		d3Matrix	_transformation;

		friend class Animation;
	};
public:
	/**
	 *
	 */
	Animation();

	/**
	 *
	 */
	void Animate( sUInt frame, Result& result ) const;
	void Animate( sDouble time, Result& result ) const;

	/**
	 *
	 */
	void LoadFromXml( const Xml::BaseDomNode& node, const Def& def );
private:
	sInt			_maxFrames;
	sDouble			_fps;

	mutable sDouble	_startTime;
	mutable sUInt	_cFrame;
	mutable Result	_cResult;

	AnimateValue	_moveX;
	AnimateValue	_moveY;
	AnimateValue	_moveZ;

	AnimateValue	_rotateX;
	AnimateValue	_rotateY;
	AnimateValue	_rotateZ;

	AnimateValue	_scaleX;
	AnimateValue	_scaleY;
	AnimateValue	_scaleZ;
};

}

#endif // _RD3_ANIMATION_INC_

