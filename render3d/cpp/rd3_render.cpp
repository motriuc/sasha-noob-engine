/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_render.cpp
//	Created                 : 20 1 2011   0:05
//	File path               : SLibF\render3d\cpp
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
#include "rd3_render.h"
#include "rd3_msg.h"
#include "rd3_mesh.h"

using namespace System::Types;

#ifdef _SPL_WIN32
	#include "dx9/dx9_conf.h"
	#include "dx9/dx9_render.h"
#endif

#ifdef _SPL_MAC
	#include "eagl_conf.h"
	#include "eagl_render.h"
#endif

#include "rd3_create_rparam.h"

namespace Rd3
{

/************************************************************************/
/*                                                                      */
/************************************************************************/
Render* Render::CreateRender( const RenderCreateParams& params ) throws_error
{
	switch( params.GetRenderType() )
	{
#ifdef _SPL_WIN32			
	case RenderType::E_DX9:
		return Dx9Render::Create( static_cast<const DX9RenderCreateParams&>( params ) );
#endif
			
#ifdef _SPL_MAC
	case RenderType::E_EAGL:
		return EAGLRender::Create( static_cast<const EAGLRenderCreateParams&>( params ) );
#endif
	}

	return NULL;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
Render::Render( const RenderType::RenderType type ) :
	_renderType( type ),
	_pRenderState( NULL ),
	_effectResPool( ResourceType::E_EFFECT ),
	_textureResPool( ResourceType::E_TEXTURE ),
	_vertexBufferPool( ResourceType::E_VERTEX_BUFFER ),
	_indexBufferPool( ResourceType::E_INDEX_BUFFER ),
	_fontResPool( ResourceType::E_FONT ),
	_messageQResPool( ResourceType::E_MESSAGEQ ),
	_meshResPool( ResourceType::E_MESH ),
	_pRenderTexture( NULL )
{
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void Render::AddMessageQueue( MessageQueue* pMsgQ )
{
	__S_ASSERT( pMsgQ != NULL );
	if( _messageQResPool[pMsgQ->GetObjectName()] )
	{
		error_throw_arg( Errors::StringError )
			_S("Message Queue : ") + pMsgQ->GetObjectName() + _S(" is already registred.")
		);		
	}
	_messageQResPool.Add( pMsgQ );
}
	
/************************************************************************/
/*                                                                      */
/************************************************************************/
Effect* Render::UseEffect( const sString& effectName ) throws_error
{
	Effect* pEffect = GetEffect( effectName );
	
	if ( pEffect == NULL ) {
		error_throw_arg( Errors::StringError )
			_S("Effect : ") + effectName + _S(" not found.")
		);
	}
	return pEffect;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
Font* Render::UseFont( const sString& fontName ) throws_error
{
	Font* pFont = GetFont( fontName );
	
	if ( pFont == NULL ) {
		error_throw_arg( Errors::StringError )
			_S("Font : ") + fontName + _S(" not found.")
		);
	}
	return pFont;	
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
Texture* Render::UseTexture( const sString& textureName ) throws_error
{
	Texture* pTexture = GetTexture( textureName );
	
	if ( pTexture == NULL ) {
		error_throw_arg( Errors::StringError )
			_S("Texture : ") + textureName + _S(" not found.")
		);
	}
	return pTexture;	
}
	
/************************************************************************/
/*                                                                      */
/************************************************************************/
Mesh* Render::UseMesh( const sString& meshName ) throws_error
{
	Mesh* pMesh = GetMesh( meshName );
	
	if ( pMesh == NULL ) {
		error_throw_arg( Errors::StringError )
			_S("Mesh : ") + meshName + _S(" not found.")
		);
	}
	return pMesh;
}
	
/************************************************************************/
/*                                                                      */
/************************************************************************/
VertexBuffer* Render::UseVb( const sString& vbName ) throws_error
{
	VertexBuffer* pVb = GetVb( vbName );
	
	if ( pVb == NULL ) 
	{
		error_throw_arg( Errors::StringError )
			_S("Vb : ") + vbName + _S(" not found.")
		);
	}
	return pVb;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
IndexBuffer* Render::UseIb( const sString& ibName ) throws_error
{
	IndexBuffer* pIb = GetIb( ibName );
	
	if ( pIb == NULL ) 
	{
		error_throw_arg( Errors::StringError )
			_S("Ib : ") + ibName + _S(" not found.")
		);
	}
	return pIb;
}
	
/************************************************************************/
/*                                                                      */
/************************************************************************/
void Render::NotifyFreeResource( ResourceObject* pRes )
{
	if( pRes->GetObjectName().Length() <= 0 )
		return;
	
	switch( pRes->GetResourceType() ) 
	{
	case ResourceType::E_VERTEX_BUFFER:
		_vertexBufferPool.Remove( pRes->GetObjectName() );
		break;	
		
	case ResourceType::E_INDEX_BUFFER:
		_indexBufferPool.Remove( pRes->GetObjectName() );
		break;
			
	case ResourceType::E_TEXTURE:
		_textureResPool.Remove( pRes->GetObjectName() );
		break;
			
	case ResourceType::E_EFFECT:
		_effectResPool.Remove( pRes->GetObjectName() );
		break;
		
	case ResourceType::E_FONT:
		_fontResPool.Remove( pRes->GetObjectName() );
		break;
			
	case ResourceType::E_MESH:
		_meshResPool.Remove( pRes->GetObjectName() );
		break;
			
	case ResourceType::E_MATERIAL:
	default:
		__S_ASSERT( sFalse );
	}
}
	
/************************************************************************/
/*                                                                      */
/************************************************************************/
Render::~Render()
{
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
VertexBuffer* Render::CreateVertexBufferFromFile(
												const sString& objectName,
												const sString& path,
												const StreamArchive& archive
												) throws_error
{
	if( path.EndsWith( _S(".vb") ) )
	   return CreateVertexBufferFromVBFile( objectName, path, archive );

	error_throw_arg( System::Errors::StringError ) 
	   _S("Unknown file vb type :") + path 
	);
	
	return NULL;
}
	
/************************************************************************/
/*                                                                      */
/************************************************************************/
VertexBuffer* Render::CreateVertexBufferFromVBFile(
												   const sString& objectName,
												   const sString& path,
												   const StreamArchive& archive ) throws_error
{
	ptr_unique<const Streams::IInputStream> pStream( archive.Open( path ) );
	Streams::TextReader reader( &pStream() );
	
	sString streamType;
	
	if( !reader.Read( streamType ) )
		error_throw_arg( System::Errors::StringError ) 
			_S("Invalid file format :") + path 
		);
	
	VertexBufferStream::Set streamSet =  VertexBufferStream::GetTypeSet( streamType );
	
	if( streamSet == VertexBufferStream::UNKNOWN )
		error_throw_arg( System::Errors::StringError ) 
			_S("Invalid vertex buffer stream set :") + streamSet 
		);
	
	VertexPList points;
	VertexNList normals;
	VertexTxCoord tx1;
	
	VertexBuffer* pVertexBuffer = NULL;
	
	for(;;)
	{
		if( streamSet & VertexBufferStream::E_XYZ )
		{
			d3Float x, y, z;
			
			if( !reader.Read( x ) || !reader.Read( y ) || !reader.Read( z ) )
				break;
		
			points.Add( d3Vector( x, y, z ) );
		}
		
		if( streamSet & VertexBufferStream::E_NORMAL )
		{
			d3Float x, y, z;
			
			if( !reader.Read( x ) || !reader.Read( y ) || !reader.Read( z ) )
				break;
			
			normals.Add( d3Vector( x, y, z ) );			
		}
		
		if( streamSet & VertexBufferStream::E_TX1 )
		{
			d3Float u, v;
			
			if( !reader.Read( u ) || !reader.Read( v ) )
				break;
			
			tx1.Add( d2Vector( u, v ) );						
		}
	}
	
	if( streamSet == ( VertexBufferStream::E_XYZ | VertexBufferStream::E_NORMAL | VertexBufferStream::E_TX1 ) )
	{
		if( points.Size() != normals.Size() || normals.Size() != tx1.Size() )
		{
			error_throw_arg( System::Errors::StringError ) 
				_S("Invalid file format :") + path 
			);
		}
		
		pVertexBuffer = CreateVertexBuffer( objectName, points, normals, tx1 );
	}
	else 
	{
		if( streamSet == VertexBufferStream::UNKNOWN )
			error_throw_arg( System::Errors::StringError ) 
				_S("Invalid vertex buffer stream :") + streamType + _S(" file: ") + path
			);
		
	}
	
	return pVertexBuffer;
}
	
/************************************************************************/
/*                                                                      */
/************************************************************************/		
IndexBuffer* Render::CreateIndexBufferFromFile(
												   const sString& objectName,
												   const sString& path,
												   const StreamArchive& archive
												   ) throws_error
{
	if( path.EndsWith( _S(".ib") ) )
		return CreateIndexBufferFromVBFile( objectName, path, archive );
	
	error_throw_arg( System::Errors::StringError ) 
		_S("Unknown file ib type :") + path 
	);
	
	return NULL;
}
	
/************************************************************************/
/*                                                                      */
/************************************************************************/	
IndexBuffer* Render::CreateIndexBufferFromVBFile( 
											 const sString& objectName,
											 const sString& path,
											 const StreamArchive& archive
											 ) throws_error
{
	ptr_unique<const Streams::IInputStream> pStream( archive.Open( path ) );	
	Streams::TextReader reader( &pStream() );
	
	IndexList indexBuffer;
	
	sInt i;	
	while( reader.Read( i ) ) 
	{
		indexBuffer.Add( i );
	}
	
	return CreateIndexBuffer( objectName, indexBuffer );
}
	
/************************************************************************/
/*                                                                      */
/************************************************************************/
Mesh* Render::CreateMeshFromFile( 
							 const sString& objectName,
							 const sString& fileName,
							 const Def& def,
							 const StreamArchive& archive
							 )
{
	if( objectName.Length() > 0 && _meshResPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);
	
	
	Rd3::Mesh* pMesh = NULL;
	try
	{
		pMesh = new Mesh( this, objectName );
		pMesh->LoadFromFile( fileName, def, archive );
		
		if( objectName.Length() > 0 )
			_meshResPool.Add( pMesh );
	}
	catch (...)
	{
		if( pMesh )
			pMesh->UnuseResource();
		throw;
	}
	
	return pMesh;
}	
	
}

