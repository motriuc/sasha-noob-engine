/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_indexbuffer.cpp
//	Created                 : 23 1 2011   22:43
//	File path               : SLibF\render3d\dx9\cpp
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

#include "rd3afx.h"

#include "dx9/dx9_conf.h"
#include "dx9/dx9_indexbuffer.h"
#include "dx9/dx9_render.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

Dx9IndexBuffer::Dx9IndexBuffer( Rd3::Render* owner, const sString& objectName, const Rd3::IndexList& indexList ) :
	_BaseClass( owner, objectName ),
	_pIndexBuffer( NULL )
{
	_indexCount = indexList.Size();
	_indexSize = sizeof( WORD );
	_indexBufferSize = _indexSize * _indexCount;
	_dwIF = D3DFMT_INDEX16;

	HRESULT hr = Dx9Render::GetDX9Device(GetOwner())->CreateIndexBuffer(
		_indexBufferSize,
		0,
		_dwIF,
		D3DPOOL_MANAGED,
		&_pIndexBuffer,
		NULL
	);

	if( FAILED(hr) )
		_DX9_ERROR( hr );

	
	void* pData;
	hr = _pIndexBuffer->Lock( 0, _indexBufferSize, &pData, 0 );

	if( FAILED(hr) )
	{
		_pIndexBuffer->Release();
		_DX9_ERROR( hr );
	}
	
	WORD* pIndexData = (WORD*)pData;

	for( sInt i = 0; i < indexList.Size(); i++ )
	{
		*pIndexData = (WORD)indexList[i];
		++pIndexData;
	}

	_pIndexBuffer->Unlock();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

Dx9IndexBuffer::~Dx9IndexBuffer()
{
	if( _pIndexBuffer )
		_pIndexBuffer->Release();
}
