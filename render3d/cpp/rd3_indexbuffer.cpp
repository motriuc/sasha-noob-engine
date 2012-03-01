/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_indexbuffer.cpp
//  Created                 : 28 1 2011   20:05
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
#include "rd3_indexbuffer.h"

//-------------------------------------------------------------------
COUNTER_USE( rd3_video_memory_ib )
COUNTER_USE( rd3_video_memory )
COUNTER_USE( rd3_index_count )
//-------------------------------------------------------------------

namespace Rd3
{

//-------------------------------------------------------------------
IndexBuffer::IndexBuffer( Render* owner, const sString& objectName ) :
	_BaseClass( owner, objectName, ResourceType::E_INDEX_BUFFER ),
	_indexCount( 0 ),
	_indexBufferSize( 0 ),
	_indexSize( 0 )
{
}

//-------------------------------------------------------------------
void IndexBuffer::PostInit()
{
	COUNTER_INT_INC( rd3_video_memory,		(sInt)_indexBufferSize );
	COUNTER_INT_INC( rd3_video_memory_ib,	(sInt)_indexBufferSize );
	COUNTER_INT_INC( rd3_index_count,		(sInt)_indexCount );	
}
	
//-------------------------------------------------------------------
IndexBuffer::~IndexBuffer()
{
	COUNTER_INT_INC( rd3_video_memory,		-(sInt)_indexBufferSize );
	COUNTER_INT_INC( rd3_video_memory_ib,	-(sInt)_indexBufferSize );
	COUNTER_INT_INC( rd3_index_count,		-(sInt)_indexCount );	
}
	
	
}

