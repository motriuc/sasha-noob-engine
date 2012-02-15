/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_utils.h
//	Created                 : 30 1 2011   17:53
//	File path               : SLibF\render3d\include
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

#ifndef _RD3_UTILS_H_
#define _RD3_UTILS_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

namespace Rd3 
{ 
/**
 * forward declarations
 */
class VertexBuffer;
class Render;


namespace Utils
{

/**
 *
 */
namespace Debug
{

/**
 *  
 */
VertexBuffer* CreateNormalsMesh(
	Render* pRender,
	const sString& name,
	d3Float size,
	const VertexBuffer* vertexBuffer
) throws_error;

}


}

}

#endif // _RD3_UTILS_H_