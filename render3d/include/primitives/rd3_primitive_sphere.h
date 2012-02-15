/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_primitive_sphere.h
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

#ifndef _RD3_PRIMITIVE_SPHERE_INC_
#define _RD3_PRIMITIVE_SPHERE_INC_

#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_primitive.h"

namespace Rd3
{
	
/**
 * PrimitiveSphere
 * 
 * Constructs a 3-dimensional sphere
 */
class PrimitiveSphere : public Primitive3D
{
public:
	/**
	 *
	 */
	PrimitiveSphere( d3Float radius, sInt nLongSeg, sInt nLatSeg );
	
	/**
	 *
	 */
	virtual void GetMesh( VertexPList& p, IndexList& i, VertexNList& n, VertexTxCoord& t ) const;
	
	virtual sInt EstimateVertexCount() const;
	
	virtual sInt EstimateIndexCount() const;
	
private:
	d3Float		_radius;
	sInt		_nLongSeg;
	sInt		_nLatSeg;
};
	
}

#endif // _RD3_PRIMITIVE_SPHERE_INC_