/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_render.cpp
//  Created                 : 20 1 2011   0:05
//  File path               : SLibF\render3d\cpp
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
#include "rd3_render.h"
#include "rd3_msg.h"
#include "rd3_mesh.h"
#include "rd3_after_effect.h"
#include "rd3_xml_def.h"
#include "rd3_font.h"
#include "rd3_rstate.h"
#include "rd3_dvertexbuffer.h"
#include "rd3_animation.h"
#include "rd3_font_sprite.h"

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

//--------------------------------------------------------------------
extern void RegisterTypes();

//--------------------------------------------------------------------
Render* Render::CreateRender( const RenderCreateParams& params ) throws_error
{
	RegisterTypes();

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
            
        default:
            return NULL;
	}

	return NULL;
}

//--------------------------------------------------------------------
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
	_aftereffectResPool( ResourceType::E_AFTEREFFECT ),
	_animationResPool( ResourceType::E_ANIMATION ),
	_serviceResPool( ResourceType::E_SERVICE ),
	
	_defaultMaterialQuality( Quality::E_Low )
{
}

//--------------------------------------------------------------------
void Render::Initialize( Def& def, const StreamArchive& archive ) throws_error
{
	if( _pRenderState != NULL )
		_pRenderState->SetRenderTarget( NULL );
}

//--------------------------------------------------------------------
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
	
//--------------------------------------------------------------------
void Render::AddService( Service* pService )
{
	__S_ASSERT( pService != NULL );
	if( _serviceResPool[pService->GetObjectName()] )
	{
		error_throw_arg( Errors::StringError )
			_S("Service : ") + pService->GetObjectName() + _S(" is already registred.")
		);		
	}
	_serviceResPool.Add( pService );	
}
	
//--------------------------------------------------------------------
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

//--------------------------------------------------------------------
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

//--------------------------------------------------------------------
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
	
//--------------------------------------------------------------------
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
	
//--------------------------------------------------------------------
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

//--------------------------------------------------------------------
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

//--------------------------------------------------------------------
AfterEffect* Render::UseAfterEffect( const sString& eName ) throws_error
{
	AfterEffect* pEf = GetAfterEffect( eName );
	
	if( pEf == NULL )
	{
		error_throw_arg( Errors::StringError )
			_S("After Effect : ") + eName + _S(" not found.")
		);
		
	}
	return pEf;
}

//--------------------------------------------------------------------
Animation* Render::UseAnimation( const sString& eName ) throws_error
{
	Animation* pAnim = GetAnimation( eName );
	
	if( pAnim == NULL )
	{
		error_throw_arg( Errors::StringError )
			_S("Animation : ") + eName + _S(" not found.")
		);
		
	}
	return pAnim;
}

//--------------------------------------------------------------------
void Render::ProcessServces( EngineData& edata )
{
	for( sInt i = 0; i < _serviceResPool.GetObjectCount(); ++i )
	{
		ResourceObject* obj = _serviceResPool[i];
		if( obj )
		{
			reinterpret_cast<Service*>(obj)->Process( edata );
		}
	}
}
	
//--------------------------------------------------------------------
void Render::ProcessMessages( EngineData& edata )
{
	for( sInt i = 0; i < _messageQResPool.GetObjectCount(); ++i )
	{
		ResourceObject* obj = _messageQResPool[i];
		if( obj )
		{
			reinterpret_cast<MessageQueue*>(obj)->ProcessMessages( edata );
		}
	}
}
	
//--------------------------------------------------------------------
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
	
	case ResourceType::E_AFTEREFFECT:
		_aftereffectResPool.Remove( pRes->GetObjectName() );
		break;

	case ResourceType::E_MESSAGEQ:
		_messageQResPool.Remove( pRes->GetObjectName() );
		break;

	case ResourceType::E_ANIMATION:
		_animationResPool.Remove( pRes->GetObjectName() );
		break;

	case ResourceType::E_SERVICE:
		_serviceResPool.Remove( pRes->GetObjectName() );
		break;
			
	case ResourceType::E_MATERIAL:
	default:
		__S_ASSERT( sFalse );
	}
}
	
//--------------------------------------------------------------------
Render::~Render()
{
	sMap<VertexBufferStream::Set, DynamicVertexBuffer*>::Iterator i = _dynamicVertexBufferMap.Begin();
	while( i != _dynamicVertexBufferMap.End() )
	{
		delete i.Value();
		++i;
	}
}

//--------------------------------------------------------------------
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
	
//--------------------------------------------------------------------
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
	else if( streamSet == ( VertexBufferStream::E_XYZ | VertexBufferStream::E_NORMAL ) )
	{
		if( points.Size() != normals.Size() )
		{
			error_throw_arg( System::Errors::StringError ) 
				_S("Invalid file format :") + path 
			);
		}
		pVertexBuffer = CreateVertexBuffer( objectName, points, normals );		
	}
	else		
	{
		error_throw_arg( System::Errors::StringError ) 
			_S("Invalid vertex buffer stream :") + streamType + _S(" file: ") + path
		);
		
	}
	
	return pVertexBuffer;
}
	
//--------------------------------------------------------------------
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
	
//--------------------------------------------------------------------
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
	
//--------------------------------------------------------------------
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
	
	Mesh* pMesh = NULL;
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
	
//--------------------------------------------------------------------
AfterEffect* Render::CreateAfterEffectFromFile( 
										   const sString& objectName,
										   const sString& fileName,
										   const Def& def,
										   const StreamArchive& archive
										   )
{
	if( objectName.Length() > 0 && _aftereffectResPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);
	
	AfterEffect* pAfterEffect = NULL;
	try
	{
		pAfterEffect = new AfterEffect( this, objectName );
		pAfterEffect->LoadFromFile( fileName, def, archive );
		
		if( objectName.Length() > 0 )
			_aftereffectResPool.Add( pAfterEffect );
	}
	catch (...)
	{
		if( pAfterEffect )
			pAfterEffect->UnuseResource();
		throw;
	}
	
	return pAfterEffect;
}	

//--------------------------------------------------------------------
Animation* Render::CreateAnimationFromFile( 
		const sString& objectName,
		const sString& fileName,
		const Def& def,
		const StreamArchive& archive
	) throws_error
{
	if( objectName.Length() > 0 && _animationResPool[objectName] != NULL ) 
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);

	ptr_unique<const Streams::IInputStream> pStream( archive.Open( fileName ) );
	ptr_unique<Xml::DomDocument> pDocument( Xml::DomDocument::Read( &pStream() ) );
	
	const System::Xml::BaseDomNode& node = pDocument().GetRoot();

	Animation* pAnimation = new Animation( this, objectName );

	try
	{
		pAnimation->LoadFromXml( node, def );

		if( objectName.Length() > 0 )
			_animationResPool.Add( pAnimation );
	}
	catch(...)
	{
		if( pAnimation != NULL )
			pAnimation->UnuseResource();
		throw;
	}
	
	return pAnimation;
}

//--------------------------------------------------------------------
Animation* Render::CreateAnimation( const sString& objectName )
{
	if( objectName.Length() > 0 && _animationResPool[objectName] != NULL ) 
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);

	Animation* pAnimation = new Animation( this, objectName );
	
	if( objectName.Length() > 0 )
		_animationResPool.Add( pAnimation );
	
	return pAnimation;

}

//--------------------------------------------------------------------
Font* Render::CreateFontFromFile(
		const sString& objectName,
		const sString& fileName,
		const Def& def,
		const StreamArchive& archive
	) throws_error
{
	if( objectName.Length() > 0 && _fontResPool[objectName] != NULL ) 
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);

	Font* pFont = NULL;
	
	if( fileName.EndsWith( _S(".xml") ) )
		pFont = CreateFontFromXmlFile( objectName, fileName, def, archive );
	else if( fileName.EndsWith( _S(".fnt") ) )
		pFont = CreateFontFromFntFile( objectName, fileName, def, archive );
	else
	{
		error_throw_arg( System::Errors::StringError ) 
			_S("Unknown font file format :") + fileName 
		);		
	}
		
	if( pFont != NULL && objectName.Length() > 0 )
		_fontResPool.Add( pFont );
	
	return pFont;
}

//--------------------------------------------------------------------
Font* Render::CreateFontFromFntFile(
	const sString& objectName,
	const sString& fileName,
	const Def& def,
	const StreamArchive& archive
	) throws_error
{
	FontSprite* pFont = new FontSprite( this, objectName );
	
	try 
	{
		pFont->LoadFromFntFile( fileName, def, archive );
	}
	catch (...) 
	{
		if( pFont )
			pFont->UnuseResource();
		throw;
	}
	
	return pFont;
}
	
//--------------------------------------------------------------------
Font* Render::CreateFontFromXmlFile(
		const sString& objectName,
		const sString& fileName,
		const Def& def,
		const StreamArchive& archive
	) throws_error
{	
	ptr_unique<const Streams::IInputStream> pStream( archive.Open( fileName ) );
	ptr_unique<Xml::DomDocument> pDocument( Xml::DomDocument::Read( &pStream() ) );
	
	const System::Xml::BaseDomNode& node = pDocument().GetRoot();

	sString type = node.GetAttributes()[ATTR_TYPE];

	Font* pFont = Font::Create( type, this, objectName );

	if( pFont == NULL )
	{
		error_throw_arg( System::Errors::StringError ) 
			_S("Invalid font type :") + type 
		);
	}

	try
	{
		pFont->LoadFromXml( node, def );
	}
	catch (...)
	{
		 if( pFont )
			 pFont->UnuseResource();
		throw;
	}
	
	return pFont;
}

}
