/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_vertexbuffer.cpp
//  Created                 : 20 1 2011   0:05
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
#include "dx9/dx9_vertexbuffer.h"
#include "dx9/dx9_render.h"
#include "dx9/dx9_vutil.h"

using namespace System::d3Math;
using namespace System::d2Math;

//-------------------------------------------------------------------
Dx9VertexBuffer::Dx9VertexBuffer( 
	Rd3::Render* owner,  
	const sString& objectName, 
	const Rd3::VertexPList& p
) throws_error :
	_BaseClass( owner, objectName ),
	_pVertexBuffer( NULL ),
	_pointOffset( 0 ),
	_normalOffset( -1 )
{
	_vertexCount = p.Size();
	_dwFVF = D3DFVF_XYZ;
	_vertexSize = sizeof( float ) * 3;
	_vertexBufferSize = _vertexSize * _vertexCount;

	HRESULT hr = Dx9Render::GetDX9Device(GetOwner())->CreateVertexBuffer(
		_vertexBufferSize,
		0,
		_dwFVF,
		D3DPOOL_MANAGED,
		&_pVertexBuffer,
		NULL
	);

	if( FAILED(hr) )
		_DX9_ERROR( hr );

	void* pBuffer;

	hr = _pVertexBuffer->Lock( 0, _vertexBufferSize, &pBuffer, 0 );

	if( FAILED( hr ) )
	{
		_pVertexBuffer->Release();
		_DX9_ERROR( hr );
	}

	for( sInt i = 0; i < p.Size(); i++ )
	{
		VUtil::AddVector( pBuffer,  p[i] );
	}

	_pVertexBuffer->Unlock();
}

//-------------------------------------------------------------------
Dx9VertexBuffer::Dx9VertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& points,
		const Rd3::VertexNList& normals
	):
	_BaseClass( owner, objectName ),
	_pVertexBuffer( NULL ),
	_pointOffset( 0 ),
	_normalOffset( -1 )
{
	__S_ASSERT( points.Size() == normals.Size() );

	_vertexCount = points.Size();
	_dwFVF = D3DFVF_XYZ | D3DFVF_NORMAL;
	_vertexSize = sizeof( float ) * 6;
	_vertexBufferSize = _vertexSize * _vertexCount;

	HRESULT hr = Dx9Render::GetDX9Device(GetOwner())->CreateVertexBuffer(
		_vertexBufferSize,
		0,
		_dwFVF,
		D3DPOOL_MANAGED,
		&_pVertexBuffer,
		NULL
	);

	if( FAILED(hr) )
		_DX9_ERROR( hr );

	void* pBuffer;

	hr = _pVertexBuffer->Lock( 0, _vertexBufferSize, &pBuffer, 0 );

	if( FAILED( hr ) )
	{
		_pVertexBuffer->Release();
		_DX9_ERROR( hr );
	}

	for( sInt i = 0; i < points.Size(); i++ )
	{
		VUtil::AddVector( pBuffer, points[i] );
		VUtil::AddVector( pBuffer, normals[i] );
	}

	_pVertexBuffer->Unlock();
}

//-------------------------------------------------------------------
Dx9VertexBuffer::Dx9VertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexNList& normals,
		const Rd3::VertexTxCoord& txCoord
	) throws_error :
	_BaseClass( owner, objectName ),
	_pVertexBuffer( NULL ),
	_pointOffset( 0 ),
	_normalOffset( -1 )
{
	__S_ASSERT( points.Size() == normals.Size() );
	__S_ASSERT( normals.Size() == txCoord.Size() );

	_vertexCount = points.Size();
	_dwFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
	_vertexSize = sizeof( float ) * 8;
	_vertexBufferSize = _vertexSize * _vertexCount;

	HRESULT hr = Dx9Render::GetDX9Device(GetOwner())->CreateVertexBuffer(
		_vertexBufferSize,
		0,
		_dwFVF,
		D3DPOOL_MANAGED,
		&_pVertexBuffer,
		NULL
	);

	if( FAILED(hr) )
		_DX9_ERROR( hr );

	void* pBuffer;

	hr = _pVertexBuffer->Lock( 0, _vertexBufferSize, &pBuffer, 0 );

	if( FAILED( hr ) )
	{
		_pVertexBuffer->Release();
		_DX9_ERROR( hr );
	}

	for( sInt i = 0; i < points.Size(); i++ )
	{
		VUtil::AddVector( pBuffer, points[i] );
		VUtil::AddVector( pBuffer, normals[i] );
		VUtil::AddTexCoord( pBuffer, txCoord[i] );
	}

	_pVertexBuffer->Unlock();
}

//-------------------------------------------------------------------
Dx9VertexBuffer::Dx9VertexBuffer( 
	Rd3::Render* owner,  
	const sString& objectName, 
	const Rd3::VertexPList& p,
	const Rd3::VertexTxCoord& tx
) throws_error :
	_BaseClass( owner, objectName ),
	_pVertexBuffer( NULL ),
	_pointOffset( 0 ),
	_normalOffset( -1 )
{
	_vertexCount = p.Size();
	_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1;
	_vertexSize = sizeof( float ) * 5;
	_vertexBufferSize = _vertexSize * _vertexCount;

	HRESULT hr = Dx9Render::GetDX9Device(GetOwner())->CreateVertexBuffer(
		_vertexBufferSize,
		0,
		_dwFVF,
		D3DPOOL_MANAGED,
		&_pVertexBuffer,
		NULL
	);

	if( FAILED(hr) )
		_DX9_ERROR( hr );

	void* pBuffer;

	hr = _pVertexBuffer->Lock( 0, _vertexBufferSize, &pBuffer, 0 );

	if( FAILED( hr ) )
	{
		_pVertexBuffer->Release();
		_DX9_ERROR( hr );
	}

	for( sInt i = 0; i < p.Size(); i++ )
	{
		VUtil::AddVector( pBuffer, p[i] );
		VUtil::AddTexCoord( pBuffer, tx[i] );
	}

	_pVertexBuffer->Unlock();
}

//-------------------------------------------------------------------
Dx9VertexBuffer::Dx9VertexBuffer( 
	Rd3::Render* owner,  
	const sString& objectName, 
	const Rd3::VertexPList& p,
	const Rd3::VertexTxCoord& tx1,
	const Rd3::VertexTxCoord& tx2
) throws_error :
	_BaseClass( owner, objectName ),
	_pVertexBuffer( NULL ),
	_pointOffset( 0 ),
	_normalOffset( -1 )
{
	_vertexCount = p.Size();
	_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEX2;
	_vertexSize = sizeof( float ) * 7;
	_vertexBufferSize = _vertexSize * _vertexCount;

	HRESULT hr = Dx9Render::GetDX9Device(GetOwner())->CreateVertexBuffer(
		_vertexBufferSize,
		0,
		_dwFVF,
		D3DPOOL_MANAGED,
		&_pVertexBuffer,
		NULL
	);

	if( FAILED(hr) )
		_DX9_ERROR( hr );

	void* pBuffer;

	hr = _pVertexBuffer->Lock( 0, _vertexBufferSize, &pBuffer, 0 );

	if( FAILED( hr ) )
	{
		_pVertexBuffer->Release();
		_DX9_ERROR( hr );
	}

	for( sInt i = 0; i < p.Size(); i++ )
	{
		VUtil::AddVector( pBuffer, p[i] );
		VUtil::AddTexCoord( pBuffer, tx1[i] );
		VUtil::AddTexCoord( pBuffer, tx2[i] );
	}

	_pVertexBuffer->Unlock();
}

//-------------------------------------------------------------------
Dx9VertexBuffer::Dx9VertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexCList& diffuseColor,
		const Rd3::VertexTxCoord& tx1,
		const Rd3::VertexTxCoord& tx2
) throws_error :
	_BaseClass( owner, objectName ),
	_pVertexBuffer( NULL ),
	_pointOffset( 0 ),
	_normalOffset( -1 )
{
	_vertexCount = p.Size();
	_dwFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEX2;
	_vertexSize = sizeof( float ) * 7 + sizeof(DWORD);;
	_vertexBufferSize = _vertexSize * _vertexCount;

	HRESULT hr = Dx9Render::GetDX9Device(GetOwner())->CreateVertexBuffer(
		_vertexBufferSize,
		0,
		_dwFVF,
		D3DPOOL_MANAGED,
		&_pVertexBuffer,
		NULL
	);

	if( FAILED(hr) )
		_DX9_ERROR( hr );

	void* pBuffer;

	hr = _pVertexBuffer->Lock( 0, _vertexBufferSize, &pBuffer, 0 );

	if( FAILED( hr ) )
	{
		_pVertexBuffer->Release();
		_DX9_ERROR( hr );
	}

	for( sInt i = 0; i < p.Size(); i++ )
	{
		VUtil::AddVector( pBuffer, p[i] );
		VUtil::AddColor( pBuffer, diffuseColor[i] );
		VUtil::AddTexCoord( pBuffer, tx1[i] );
		VUtil::AddTexCoord( pBuffer, tx2[i] );
	}

	_pVertexBuffer->Unlock();
}

//-------------------------------------------------------------------
Dx9VertexBuffer::Dx9VertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexCList& diffuseColor
) throws_error :
	_BaseClass( owner, objectName ),
	_pVertexBuffer( NULL ),
	_pointOffset( 0 ),
	_normalOffset( -1 )
{
	__S_ASSERT( p.Size() == diffuseColor.Size() );

	_vertexCount = p.Size();
	_dwFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	_vertexSize = sizeof( float ) * 3 + sizeof(DWORD);
	_vertexBufferSize = _vertexSize * _vertexCount;

	HRESULT hr = Dx9Render::GetDX9Device(GetOwner())->CreateVertexBuffer(
		_vertexBufferSize,
		0,
		_dwFVF,
		D3DPOOL_MANAGED,
		&_pVertexBuffer,
		NULL
	);

	if( FAILED(hr) )
	{
		_DX9_ERROR( hr );
	}

	void* pBuffer;

	hr = _pVertexBuffer->Lock( 0, _vertexBufferSize, &pBuffer, 0 );

	if( FAILED( hr ) )
	{
		_pVertexBuffer->Release();
		_DX9_ERROR( hr );
	}

	for( sInt i = 0; i < p.Size(); i++ )
	{
		VUtil::AddVector( pBuffer, p[i] );
		VUtil::AddColor( pBuffer, diffuseColor[i] );
	}

	_pVertexBuffer->Unlock();
}

//-------------------------------------------------------------------
Dx9VertexBuffer::Dx9VertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexNList& n,
		const Rd3::VertexCList& diffuseColor
	) throws_error :
	_BaseClass( owner, objectName ),
	_pVertexBuffer( NULL ),
	_pointOffset( 0 ),
	_normalOffset( 3*sizeof( float ) )
{
	__S_ASSERT( p.Size() == diffuseColor.Size() );
	__S_ASSERT( p.Size() == n.Size() );

	_vertexCount = p.Size();
	_dwFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;
	_vertexSize = sizeof( float ) * 6 + sizeof(DWORD);
	_vertexBufferSize = _vertexSize * _vertexCount;

	HRESULT hr = Dx9Render::GetDX9Device(GetOwner())->CreateVertexBuffer(
		_vertexBufferSize,
		0,
		_dwFVF,
		D3DPOOL_MANAGED,
		&_pVertexBuffer,
		NULL
	);

	if( FAILED(hr) )
	{
		_DX9_ERROR( hr );
	}

	void* pBuffer;

	hr = _pVertexBuffer->Lock( 0, _vertexBufferSize, &pBuffer, 0 );

	if( FAILED( hr ) )
	{
		_pVertexBuffer->Release();
		_DX9_ERROR( hr );
	}

	for( sInt i = 0; i < p.Size(); i++ )
	{
		VUtil::AddVector( pBuffer, p[i] );
		VUtil::AddVector( pBuffer, n[i] );
		VUtil::AddColor( pBuffer, diffuseColor[i] );
	}

	_pVertexBuffer->Unlock();
}

//-------------------------------------------------------------------
void Dx9VertexBuffer::GetVectorList( sInt offset, System::d3Math::d3VectorList& v ) const
{
	v.RemoveAll( sFalse );

	if( offset < 0 )
		return;

	v.Reserve( _vertexCount );

	void* pBuffer;
	HRESULT hr = _pVertexBuffer->Lock( 0, _vertexBufferSize, &pBuffer, 0 );

	if( FAILED( hr ) )
		return;

	SBYTE* p = ( (SBYTE*)pBuffer ) + offset;

	for( sUInt i = 0; i < _vertexCount; i++ )
	{
		v.Add( d3Vector( (float*)p ));
		p+= _vertexSize;
	}

	_pVertexBuffer->Unlock();
}

//-------------------------------------------------------------------
Dx9VertexBuffer::~Dx9VertexBuffer()
{
	if( _pVertexBuffer )
		_pVertexBuffer->Release();
}

//-------------------------------------------------------------------
void Dx9VertexBuffer::GetPoints( Rd3::VertexPList& points ) const
{
	GetVectorList( _pointOffset, points );
}

//-------------------------------------------------------------------
void Dx9VertexBuffer::GetNormals( Rd3::VertexNList& normals ) const
{
	GetVectorList( _normalOffset, normals );
}

//-------------------------------------------------------------------
void Dx9VertexBuffer::GetDiffuseColor( Rd3::VertexCList& colors ) const
{
	__S_ASSERT( sFalse );
}

//-------------------------------------------------------------------
void Dx9VertexBuffer::ComputeBoundingBox( d3AABBox& bbox ) const
{
	bbox = d3AABBox::GetEmpty();

	void* pBuffer;

	HRESULT hr = _pVertexBuffer->Lock( 0, _vertexBufferSize, &pBuffer, 0 );

	if( FAILED( hr ) )
		return;

	SBYTE* p = ( (SBYTE*)pBuffer );

	for( sUInt i = 0; i < _vertexCount; i++ )
	{
		bbox.Add( d3Vector( (float*)p ));
		p+= _vertexSize;
	}

	_pVertexBuffer->Unlock();

}
	
//-------------------------------------------------------------------
void Dx9VertexBuffer::ComputeBoundingBox( d3AABBox& bbox, const d3Matrix& tran ) const
{
	__S_ASSERT( sFalse );
}
