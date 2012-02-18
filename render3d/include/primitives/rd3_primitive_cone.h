/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_primitive_cone.h
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

#ifndef _RD3_PRIMITIVE_CONE_INC_
#define _RD3_PRIMITIVE_CONE_INC

#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_primitive.h"

namespace Rd3
{
	
/**
 * PrimitiveCone
 * 
 */
class PrimitiveCone : public Primitive3D
{
public:
	PrimitiveCone() {}
	
	/**
	 *
	 */
	PrimitiveCone( d3Float height, d3Float topRadius, d3Float bottomRadius, sBool openEnded, sInt ns, sInt nt );
	
	/**
	 *
	 */
	virtual void GetMesh( VertexPList& p, IndexList& i, VertexNList& n, VertexTxCoord& t ) const throws_error;
	
	virtual sInt EstimateVertexCount() const;
	
	virtual sInt EstimateIndexCount() const;
	
	virtual void LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error;
	
private:
	d3Float		_height;
	d3Float		_topRadius;
	d3Float		_bottomRadius;
	sInt		_ns;
	sInt		_nt;
	sBool		_openEnded;
	
};
	
}

#endif // _RD3_PRIMITIVE_CONE_INC