/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_primitive_torus.h
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

#ifndef _RD3_PRIMITIVE_TORUS_INC_
#define _RD3_PRIMITIVE_TORUS_INC_

#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_primitive.h"

namespace Rd3
{
	
/**
 * PrimitiveTorus
 * 
 */
class PrimitiveTorus : public Primitive3D
{
public:
	
	/**
	 *
	 */
	PrimitiveTorus() {}
	
	/**
	 *
	 */
	PrimitiveTorus( d3Float radius, d3Float tubeRadius, sInt ns, sInt nt );
	
	/**
	 *
	 */
	virtual void GetMesh( VertexPList& p, IndexList& i, VertexNList& n, VertexTxCoord& t ) const throws_error;
	
	virtual sInt EstimateVertexCount() const;
	
	virtual sInt EstimateIndexCount() const;
	
	virtual void LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error;	
private:
	sFloat	_radius;
	sFloat	_tubeRadius;
	sInt	_ns;
	sInt	_nt;
};
	
}

#endif // _RD3_PRIMITIVE_TORUS_INC_