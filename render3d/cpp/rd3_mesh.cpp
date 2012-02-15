/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_mesh.cpp
//	Created                 : 5 2 2012   21:56
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
#include "rd3afx.h"
#include "rd3_mesh.h"
#include "rd3_render.h"
#include "rd3_xml_def.h"
#include "rd3_primitive.h"
#include "rd3_primitive_sphere.h"
#include "rd3_primitive_torus.h"
#include "rd3_primitive_arrow.h"
#include "rd3_primitive_cone.h"

namespace Rd3
{
	
//-------------------------------------------------------------------	
Mesh::Mesh( Render* owner, const sString& objectName ) :
	_BaseClass( owner, objectName, ResourceType::E_MESH ),
	_type( PrimitiveType::E_TRIANGLE_LIST )
{
}

//-------------------------------------------------------------------	
void Mesh::SetPrimitiveMesh( const Primitive3D& primitive )
{
	_vertexBuffer.ResourceFree();
	_indexBuffer.ResourceFree();
	
	VertexPList points;
	IndexList index;
	VertexNList normals;
	VertexTxCoord tx;
	primitive.GetMesh( points, index, normals, tx );
		
	_vertexBuffer = GetOwner()->CreateVertexBuffer( _S(""), points, normals, tx );
	_indexBuffer = GetOwner()->CreateIndexBuffer( _S(""), index );
}	

//-------------------------------------------------------------------	
void Mesh::SetVb( const sString& name )
{
	_vertexBuffer = GetOwner()->UseVb( name );
}
	
//-------------------------------------------------------------------	
void Mesh::SetIb( const sString& name )
{
	_indexBuffer = GetOwner()->UseIb( name );
}		
//-------------------------------------------------------------------	
void Mesh::LoadFromFile( const sString& path, const Def& def, const Streams::StreamArchive& archive ) throws_error
{
	ptr_unique<const Streams::IInputStream> pStream( archive.Open( path ) );
	
	ptr_unique<Xml::DomDocument> pDocument( Xml::DomDocument::Read( &pStream() ) );
	
	LoadFromXml( pDocument().GetRoot(), def, archive );	
}
	
//-------------------------------------------------------------------	
void Mesh::LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error
{
	for( sInt i = 0; i < node.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& child = node[i];
		
		if( !XmlCheckDef( child, def ) )
			continue;
		
		if( child.GetName() == _S("sphere") )
		{
			d3Float radius = child.GetAttributes()[_S("radius")].ToFloat();
			sInt longSeg = child.GetAttributes()[_S("longitudinal.segments")].ToInt();
			sInt latSeg = child.GetAttributes()[_S("latitudinal.segments")].ToInt();
			
			PrimitiveSphere prim( radius, longSeg, latSeg );
			SetPrimitiveMesh( prim );
		}
		else if( child.GetName() == _S("torus") )
		{
			d3Float radius = child.GetAttributes()[_S("radius")].ToFloat();
			d3Float tubeRadius = child.GetAttributes()[_S("tube.radius")].ToFloat();
			
			sInt ns = child.GetAttributes()[_S("segments")].ToInt();
			sInt nt = child.GetAttributes()[_S("tube.segments")].ToInt();
						
			PrimitiveTorus prim( radius, tubeRadius, ns, nt );
			SetPrimitiveMesh( prim );
		}
		else if( child.GetName() == _S("arrow") )
		{
			d3Float radius = child.GetAttributes()[_S("radius")].ToFloat();
			d3Float height = child.GetAttributes()[_S("height")].ToFloat();
			d3Float headHeight = child.GetAttributes()[_S("head.height")].ToFloat();
			d3Float headRadius = child.GetAttributes()[_S("head.radius")].ToFloat();
			sInt ns = child.GetAttributes()[_S("segments")].ToInt();
			sInt nt = child.GetAttributes()[_S("tube.segments")].ToInt();
			
			PrimitiveArrow prim( radius, height, headHeight, headRadius, ns, nt );
			SetPrimitiveMesh( prim );
		}
		else if( child.GetName() == _S("cone") )
		{
			d3Float height = child.GetAttributes()[_S("height")].ToFloat();
			d3Float topRadius = child.GetAttributes()[_S("top.radius")].ToFloat();
			d3Float bottomRadius = child.GetAttributes()[_S("bottom.radius")].ToFloat();
			
			sBool openEnded = sFalse;
			if( child.GetAttributes()[_S("openended")] == _S("true") )
				openEnded = sTrue;
			
			sInt ns = child.GetAttributes()[_S("segments")].ToInt();
			sInt nt = child.GetAttributes()[_S("tube.segments")].ToInt();
		
			PrimitiveCone prim( height, topRadius, bottomRadius, openEnded, ns, nt );
			SetPrimitiveMesh( prim );
		}
		else if( child.GetName() == ELEMENT_MATERIAL )
		{
			sString type = child.GetAttributes()[ATTR_TYPE];
			
			Material* pMaterial = Material::Create( type, GetOwner(), _S("") );
			if( pMaterial )
			{
				_material.ResourceCreate( pMaterial );
				_material().LoadFromXml( child, def );
			}
		}
		else if( child.GetName() == ELEMENT_VBUFFER )
		{
			SetVb( child.GetAttributes()[ATTR_NAME] );
		}
		else if( child.GetName() == ELEMENT_IBUFFER )
		{
			SetIb( child.GetAttributes()[ATTR_NAME] );			
		}
	}
}
	
}