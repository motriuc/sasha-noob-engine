/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_dvertexbuffer.cpp
//  Created                 : 4 3 2012   1:22
//  File path               : SLibF\render3d\cpp
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
#include "rd3afx.h"
#include "dx9/dx9_conf.h"
#include "dx9/dx9_types.h"
#include "dx9/dx9_render.h"
#include "dx9/dx9_dvertexbuffer.h"
#include "dx9/dx9_vutil.h"

//------------------------------------------------------------------
Dx9DynamicVertexBuffer::Dx9DynamicVertexBuffer( Rd3::Render* owner, const sString& objectName, Rd3::VertexBufferStream::Set set, sInt maxVertexCount ):
	_BaseClass( owner, objectName, set ),
	_pVertexBuffer( NULL ),
	_vertexStart( 0 ),
	_vertexOffset( 0 ),
	_dwDiscard( D3DLOCK_NOOVERWRITE )
{
	_dwFVF = Rd3::VertexBufferStream::GetDirectX_FVF( set );
	_vertexSize = Rd3::VertexBufferStream::GetDirectX_VertexSize( set );
	_maxVertexCount = maxVertexCount;

	SDWORD dwDX_BufferSize = _maxVertexCount * _vertexSize;

	HRESULT hr = Dx9Render::GetDX9Device(GetOwner())->CreateVertexBuffer(
		dwDX_BufferSize,
		D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
		_dwFVF,
		D3DPOOL_DEFAULT,
		&_pVertexBuffer,
		NULL
	);

	if( FAILED(hr) )
		_DX9_ERROR( hr );
}

//------------------------------------------------------------------
Dx9DynamicVertexBuffer::~Dx9DynamicVertexBuffer()
{
	if( _pVertexBuffer )
		_pVertexBuffer->Release();
}

//------------------------------------------------------------------
sBool Dx9DynamicVertexBuffer::BeginAdd( sInt vertexCount )
{
	__S_ASSERT( _cacheCurrentVertex == -2 );

	if( vertexCount > (sInt)_maxVertexCount )
		return sFalse;

	_cacheCurrentVertex = -1;
	_vertexCount = vertexCount;

	if( _vertexStart + (sInt)_vertexCount > (sInt)_maxVertexCount )
	{
		_vertexStart = 0;
		_dwDiscard = D3DLOCK_DISCARD;
	}
	
	_vertexOffset = _vertexStart;
	return sFalse;
}

//------------------------------------------------------------------
void Dx9DynamicVertexBuffer::EndAdd()
{
	__S_ASSERT( _cacheCurrentVertex >= 0 );
	Flush();
	_cacheCurrentVertex = - 2;
}

//------------------------------------------------------------------
void Dx9DynamicVertexBuffer::SetVertexData( void* pBuf, sInt vCount )
{
	for( sInt i = 0; i < vCount; ++i )
	{
		if( _vbset & Rd3::VertexBufferStream::E_XYZ )
			VUtil::AddVector( pBuf, _points[i] );

		if( _vbset & Rd3::VertexBufferStream::E_NORMAL )
			VUtil::AddVector( pBuf, _normal[i] );

		if( _vbset & Rd3::VertexBufferStream::E_COLOR_DIF )
			VUtil::AddColor( pBuf, _diffuseColor[i] );

		if( _vbset & Rd3::VertexBufferStream::E_TX1 )
			VUtil::AddTexCoord( pBuf, _tx1[i] );

		if( _vbset & Rd3::VertexBufferStream::E_TX1 )
			VUtil::AddTexCoord( pBuf, _tx2[i] );
	}
}

//------------------------------------------------------------------
void Dx9DynamicVertexBuffer::Flush()
{
	if( _cacheCurrentVertex < 0 )
		return;

	sInt vertexesToAdd = _cacheCurrentVertex + 1;
	
	void* pBuf;
	HRESULT hr = _pVertexBuffer->Lock(
		_vertexStart * _vertexSize,
		vertexesToAdd * _vertexSize,
		&pBuf,
		_dwDiscard 
	);
	
	__S_ASSERT( SUCCEEDED( hr ) );
	
	SetVertexData( pBuf,vertexesToAdd );

    _pVertexBuffer->Unlock();
    _vertexStart += vertexesToAdd;
    _dwDiscard = D3DLOCK_NOOVERWRITE;
}
