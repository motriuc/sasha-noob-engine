/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_primitive_cone.cpp
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

#include "rd3afx.h"
#include "rd3_primitive_cone.h"

using namespace System;
using namespace System::d3Math;
using namespace System::d2Math;

namespace Rd3
{
//------------------------------------------------------------------	
	
AUTO_REGISTER_PRIMITIVE_FACTORY( _S("cone"), PrimitiveCone )
	
//------------------------------------------------------------------
PrimitiveCone::PrimitiveCone( d3Float height, d3Float topRadius, d3Float bottomRadius, sBool openEnded, sInt ns, sInt nt ) :
	_height( height ),
	_topRadius( topRadius ),
	_bottomRadius( bottomRadius ),
	_ns( ns ),
	_nt( nt ),
	_openEnded( openEnded )
{
}

//------------------------------------------------------------------
void PrimitiveCone::LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error
{
	_height =		node.GetAttributes()[_S("height")].ToFloat();
	_topRadius =	node.GetAttributes()[_S("top.radius")].ToFloat();
	_bottomRadius = node.GetAttributes()[_S("bottom.radius")].ToFloat();
	
	_openEnded = sFalse;
	if( node.GetAttributes()[_S("openended")] == _S("true") )
		_openEnded = sTrue;
	
	_ns = node.GetAttributes()[_S("segments")].ToInt();
	_nt = node.GetAttributes()[_S("tube.segments")].ToInt();
}	
	
//------------------------------------------------------------------
void PrimitiveCone::GetMesh( VertexPList& p, IndexList& i, VertexNList& n, VertexTxCoord& tx ) const throws_error
{
	d3Float totalHeight;
	
	if( _openEnded )
	{
		totalHeight = _height;
	}
	else
	{
		totalHeight = _bottomRadius + _height + _topRadius;
	}
	
	d3Float dR = _bottomRadius - _topRadius;
	d3Float length = FMath::Sqrt( _height * _height + dR * dR );
	
	if( !_openEnded)
	{
		for( sInt s = 0; s <= _ns; s++)
		{
			p.Add( d3Vector( 0.0f, -_height / 2.0f, 0.0f ) );
			n.Add( d3Vector( 0.0f, -1.0f, 0.0 ) );
			
			tx.Add( d2Vector( 
				1.0f * s / _ns,
				1.0f
			));
		}
	}
	
	d3Float vOffset;
	
	if( _openEnded )
	{
		vOffset = 0;
	}
	else
	{
		vOffset = _bottomRadius;
	}
	
	for( sInt t = 0; t <= _nt; t++)
	{
		d3Float radius = _bottomRadius - (_bottomRadius - _topRadius) * t / _nt;
		
		for( sInt s = 0; s <= _ns; s++ ) 
		{
			d3Float theta = s * FMath::f2Pi / _ns;
			d3Float sinTheta = FMath::Sin( theta );
			d3Float cosTheta = FMath::Cos( theta );
			
			p.Add( d3Vector( 
				radius * sinTheta,
				-(_height / 2.0f) + (t * _height / _nt),
				radius * cosTheta
			));
			
			n.Add( d3Vector(
				sinTheta * _height / length,
				dR / length,
				cosTheta * _height / length
			));
			
			tx.Add( d2Vector( 
				1.0f * s / _ns,
				1.0f - (vOffset + t * _height / _nt) / totalHeight
			));
		}
	}
	
	if( !_openEnded )
	{
		for (sInt s = 0; s <= _ns; s++)
		{
			p.Add( d3Vector( 0.0f, _height / 2.0f, 0.0f ) );
			n.Add( d3Vector( 0.0f, 1.0f, 0.0f ) );
			
			tx.Add( d2Vector(
				1.0f * s / _ns,
				0.0f
			));
		}
	}
	
	sInt totalNT;
	
	if( _openEnded )
	{
		totalNT = _nt;
	}
	else
	{
		totalNT = _nt + 2;
	}
	
	for( sInt t = 0; t < totalNT; t++)
	{
		for( sInt s = 0; s < _ns; s++)
		{
			sInt first = ( t * (_ns + 1) ) + s;
			sInt second = first + ( _ns + 1 );
			sInt third = first + 1;
			sInt fourth = second + 1;
			
			i.Add( first, third, second );
			i.Add( second, third, fourth );
		}
	}
	
}
	
//------------------------------------------------------------------	
sInt PrimitiveCone::EstimateVertexCount() const
{
	sInt c = ( _nt + 1 ) * ( _ns + 1 );
	
	if( !_openEnded )
	{
		c += 2 * ( _ns + 1 );
	}
	
	return c;
}
	
//------------------------------------------------------------------	
sInt PrimitiveCone::EstimateIndexCount() const
{
	return _ns * _nt * 6;
}
	
	
}