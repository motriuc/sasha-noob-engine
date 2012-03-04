/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_dvertexbuffer.cpp
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
#include "rd3_dvertexbuffer.h"

using namespace System;

namespace Rd3
{
//------------------------------------------------------------------
DynamicVertexBuffer::DynamicVertexBuffer( Render* owner, const sString& objectName, VertexBufferStream::Set vbset ):
	_BaseClass( owner, objectName, ResourceType::E_DVERTEX_BUFFER ),
	_vertexCount( 0 ),
	_vertexSize( 0 ),

	_maxVertexCount( 0 ),
	_currentVertex( -2 ),
	_vbset( vbset )
{
}


}
