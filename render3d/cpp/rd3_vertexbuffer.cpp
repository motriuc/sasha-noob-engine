/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_vertexbuffer.cpp
//	Created                 : 20 1 2011   0:05
//	File path               : SLibF\render3d\cpp
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
#include "rd3_vertexbuffer.h"

//-------------------------------------------------------------------
COUNTER_USE( rd3_video_memory_vb )
COUNTER_USE( rd3_video_memory )
COUNTER_USE( rd3_vertex_count )
//-------------------------------------------------------------------

namespace Rd3
{

//-------------------------------------------------------------------
VertexBuffer::VertexBuffer( Render* owner, const sString& objectName ) :
	_BaseClass( owner, objectName, ResourceType::E_VERTEX_BUFFER ),
	_vertexCount( 0 ),
	_vertexBufferSize( 0 ),
	_vertexSize( 0 )
{
}

//-------------------------------------------------------------------
void VertexBuffer::PostInit()
{
	COUNTER_INT_INC( rd3_video_memory,		(sInt)_vertexBufferSize );
	COUNTER_INT_INC( rd3_video_memory_vb,	(sInt)_vertexBufferSize );
	COUNTER_INT_INC( rd3_vertex_count,		(sInt)_vertexCount );
}

//-------------------------------------------------------------------
VertexBuffer::~VertexBuffer()
{
	COUNTER_INT_INC( rd3_video_memory_vb,	-(sInt)_vertexBufferSize );	
	COUNTER_INT_INC( rd3_video_memory,		-(sInt)_vertexBufferSize );
	COUNTER_INT_INC( rd3_vertex_count,		-(sInt)_vertexCount );
}
	
}