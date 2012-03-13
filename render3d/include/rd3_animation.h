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
#include "rd3_resobj.h"

namespace Rd3
{

using namespace System::d3Math;
using namespace System::d2Math;
using namespace System;

/**
 * Animation
 */
class Animation : public ResourceObject
{
private:
	typedef ResourceObject _BaseClass;
public:
	/**
	 * Result
	 */
	class Result
	{
	public:
		/**
		 * Get object animation transformation
		 */
		void GetTransformation( d3Matrix& matrix ) const;

		/**
		 * Get Texture animation positions
		 */
		const d2Vector& GetTx() const { return _tx; }

		d3Vector GetMove() const	{ return _move; }
		d3Vector GetRotate() const	{ return _rotate; }
		d3Vector GetScale() const	{ return _scale; }
	private:
		d3Vector	_move;
		d3Vector	_rotate;
		d3Vector	_scale;
		d2Vector	_tx;

		friend class Animation;
	};

	class State
	{
	public:
		State( sDouble fps = 60.0 ) :
			_startTime( 0.0 ),
			_fps( fps ),
			_cFrame( 0 )
		{
		}

	private:
		sDouble	_fps;
		sDouble	_startTime;
		sUInt	_cFrame;
		Result	_cResult;

		friend class Animation;
	};
public:
	/**
	 *
	 */
	Animation( Render* owner, const sString& objectName );

	/**
	 *
	 */
	void Animate( sUInt frame, Result& result ) const;
	void Animate( sDouble time, State& state, Result& result ) const;

	/**
	 *
	 */
	void LoadFromXml( const Xml::BaseDomNode& node, const Def& def );
private:
	sInt			_maxFrames;

	AnimateValue	_moveX;
	AnimateValue	_moveY;
	AnimateValue	_moveZ;

	AnimateValue	_rotateX;
	AnimateValue	_rotateY;
	AnimateValue	_rotateZ;

	AnimateValue	_scaleX;
	AnimateValue	_scaleY;
	AnimateValue	_scaleZ;

	AnimateValue	_textureX;
	AnimateValue	_textureY;
};

}

#endif // _RD3_ANIMATION_INC_

