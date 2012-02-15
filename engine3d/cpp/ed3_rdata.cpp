/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_rdata.cpp
//  Created             : 20 1 2012
//  Author              : Motriuc Alexandru
//  File Path           : SLibF\engine3d\include
//  System independent  : 0%
//  Library             : 
//
//  Purpose:
//    
//
/////////////////////////////////////////////////////////////////////
//  Modification History :
//
/////////////////////////////////////////////////////////////////////
#include "ed3afx.h"
#include "ed3_rdata.h"

namespace Ed3 
{
//-------------------------------------------------------------------
d3RenderData::d3RenderData( Rd3::RenderState* renderState, const d3ObjectClass& renderObjectClass ):
	_renderState( renderState ),
	_renderObjectsClass( renderObjectClass )
{
	__S_ASSERT( _renderState != NULL );
}

}