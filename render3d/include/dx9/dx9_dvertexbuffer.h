/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_dvertexbuffer.h
//  Created                 : 4 3 2012   1:22
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
#ifndef _DX9_DVERTEX_BUFFER_INC_
#define _DX9_DVERTEX_BUFFER_INC_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

#include "rd3_dvertexbuffer.h"
#include "dx9_types.h"

/**
 * Dx9DynamicVertexBuffer
 */
class Dx9DynamicVertexBuffer : public Rd3::DynamicVertexBuffer
{
private:
	typedef Rd3::DynamicVertexBuffer _BaseClass;
public:
	/**
	 *
	 */
	Dx9DynamicVertexBuffer( Rd3::Render* owner, const sString& objectName, Rd3::VertexBufferStream::Set set, sInt maxVertexCount );
	~Dx9DynamicVertexBuffer();

	LPDIRECT3DVERTEXBUFFER9 GetHandle() const	{ return _pVertexBuffer; }
	DWORD GetFVF() const						{ return _dwFVF; }
	DWORD Offset() const						{ return _vertexOffset; }
public:
	virtual sBool BeginAdd( sInt vertexCount );
	virtual void Flush();
	virtual void EndAdd();
private:
	DWORD	_dwFVF;
	DWORD	_dwDiscard;
	sInt	_vertexStart;
	sInt	_vertexOffset;

	LPDIRECT3DVERTEXBUFFER9		_pVertexBuffer;
private:
	void SetVertexData( void* pBuf, sInt vCount );
};

#endif // _DX9_DVERTEX_BUFFER_INC_