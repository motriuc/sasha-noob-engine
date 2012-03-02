/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_indexbuffer.h
//  Created                 : 28 1 2011   20:20
//  File path               : SLibF\render3d\include\dx9
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
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

#ifndef _DX9_INDEXBUFFER_H_
#define _DX9_INDEXBUFFER_H_

#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

#include "rd3_indexbuffer.h"

/**
 *
 */
class Dx9IndexBuffer : public Rd3::IndexBuffer
{
private:
	typedef Rd3::IndexBuffer _BaseClass;
public:
	/**
	 *
	 */
	Dx9IndexBuffer( Rd3::Render* owner, const sString& objectName, const Rd3::IndexList& indexList ); 

	/**
	 *
	 */
	virtual ~Dx9IndexBuffer();

	/**
	 *
	 */
	LPDIRECT3DINDEXBUFFER9 GetHandle() const { return _pIndexBuffer; }

	/**
	 *
	 */
	D3DFORMAT GetIF() const	{ return _dwIF; }
private:
	LPDIRECT3DINDEXBUFFER9     _pIndexBuffer;
	D3DFORMAT                  _dwIF;
};


#endif // _DX9_INDEXBUFFER_H_
