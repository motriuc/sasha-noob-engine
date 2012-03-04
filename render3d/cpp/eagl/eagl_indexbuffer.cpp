/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_indexbuffer.cpp
//	Created                 : 5 2 2012   20:20
//	File path               : SLibF\render3d\cpp\eagl
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

#include "eagl_conf.h"
#include "eagl_indexbuffer.h"


//-------------------------------------------------------------------
EAGLIndexBuffer::EAGLIndexBuffer( Rd3::Render* owner, const sString& objectName, const Rd3::IndexList& indexList ):
	_BaseClass( owner, objectName ),
	_ib( 0 )
{
	sUInt max = 0;
	
	for( sInt i = 0; i < indexList.Size(); ++i )
		max = FMath::Max( max, indexList[i] );
	
	if( max < Limit::SBYTE::Max )
		AddAsByte( indexList );
	else if( max < Limit::SWORD::Max )
		AddAsShort( indexList );
	else 
	{
		__S_ASSERT( sFalse );
	}
	
	PostInit();
}

//-------------------------------------------------------------------
EAGLIndexBuffer::~EAGLIndexBuffer()
{
	if( _ib != 0 )
		glDeleteBuffers( 1, &_ib );
}

//-------------------------------------------------------------------
void EAGLIndexBuffer::AddAsByte( const Rd3::IndexList& indexList )
{
	_indexCount = indexList.Size();
	_indexBufferSize = _indexCount * sizeof(SBYTE);
	_indexSize = sizeof(SBYTE);
	
	_type = GL_UNSIGNED_BYTE;
	
	ptr_array_unique<SBYTE> pIndexBuffer( new SBYTE[_indexBufferSize] );
	
	for( sInt i = 0; i < _indexCount; ++i )
	{
		__S_ASSERT( indexList[i] >=  Limit::SBYTE::Min );
		__S_ASSERT( indexList[i] <= Limit::SBYTE::Max );
		
		pIndexBuffer[i] = (SBYTE)indexList[i];
	}
	
	glGenBuffers( 1, &_ib );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ib );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, _indexBufferSize, pIndexBuffer, GL_STATIC_DRAW );
}

//-------------------------------------------------------------------
void EAGLIndexBuffer::AddAsShort( const Rd3::IndexList& indexList )
{
	_indexCount = indexList.Size();
	_indexBufferSize = sizeof(SWORD)*_indexCount;
	_indexSize = sizeof(SWORD);
	
	_type = GL_UNSIGNED_SHORT;
	
	ptr_array_unique<SBYTE> pIndexBuffer( new SBYTE[_indexBufferSize] );
	
	SWORD* pWord = (SWORD*)pIndexBuffer.ptr();
	
	for( sInt i = 0; i < _indexCount; ++i )
	{
		__S_ASSERT( indexList[i] >=  Limit::SWORD::Min );
		__S_ASSERT( indexList[i] <= Limit::SWORD::Max );
		
		pWord[i] = (SWORD)indexList[i];
	}

	glGenBuffers( 1, &_ib );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ib );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, _indexBufferSize, pIndexBuffer, GL_STATIC_DRAW );
}


