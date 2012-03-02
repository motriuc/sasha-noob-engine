/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_primitive_sphere.h
//  Created                 : 5 2 2012   0:05
//  File path               : SLibF\render3d\include\primitives
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
#include "rd3_primitive_sphere.h"

using namespace System;
using namespace System::d3Math;
using namespace System::d2Math;

namespace Rd3
{	
//------------------------------------------------------------------
PrimitiveSphere::PrimitiveSphere( d3Float radius, sInt nLongSeg, sInt nLatSeg ) :
	_radius( radius ),
	_nLongSeg( nLongSeg ),
	_nLatSeg( nLatSeg )
{
}
//------------------------------------------------------------------
void PrimitiveSphere::LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error
{
	_radius =		node.GetAttributes()[_S("radius")].ToFloat();
	_nLongSeg =		node.GetAttributes()[_S("longitudinal.segments")].ToInt();
	_nLatSeg =		node.GetAttributes()[_S("latitudinal.segments")].ToInt();
}
	
//------------------------------------------------------------------
void PrimitiveSphere::GetMesh( VertexPList& p, IndexList& i, VertexNList& n, VertexTxCoord& t ) const throws_error
{
	for( sInt lat = 0; lat <= _nLatSeg; ++lat )
	{
		for( sInt lng = 0; lng <= _nLongSeg; ++lng )
		{
			d3Float theta = lat * FMath::fPi / _nLatSeg;
			d3Float phi = lng * FMath::f2Pi / _nLongSeg;
			
			d3Float sinTheta = FMath::Sin( theta );
			
			d3Vector v( 
				sinTheta * FMath::Cos( phi ),
				FMath::Cos( theta ),
				sinTheta * FMath::Sin( phi )
			);
			
			n.Add( v );
			
			v *= _radius;
			
			p.Add( v );
			
			d2Vector tx(
				1.0f - ( 1.0f * lng / _nLongSeg ),
				1.0f * lat / _nLatSeg
			);
			
			t.Add( tx );
		}
	}
	
	for( sInt lat = 0; lat < _nLatSeg; ++lat )
	{
		for( sInt lng = 0; lng < _nLongSeg; ++lng )
		{
			sInt i1 = lat * ( _nLongSeg + 1 ) + lng;
			sInt i3 = i1 + 1;
			sInt i2 = i3 + _nLongSeg;
			sInt i4 = i2 + 1;
			
			i.Add( i1, i3, i2 );
			i.Add( i2, i3, i4 );
		}
	}
}
	
//------------------------------------------------------------------	
sInt PrimitiveSphere::EstimateVertexCount() const
{
	return ( _nLatSeg + 1 ) * ( _nLongSeg + 1 );
}
	
//------------------------------------------------------------------	
sInt PrimitiveSphere::EstimateIndexCount() const
{
	return _nLatSeg * _nLongSeg * 6;
}
	
	
}