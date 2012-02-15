/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_primitive.h
//	Created                 : 5 2 2012   0:05
//	File path               : SLibF\render3d\include\primitives
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

#ifndef _RD3_PRIMITIVE_INC_
#define _RD3_PRIMITIVE_INC_

#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

namespace Rd3
{

/**
 * Primitive3D
 */
class Primitive3D
{
public:
	/**
	 *
	 */
	virtual void GetMesh( VertexPList& p, IndexList& i, VertexNList& n, VertexTxCoord& t ) const = 0;
	
	/**
	 *
	 */
	virtual sInt EstimateVertexCount() const = 0;
	
	/**
	 *
	 */
	virtual sInt EstimateIndexCount() const = 0;
};
	
}

#endif // _RD3_PRIMITIVE_INC_