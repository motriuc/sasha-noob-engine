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
	_pIndexBuffer( NULL )
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
	delete[] _pIndexBuffer;
}

//-------------------------------------------------------------------
void EAGLIndexBuffer::AddAsByte( const Rd3::IndexList& indexList )
{
	_indexCount = indexList.Size();
	_indexBufferSize = _indexCount * sizeof(SBYTE);
	_indexSize = sizeof(SBYTE);
	
	_type = GL_UNSIGNED_BYTE;
	
	_pIndexBuffer = new SBYTE[_indexBufferSize];
	
	for( sInt i = 0; i < _indexCount; ++i )
	{
		__S_ASSERT( indexList[i] >=  Limit::SBYTE::Min );
		__S_ASSERT( indexList[i] <= Limit::SBYTE::Max );
		
		_pIndexBuffer[i] = (SBYTE)indexList[i];
	}
}

//-------------------------------------------------------------------
void EAGLIndexBuffer::AddAsShort( const Rd3::IndexList& indexList )
{
	_indexCount = indexList.Size();
	_indexBufferSize = sizeof(SWORD)*_indexCount;
	_indexSize = sizeof(SWORD);
	
	_type = GL_UNSIGNED_SHORT;
	
	_pIndexBuffer = new SBYTE[_indexBufferSize];
	
	SWORD* pWord = (SWORD*)_pIndexBuffer;
	
	for( sInt i = 0; i < _indexCount; ++i )
	{
		__S_ASSERT( indexList[i] >=  Limit::SWORD::Min );
		__S_ASSERT( indexList[i] <= Limit::SWORD::Max );
		
		pWord[i] = (SWORD)indexList[i];
	}
}


