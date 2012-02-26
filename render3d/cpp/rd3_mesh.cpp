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
		
		if( child.GetName() == ELEMENT_PRIMITIVE )
		{
			sString type = child.GetAttributes()[ATTR_TYPE];
			ptr_unique<Primitive3D> primitive( Primitive3D::Create( type ) );
			
			if( primitive.IsNull() )
				error_throw_arg( Errors::StringError )
					_S("Unknown primitive type: ") + type 
				);
			
			primitive().LoadFromXml( child, def, archive );
			SetPrimitiveMesh( primitive() );
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
	
	if( _material == NULL )
		error_throw_arg( Errors::StringError )
			_S("Missing material in mesh: ") + GetObjectName() 
		);
	
	if( _vertexBuffer == NULL )
		error_throw_arg( Errors::StringError )
			_S("Missing vb in mesh: ") + GetObjectName() 
		);

	if( _indexBuffer == NULL )
		error_throw_arg( Errors::StringError )
			_S("Missing ib in mesh: ") + GetObjectName() 
		);	
}
	
}