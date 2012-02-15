/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_utils.cpp
//	Created                 : 30 1 2011   17:53
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
#include "rd3_utils.h"
#include "rd3_vertexbuffer.h"
#include "rd3_render.h"

namespace Rd3
{
namespace Utils
{
namespace Debug
{
/**
 *
 */
VertexBuffer* CreateNormalsMesh( Render* pRender, const sString& name, d3Float normalSize, const VertexBuffer* vertexBuffer ) throws_error
{
	__S_ASSERT( pRender != NULL );
	__S_ASSERT( vertexBuffer != NULL );

	VertexPList points;
	VertexNList normals;

	vertexBuffer->GetNormals( normals );

	if( normals.Size() <= 0 )
		return NULL;

	vertexBuffer->GetPoints( points );

	if( points.Size() <= 0 )
		return NULL;

	__S_ASSERT( points.Size() == normals.Size() );
	
	VertexPList normalM;
	normalM.Reserve( 2* points.Size() );

	for( sInt i = 0; i < points.Size(); i++ )
	{
		normalM.Add( points[i] );
		normalM.Add( points[i] + normals[i].UnitVector() * normalSize );
	}

	return pRender->CreateVertexBuffer( name, normalM );
}


}
}
}