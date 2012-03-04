/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_vertexbuffer.cpp
//  Created                 : 18 1 2012   0:05
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

#include "eagl_conf.h"
#include "eagl_vertexbuffer.h"

using namespace System;
using namespace Rd3;

//-------------------------------------------------------------------
inline void AddVector( void*& pBuffer, const d3Vector& v )
{
	GLfloat* pV = (GLfloat*)( pBuffer );
	
	*pV = v.x;		++pV; 
	*pV = v.y;		++pV; 
	*pV = v.z;		++pV; 
	
	pBuffer = pV;
}

//-------------------------------------------------------------------
inline void AddVector( void*& pBuffer, const d2Vector& v )
{
	GLfloat* pV = (GLfloat*)( pBuffer );
	
	*pV = v.x;		++pV; 
	*pV = v.y;		++pV; 
	
	pBuffer = pV;
}

//-------------------------------------------------------------------
inline void AddTexCoord( void*& pBuffer, const d2Vector& v )
{
	GLfloat* pV = (float*)( pBuffer );
	
	*pV = v.x;		++pV; 
	*pV = v.y;		++pV; 
	
	pBuffer = pV;
}

//-------------------------------------------------------------------
inline void AddColor( void*& pBuffer, sRGBColor c )
{
	GLubyte* pC = (GLubyte*)( pBuffer );
	
	*pC = RGBColor::GetByteR( c );  ++pC;
	*pC = RGBColor::GetByteG( c );  ++pC;
	*pC = RGBColor::GetByteB( c );  ++pC;
	*pC = RGBColor::GetByteA( c );  ++pC;
	
	pBuffer = pC;
}

//--------------------------------------------------------------------------------------------
void EAGLVertexBuffer::CreateVb( 
								const Rd3::VertexPList* p,
								const Rd3::VertexNList* n,
								const Rd3::VertexCList* diffuseColor,
								const Rd3::VertexTxCoord* tx1,
								const Rd3::VertexTxCoord* tx2 
								)
{
	__S_ASSERT( _offPoints ==  -1 );
	__S_ASSERT( _offNormals == -1 ),
	__S_ASSERT( _offTx1 == -1 );
	__S_ASSERT( _offTx2 == -1 );
	__S_ASSERT( _offDiffuzeColor ==  -1 );
	
	__S_ASSERT( p!= NULL );
	
	__S_ASSERT( n == NULL || ( n!= NULL && n->Size() == p->Size() ) );
	__S_ASSERT( diffuseColor == NULL || ( diffuseColor!= NULL && diffuseColor->Size() == p->Size() ) );
	__S_ASSERT( tx1 == NULL || ( tx1!= NULL && tx1->Size() == p->Size() ) );
	__S_ASSERT( tx2 == NULL || ( tx2!= NULL && tx1->Size() == p->Size() ) );
	
	_vertexCount = p->Size();
	_vertexSize = 0;
	
	_offPoints =_vertexSize;
	_vertexSize += sizeof( GLfloat ) * 3;
	
	if( n != NULL )
	{
		_offNormals = _vertexSize;
		_vertexSize += sizeof( GLfloat ) * 3;
	}
	
	if( diffuseColor != NULL )
	{
		_offDiffuzeColor = _vertexSize;
		_vertexSize += sizeof( GLubyte ) * 4;
	}
	
	if( tx1 != NULL )
	{
		_offTx1 = _vertexSize;
		_vertexSize += sizeof( GLfloat ) * 2;
	}

	if( tx2 != NULL )
	{
		_offTx2 = _vertexSize;
		_vertexSize += sizeof( GLfloat ) * 2;
	}
	
	_vertexBufferSize = _vertexSize * _vertexCount;	
	
	_bbox = d3AABBox::GetEmpty();
	
	ptr_array_unique<char> buffer( new char[_vertexBufferSize] );
	
	void* pBuffer = buffer;
	
	for( sInt i = 0; i < p->Size(); i++ )
	{
		AddVector( pBuffer, (*p)[i] );
		_bbox.Add( (*p)[i] );
		
		if( n!= NULL )
			AddVector( pBuffer, (*n)[i] );
		   
		if( diffuseColor != NULL )
			AddColor( pBuffer, (*diffuseColor)[i] );
		
		if( tx1 != NULL )
			AddTexCoord( pBuffer, (*tx1)[i] );

		if( tx2 != NULL )
			AddTexCoord( pBuffer, (*tx2)[i] );
	}
	
	glGenBuffers( 1, &_vb );
	glBindBuffer( GL_ARRAY_BUFFER, _vb );
	glBufferData( GL_ARRAY_BUFFER, _vertexBufferSize, buffer, GL_STATIC_DRAW );
}

//--------------------------------------------------------------------------------------------
EAGLVertexBuffer::~EAGLVertexBuffer()
{
	if( _vb != 0 )
		glDeleteBuffers( 1, &_vb );
}

//--------------------------------------------------------------------------------------------
void EAGLVertexBuffer::GetPoints( Rd3::VertexPList& points ) const
{
	__S_ASSERT( sFalse );
}

//--------------------------------------------------------------------------------------------
void EAGLVertexBuffer::GetNormals( Rd3::VertexNList& normals ) const
{
	__S_ASSERT( sFalse );
}

//--------------------------------------------------------------------------------------------
void EAGLVertexBuffer::GetDiffuseColor( Rd3::VertexCList& colors ) const
{
	__S_ASSERT( sFalse );
}

//--------------------------------------------------------------------------------------------
void EAGLVertexBuffer::ComputeBoundingBox( d3AABBox& bbox ) const
{
	bbox = _bbox;
}

//--------------------------------------------------------------------------------------------
void EAGLVertexBuffer::ComputeBoundingBox( d3AABBox& bbox, const d3Matrix& tran ) const
{
	__S_ASSERT( sFalse );
}

//--------------------------------------------------------------------------------------------
void EAGLVertexBuffer::SetAttributes( const sInt* attributesId ) const
{
	__S_ASSERT( _vb != 0 );
	
	glBindBuffer( GL_ARRAY_BUFFER, _vb );
	
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

//--------------------------------------------------------------------------------------------
EAGLVertexBuffer::EAGLVertexBuffer( 
	Rd3::Render* owner,  
	const sString& objectName, 
	const Rd3::VertexPList& p
) throws_error :
	_BaseClass( owner, objectName ),
	_vb( 0 ),
	_offPoints( -1 ),
	_offNormals( -1 ),
	_offTx1( -1 ),
	_offTx2( -1 ),
	_offDiffuzeColor( -1 )
{
	CreateVb( &p );
	PostInit();
}

//--------------------------------------------------------------------------------------------
EAGLVertexBuffer::EAGLVertexBuffer( 
								 Rd3::Render* owner,  
								 const sString& objectName, 
								 const Rd3::VertexPList& p,
								 const Rd3::VertexCList& diffuseColor
) throws_error :
	_BaseClass( owner, objectName ),
	_vb( 0 ),

	_offPoints( -1 ),
	_offNormals( -1 ),
	_offTx1( -1 ),
	_offTx2( -1 ),
	_offDiffuzeColor( -1 )
{
	CreateVb( &p, NULL, &diffuseColor );			
	PostInit();
}

//--------------------------------------------------------------------------------------------
EAGLVertexBuffer::EAGLVertexBuffer( 
				 Rd3::Render* owner,  
				 const sString& objectName, 
				 const Rd3::VertexPList& p,
				 const Rd3::VertexTxCoord& tx
) throws_error :
	_BaseClass( owner, objectName ),
	_vb( 0 ),

	_offPoints( -1 ),
	_offNormals( -1 ),
	_offTx1( -1 ),
	_offTx2( -1 ),
	_offDiffuzeColor( -1 )
{
	CreateVb( &p, NULL, NULL, &tx );			
	PostInit();
}

//--------------------------------------------------------------------------------------------
EAGLVertexBuffer::EAGLVertexBuffer( 
				 Rd3::Render* owner,  
				 const sString& objectName, 
				 const Rd3::VertexPList& p,
				 const Rd3::VertexNList& n
) throws_error :
	_BaseClass( owner, objectName ),
	_vb( 0 ),
	_offPoints( -1 ),
	_offNormals( -1 ),
	_offTx1( -1 ),
	_offTx2( -1 ),
	_offDiffuzeColor( -1 )

{
	CreateVb( &p, &n );		
	PostInit();	
}


//--------------------------------------------------------------------------------------------
EAGLVertexBuffer::EAGLVertexBuffer( 
				 Rd3::Render* owner,  
				 const sString& objectName, 
				 const Rd3::VertexPList& p,
				 const Rd3::VertexNList& n,
				 const Rd3::VertexTxCoord& tx
) throws_error :
	_BaseClass( owner, objectName ),
	_vb( 0 ),
	_offPoints( -1 ),
	_offNormals( -1 ),
	_offTx1( -1 ),
	_offTx2( -1 ),
	_offDiffuzeColor( -1 )
{
	CreateVb( &p, &n, NULL, &tx );	
	PostInit();
}

