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
		const d2Vector& GetTx1() const		{ return _tx1; }
		const d2Vector& GetTx2() const		{ return _tx2; }

		const d3Vector& GetMove() const		{ return _move; }
		const d3Vector& GetRotate() const	{ return _rotate; }
		const d3Vector& GetScale() const	{ return _scale; }
	private:
		d3Vector	_move;
		d3Vector	_rotate;
		d3Vector	_scale;
		d2Vector	_tx1;
		d2Vector	_tx2;

		friend class Animation;
	};

	class State
	{
	public:
		State( void* pData = NULL, sDouble fps = 60.0 ) :
			_startTime( 0.0 ),
			_fps( fps ),
			_cFrame( 0 ),
			_beginAnimateFrame( 0 ),
			_endAnimateFrame( Limit::sUInt::Max ),
			_pData( pData )
		{
		}

		/**
		 * Animation events
		 */
		Events::sEvent2< const Animation& /*animation*/, State& /*animation state*/  >	onAnimationEnd;

		/**
		 *
		 */
		const sString& GetCurrentSequence() const { return _currentSequence; }

		/**
		 *
		 */
		void* GetData() { return _pData; }
		void SetData( void* pData )	{ _pData = pData; }

	private:
		sDouble	_fps;
		sDouble	_startTime;
		sUInt	_cFrame;
		Result	_cResult;
		sUInt	_beginAnimateFrame;
		sUInt	_endAnimateFrame;
		sString	_currentSequence;
		void*	_pData;

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

	/**
	 *
	 */
	void SetAnimationSequence( const sString& name, State& state ) const;
	void SetAnimationSequence( const sString& name, sUInt beginFrame, sUInt endFrame, State& state ) const;
	
	/**
	 *
	 */
	void AddAnimationSequence( const sString& name, sInt beginFrame, sInt endFrame );

	/**
	 *
	 */
	void RemoveFrames( sInt from, sInt to );

	/**
	 *
	 */
	void Move( sInt frame, const d3Point& pos ); 
private:
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

	AnimateValue	_textureDX;
	AnimateValue	_textureDY;

	typedef struct
	{
		sInt beginFrame;
		sInt endFrame;
	} AnimationSequence;

	sMap<sString, AnimationSequence>	_animationSequences;
};

}

#endif // _RD3_ANIMATION_INC_

