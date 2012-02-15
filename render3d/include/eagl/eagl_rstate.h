/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_rstate.h
//	Created                 : 18 1 2012   0:05
//	File path               : SLibF\render3d\include\eagl
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//	Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

#ifndef _EAGL_RSTATE_H_
#define _EAGL_RSTATE_H_

#ifndef _EAGL_CONF_H_
	#error eagl_conf.h must be included
#endif

#include "rd3_rstate.h"

/**
 * EAGLRenderState
 */
class EAGLRenderState : public Rd3::WorldRenderState
{
private:
	typedef Rd3::WorldRenderState _BaseClass;
public:
	EAGLRenderState( Rd3::Render* owner );

	/**
	 *
	 */
	virtual void BeginWorldRender( const Rd3::EngineDataForRender& edata );

	/**
	 *
	 */
	virtual void EndWorldRender();

	/**
	 *
	 */
	virtual void RenderPrimitive( const Rd3::VertexBuffer* vb, Rd3::PrimitiveType::PrimitiveType type );
	virtual void RenderPrimitive( const Rd3::VertexBuffer* vb, const Rd3::IndexBuffer* ib, Rd3::PrimitiveType::PrimitiveType type );

	virtual void Clear( System::Types::sRGBColor color );

private:
};


#endif // _EAGL_RSTATE_H_
