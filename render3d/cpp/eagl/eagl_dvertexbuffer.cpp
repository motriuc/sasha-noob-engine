/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_dvertexbuffer.cpp
//  Created                 : 4 3 2012   1:22
//  File path               : SLibF\render3d\cpp\eagl
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
#include "eagl_conf.h"
#include "eagl_dvertexbuffer.h"
#include "eagl_vutil.h"

using namespace Rd3;

//------------------------------------------------------------------
EAGLDynamicVertexBuffer::EAGLDynamicVertexBuffer( Rd3::Render* owner, const sString& objectName, Rd3::VertexBufferStream::Set vbset, sInt maxVertexCount ):
	_BaseClass( owner, objectName, vbset ),
	_offPoints( -1 ),
	_offNormals( -1 ),
	_offTx1( -1 ),
	_offTx2( -1 ),
	_offDiffuzeColor( -1 ),
	_cvb( -1 )
{
	_maxVertexCount = maxVertexCount;
	
	_vertexSize = 0;
	
	if( _vbset & Rd3::VertexBufferStream::E_XYZ )
	{
		_offPoints =_vertexSize;
		_vertexSize += sizeof( GLfloat ) * 3;
	}
	
	if( _vbset & Rd3::VertexBufferStream::E_NORMAL )
	{
		_offNormals = _vertexSize;
		_vertexSize += sizeof( GLfloat ) * 3;
	}
	
	if( _vbset & Rd3::VertexBufferStream::E_COLOR_DIF )
	{
		_offDiffuzeColor = _vertexSize;
		_vertexSize += sizeof( GLubyte ) * 4;
	}
	
	if( _vbset & Rd3::VertexBufferStream::E_TX1 )
	{
		_offTx1 = _vertexSize;
		_vertexSize += sizeof( GLfloat ) * 2;
	}
	
	if( _vbset & Rd3::VertexBufferStream::E_TX2 )
	{
		_offTx2 = _vertexSize;
		_vertexSize += sizeof( GLfloat ) * 2;
	}
	
	_pBuffer = new char[ _vertexSize * CacheVertexBufferSize ];
	
	glGenBuffers( 2, _vb );
	
	for( sInt i = 0; i < vbCount; ++i )
	{
		glBindBuffer( GL_ARRAY_BUFFER, _vb[i] );
		glBufferData( GL_ARRAY_BUFFER, _vertexSize*_maxVertexCount, NULL, GL_DYNAMIC_DRAW );		
	}
}

//------------------------------------------------------------------
EAGLDynamicVertexBuffer::~EAGLDynamicVertexBuffer()
{
	delete[] _pBuffer;
	glDeleteBuffers( 2, _vb );
}

//------------------------------------------------------------------
sBool EAGLDynamicVertexBuffer::BeginAdd( sInt vertexCount )
{
	__S_ASSERT( _cacheCurrentVertex == -2 );
	
	if( vertexCount > (sInt)_maxVertexCount )
		return sFalse;
	
	_cacheCurrentVertex = -1;
	_vertexCount = vertexCount;
	_vertexStart = 0;
	_cvb = ( _cvb + 1 ) % vbCount;
	
	return sTrue;
}

//------------------------------------------------------------------
void EAGLDynamicVertexBuffer::EndAdd()
{
	__S_ASSERT( _cacheCurrentVertex >= 0 );
	Flush();
	_cacheCurrentVertex = - 2;
}

//------------------------------------------------------------------
void EAGLDynamicVertexBuffer::SetVertexData( void* pBuf, sInt vCount )
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
		
		if( _vbset & Rd3::VertexBufferStream::E_TX2 )
			VUtil::AddTexCoord( pBuf, _tx2[i] );
	}
}

//------------------------------------------------------------------
void EAGLDynamicVertexBuffer::Flush()
{
	if( _cacheCurrentVertex < 0 )
		return;
	
	sInt vertexesToAdd = _cacheCurrentVertex + 1;
		
	SetVertexData( _pBuffer, vertexesToAdd );
	
	glBindBuffer( GL_ARRAY_BUFFER, _vb[_cvb] );	
	glBufferSubData( GL_ARRAY_BUFFER, _vertexStart * _vertexSize, vertexesToAdd * _vertexSize, _pBuffer );
	
	_vertexStart+= vertexesToAdd;
}

//------------------------------------------------------------------
void EAGLDynamicVertexBuffer::SetAttributes( const sInt* attributesId ) const
{
	__S_ASSERT( _vb[_cvb] != 0 );
	
	glBindBuffer( GL_ARRAY_BUFFER, _vb[_cvb] );
	
	if( _offPoints >= 0 )
	{
		sInt p = attributesId[AttributeParameter::E_POSITION];
		
		if( p >= 0 )
		{
			glVertexAttribPointer( p, 3, GL_FLOAT, 0, _vertexSize, (void*)_offPoints );
			glEnableVertexAttribArray( p );			
		}
	}
	
	if( _offNormals >= 0 )
	{
		sInt p = attributesId[AttributeParameter::E_NORMALS];
		
		if( p >= 0 )
		{
			glVertexAttribPointer( p, 3, GL_FLOAT, 0, _vertexSize, (void*)_offNormals );
			glEnableVertexAttribArray( p );			
		}
	}
	
	if( _offDiffuzeColor >= 0 ) 
	{
		sInt p = attributesId[AttributeParameter::E_COLOR_DIFUSE];
		
		if( p >= 0 ) 
		{
			glVertexAttribPointer( p, 4, GL_UNSIGNED_BYTE, 1, _vertexSize, (void*)_offDiffuzeColor );
			glEnableVertexAttribArray( p );
			
		}
	}	
	
	if( _offTx1 >= 0 )
	{
		sInt p = attributesId[AttributeParameter::E_TX1];
		
		if( p >= 0 )
		{
			glVertexAttribPointer( p, 2, GL_FLOAT, 0, _vertexSize, (void*)_offTx1 );
			glEnableVertexAttribArray( p );			
		}
	}
	
	if( _offTx2 >= 0 )
	{
		sInt p = attributesId[AttributeParameter::E_TX2];
		
		if( p >= 0 )
		{
			glVertexAttribPointer( p, 2, GL_FLOAT, 0, _vertexSize, (void*)_offTx2 );
			glEnableVertexAttribArray( p );			
		}
	}
}
