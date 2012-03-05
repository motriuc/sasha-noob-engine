/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_dvertexbuffer.h
//  Created                 : 5 3 2012   1:22
//  File path               : SLibF\render3d\include\eagl
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
#ifndef _EAGL_DVERTEX_BUFFER_INC_
#define _EAGL_DVERTEX_BUFFER_INC_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

#include "rd3_dvertexbuffer.h"

/**
 * EAGLDynamicVertexBuffer
 */
class EAGLDynamicVertexBuffer : public Rd3::DynamicVertexBuffer
{
private:
	typedef Rd3::DynamicVertexBuffer _BaseClass;
	static const sInt vbCount = 2;
public:
	/**
	 *
	 */
	EAGLDynamicVertexBuffer( Rd3::Render* owner, const sString& objectName, Rd3::VertexBufferStream::Set vbset, sInt maxVertexCount );

	~EAGLDynamicVertexBuffer();
public:
	/**
	 *
	 */
	virtual sBool BeginAdd( sInt vertexCount );
	virtual void EndAdd();
	virtual void Flush();
	
	/**
	 * Sets vb to the attributes of the OpenGL pipeline
	 */
	void SetAttributes( const sInt* attributesId ) const;	
private:
	GLuint	_vb[vbCount];
	sInt	_cvb;
	sInt	_vertexStart;
	char*	_pBuffer;
	
	sInt	_offPoints;
	sInt	_offNormals;
	sInt	_offTx1;
	sInt	_offTx2;
	sInt	_offDiffuzeColor;
private:
	void SetVertexData( void* pBuf, sInt vCount );	
};

#endif // _EAGL_DVERTEX_BUFFER_INC_