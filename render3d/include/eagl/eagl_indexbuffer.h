/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_indexbuffer.h
//	Created                 : 5 2 2012   20:20
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

#ifndef _EAGL_INDEXBUFFER_H_
#define _EAGL_INDEXBUFFER_H_

#ifndef _EAGL_CONF_H_
	#error eagl_conf.h must be included
#endif

#include "rd3_indexbuffer.h"

/**
 * EAGLIndexBuffer
 */
class EAGLIndexBuffer : public Rd3::IndexBuffer
{
private:
	typedef Rd3::IndexBuffer _BaseClass;
public:
	/**
	 *
	 */
	EAGLIndexBuffer( Rd3::Render* owner, const sString& objectName, const Rd3::IndexList& indexList ); 

	/**
	 *
	 */
	virtual ~EAGLIndexBuffer();
	
	const SBYTE* GetBuffer() const		{ return _pIndexBuffer; }
	GLenum GetBufferType() const		{ return _type; }
private:
	SBYTE*	_pIndexBuffer;
	GLenum	_type;
	
	void AddAsByte( const Rd3::IndexList& indexList );
	void AddAsShort( const Rd3::IndexList& indexList ); 
};


#endif // _EAGL_INDEXBUFFER_H_
