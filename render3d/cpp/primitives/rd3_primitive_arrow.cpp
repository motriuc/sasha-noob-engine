/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_primitive_arrow.cpp
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
#include "rd3_primitive_arrow.h"

using namespace System;
using namespace System::d3Math;
using namespace System::d2Math;

namespace Rd3
{	
//------------------------------------------------------------------
PrimitiveArrow::PrimitiveArrow( d3Float radius, d3Float height, d3Float headHeight, d3Float headRadius, sInt ns, sInt nt ) :
	_radius( radius ),
	_height( height ),
	_headHeight( headHeight ),
	_headRadius( headRadius ),
	_ns( ns ),
	_nt( nt )
{
}

//------------------------------------------------------------------
void PrimitiveArrow::LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error
{
	_radius =		node.GetAttributes()[_S("radius")].ToFloat();
	_height =		node.GetAttributes()[_S("height")].ToFloat();
	_headHeight =	node.GetAttributes()[_S("head.height")].ToFloat();
	_headRadius =	node.GetAttributes()[_S("head.radius")].ToFloat();
	_ns =			node.GetAttributes()[_S("segments")].ToInt();
	_nt =			node.GetAttributes()[_S("tube.segments")].ToInt();
}
	
//------------------------------------------------------------------
void PrimitiveArrow::GetMesh( VertexPList& p, IndexList& i, VertexNList& n, VertexTxCoord& tx ) const throws_error
{
	d3Float totalHeight = _radius + _height + ( _headRadius - _radius );
	
	// bottom
	for( sInt s = 0; s <= _ns; s++)
	{
		p.Add( d3Vector( 0.0f, - _height / 2.0f, 0.0f ) );
		n.Add( d3Vector( 0.0f, -1.0f, 0.0f ) );
		tx.Add( d2Vector( 1.0f * s / _ns, 1.0f ) );		
	}
	
	d3Float vOffset = _radius;
	d3Float headStart = _height - _headHeight;
	
	// middle
	for ( sInt t = 0; t <= _nt; t++)
	{
		for( sInt s = 0; s <= _ns; s++)
		{
			d3Float theta = s * FMath::f2Pi / _ns;
			d3Float sinTheta = FMath::Sin( theta );
			d3Float cosTheta = FMath::Cos( theta );
		
			p.Add( d3Vector( 
				_radius * sinTheta,
				-( _height / 2.0f ) + ( t * headStart / _nt ),
				_radius * cosTheta
			));
			
			n.Add( d3Vector( sinTheta, 0.0f, cosTheta ) );
			
			tx.Add( d2Vector( 
				1.0f * s / _ns,
				1.0f - ( vOffset + t * headStart / _nt ) / totalHeight
			));
		}
	}
	
	// head
	for( sInt s = 0; s <= _ns; s++)
	{
		d3Float theta = s * FMath::f2Pi / _ns;
		d3Float sinTheta = FMath::Sin( theta );
		d3Float cosTheta = FMath::Cos( theta );

		p.Add( d3Vector( 
			_headRadius * sinTheta,
			_height / 2.0f - _headHeight,
			_headRadius * cosTheta
		));
		
		n.Add( d3Vector( sinTheta, 0.0f, cosTheta ) );
		
		tx.Add( d2Vector(
			1.0f * s / _ns,
			0.0f
		));
	}
	
	// top
	for( sInt s = 0; s <= _ns; s++) 
	{
		p.Add( d3Vector( 0.0f, _height / 2.0f, 0.0f ) );
		n.Add( d3Vector( 0.0f, 1.0f, 0.0f ) );
		
		tx.Add( d2Vector( 
			1.0f * s / _ns, 
			1.0f - (headStart + _headRadius / totalHeight)
		));
		
	}
	
	sInt totalNT = _nt + 3;
	
	for( sInt t = 0; t < totalNT; t++ )
	{
		for( sInt s = 0; s < _ns; s++ )
		{
			sInt first = (t * (_ns + 1)) + s;
			sInt second = first + (_ns + 1);
			sInt third = first + 1;
			sInt fourth = second + 1;
			
			i.Add( first, third, second );
			i.Add( second, third, fourth );			
		}
	}
}

//------------------------------------------------------------------	
sInt PrimitiveArrow::EstimateVertexCount() const
{
	return ( _nt + 4 ) * ( _ns + 1 );
}
	
//------------------------------------------------------------------	
sInt PrimitiveArrow::EstimateIndexCount() const
{
	return (_nt + 3) * _ns * 6;
}
	
	
}