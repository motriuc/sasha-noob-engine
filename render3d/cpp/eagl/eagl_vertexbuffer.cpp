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

//--------------------------------------------------------------------------------------------
EAGLVertexBuffer::~EAGLVertexBuffer()
{
	delete[] _listPoints;
	delete[] _listDiffuseColor;
	delete[] _listNormals;
	delete[] _listTx1;
	delete[] _listTx2;
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
void EAGLVertexBuffer::SetAttributes( const sInt* attributesId ) const
{
	if( _listPoints != NULL )
	{
		sInt p = attributesId[AttributeParameter::E_POSITION];
		
		if( p >= 0 )
		{
			glVertexAttribPointer( p, 3, GL_FLOAT, 0, 0, _listPoints);
			glEnableVertexAttribArray( p );			
		}
	}

	if( _listDiffuseColor != NULL ) 
	{
		sInt p = attributesId[AttributeParameter::E_COLOR_DIFUSE];
		
		if( p >= 0 ) 
		{
			glVertexAttribPointer( p, 4, GL_UNSIGNED_BYTE, 1, 0, _listDiffuseColor );
			glEnableVertexAttribArray( p );
			
		}
	}
	
	if( _listNormals != NULL )
	{
		sInt p = attributesId[AttributeParameter::E_NORMALS];
		
		if( p >= 0 )
		{
			glVertexAttribPointer( p, 3, GL_FLOAT, 0, 0, _listNormals);
			glEnableVertexAttribArray( p );			
		}
	}
	
	if( _listTx1 )
	{
		sInt p = attributesId[AttributeParameter::E_TX1];

		if( p >= 0 )
		{
			glVertexAttribPointer( p, 2, GL_FLOAT, 0, 0, _listTx1 );
			glEnableVertexAttribArray( p );			
		}
	}
	
	if( _listTx2 )
	{
		sInt p = attributesId[AttributeParameter::E_TX2];
		
		if( p >= 0 )
		{
			glVertexAttribPointer( p, 2, GL_FLOAT, 0, 0, _listTx2 );
			glEnableVertexAttribArray( p );			
		}
	}	
}

//--------------------------------------------------------------------------------------------
GLfloat* EAGLVertexBuffer::AddVectors( const Rd3::VertexPList& points )
{
	GLfloat* pVer = new GLfloat[points.Size() * 3];
	GLfloat* pV = pVer;
	
	for( sInt i = 0; i < points.Size(); ++i )
	{
		const d3Math::d3Vector& v = points[i];
		*pV = v.x;		++pV; 
		*pV = v.y;		++pV; 
		*pV = v.z;		++pV; 
	}
	
	return pVer;
}

//--------------------------------------------------------------------------------------------
GLubyte* EAGLVertexBuffer::AddColors( const Rd3::VertexCList& colors )
{
	GLubyte* pColors = new GLubyte[colors.Size()*4];
	GLubyte* pC = pColors;
	
	for( sInt i = 0; i < colors.Size(); ++i )
	{
		sRGBColor c = colors[i];
		
		*pC = RGBColor::GetByteR( c );	++pC;
		*pC = RGBColor::GetByteG( c );	++pC;
		*pC = RGBColor::GetByteB( c );	++pC;
		*pC = RGBColor::GetByteA( c );	++pC;
	}
	
	return pColors;
}

//--------------------------------------------------------------------------------------------
GLfloat* EAGLVertexBuffer::AddTx( const Rd3::VertexTxCoord& tx )
{
	GLfloat* pTex = new GLfloat[ tx.Size()*2 ];
	GLfloat* pT = pTex;
	
	for ( sInt i = 0; i < tx.Size(); ++i ) 
	{
		const d2Math::d2Vector& v = tx[i];
		
		*pT = v.x;		++pT;
		*pT = v.y;		++pT;
	}
	
	return pTex;
}

//--------------------------------------------------------------------------------------------
EAGLVertexBuffer::EAGLVertexBuffer( 
	Rd3::Render* owner,  
	const sString& objectName, 
	const Rd3::VertexPList& p
) throws_error :
	_BaseClass( owner, objectName ),
	_listPoints( NULL ),
	_listDiffuseColor( NULL ),
	_listNormals( NULL ),
	_listTx1( NULL ),
	_listTx2( NULL )
{
	_vertexCount = p.Size();
	_vertexSize = sizeof( GLfloat ) * 3;
	_vertexBufferSize = _vertexSize * _vertexCount;
	
	_listPoints = AddVectors( p );
}

//--------------------------------------------------------------------------------------------
EAGLVertexBuffer::EAGLVertexBuffer( 
								 Rd3::Render* owner,  
								 const sString& objectName, 
								 const Rd3::VertexPList& p,
								 const Rd3::VertexCList& diffuseColor
) throws_error :
	_BaseClass( owner, objectName ),
	_listPoints( NULL ),
	_listDiffuseColor( NULL ),
	_listNormals( NULL ),
	_listTx1( NULL ),
	_listTx2( NULL )
{
	__S_ASSERT( p.Size() == diffuseColor.Size() );
	
	_vertexCount = p.Size();
	_vertexSize = sizeof( GLfloat ) * 3 + sizeof( GLubyte ) * 4;
	_vertexBufferSize = _vertexSize * _vertexCount;
	
	_listPoints = AddVectors( p );
	_listDiffuseColor = AddColors( diffuseColor );

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
	_listPoints( NULL ),
	_listDiffuseColor( NULL ),
	_listNormals( NULL ),
	_listTx1( NULL ),
	_listTx2( NULL )
{
	__S_ASSERT( p.Size() == tx.Size() );
	
	_vertexCount = p.Size();
	_vertexSize = sizeof( GLfloat ) * 3 + sizeof( GLfloat ) * 2;
	_vertexBufferSize = _vertexSize * _vertexCount;	

	_listPoints = AddVectors( p );
	_listTx1 = AddTx( tx );
	
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
	_listPoints( NULL ),
	_listDiffuseColor( NULL ),
	_listNormals( NULL ),
	_listTx1( NULL ),
	_listTx2( NULL )
{
	__S_ASSERT( p.Size() == n.Size() );
	
	_vertexCount = p.Size();
	_vertexSize = sizeof( GLfloat ) * 3 + sizeof( GLfloat ) * 3;
	_vertexBufferSize = _vertexSize * _vertexCount;	
	
	_listPoints = AddVectors( p );
	_listNormals = AddVectors( n );
	
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
	_listPoints( NULL ),
	_listDiffuseColor( NULL ),
	_listNormals( NULL ),
	_listTx1( NULL ),
	_listTx2( NULL )
{
	__S_ASSERT( p.Size() == tx.Size() );
	__S_ASSERT( p.Size() == n.Size() );
	
	_vertexCount = p.Size();
	_vertexSize = sizeof( GLfloat ) * 3 + sizeof( GLfloat ) * 3 + sizeof( GLfloat ) * 2;
	_vertexBufferSize = _vertexSize * _vertexCount;	

	_listPoints = AddVectors( p );
	_listNormals = AddVectors( n );
	_listTx1 = AddTx( tx );
	
	PostInit();
}

