/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_render.cpp
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

#include "eagl_conf.h"
#include "eagl_render.h"
#include "eagl_effect.h"
#include "eagl_vertexbuffer.h"
#include "eagl_indexbuffer.h"
#include "eagl_rstate.h"
#include "eagl_texture.h"
#include "eagl_font_sprite.h"

#include "platform_eagl_context.h"

#include "rd3_create_rparam.h"
#include "rd3_def.h"

using namespace System::Streams;
using namespace System;

////////////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------
Rd3::Render* EAGLRender::Create( const Rd3::EAGLRenderCreateParams& param ) throws_error
{
	EAGLRenderContext* context = EAGLRenderContext_Create();
	
	if (context == NULL) {
		error_throw_arg( System::Errors::StringError)
			_S("Can't create EAGL render context")
		);
	}

	EAGLRender* pRender = new EAGLRender();

	pRender->_renderContext = context;
	pRender->_params = param.GetParams();

	return pRender;
}

//-------------------------------------------------------------------------------------
void EAGLRender::InitSystemResources( Rd3::Def& def, const Streams::StreamArchive& archive ) throws_error
{
	// default effect for the font rendering
	CreateEffectFromFile( _S("system.font.fx.1"),  def, _S("%engine%/system.font.fx.1.xml"), archive );
	CreateEffectFromFile( _S("system.flatcolor.fx.1"), def, _S("%engine%/system.flatcolor.1.xml"), archive );
	CreateEffectFromFile( _S("system.flatcolor.fx.2"), def, _S("%engine%/system.flatcolor.2.xml"), archive );
	CreateEffectFromFile( _S("system.texture.fx.1"), def, _S("%engine%/system.texture.ps.1.xml"), archive );
	
	// affter effects
	CreateEffectFromFile( _S("system.after.effect.none"), def, _S( "%engine%/system.after.effect.none.fx.xml"), archive );
	CreateEffectFromFile( _S("system.after.effect.blur"), def, _S( "%engine%/system.after.effect.blur.fx.xml"), archive );
	CreateEffectFromFile( _S("system.after.effect.color"), def, _S( "%engine%/system.after.effect.color.fx.xml"), archive ); 
	
	// std effect
	CreateEffectFromFile( _S("system.solid.fx.1"), def, _S("%engine%/system.solid.fx.1.xml"), archive );
	
	// system font default
	CreateFontSystem( _S("system.font.default"), _S("Baskerville"), 26 );
}

//-------------------------------------------------------------------------------------
void EAGLRender::Initialize( Rd3::Def& def, const StreamArchive& archive ) throws_error
{
	InitCreateFrameBuffers( def );
	InitSystemResources( def, archive );
}

//-------------------------------------------------------------------------------------
void EAGLRender::InitCreateFrameBuffers( Rd3::Def& def )
{
	EAGLRenderContext_SetCurrent( _renderContext ); 
	
	// Create default framebuffer object.
	glGenFramebuffers( 1, &_defaultFramebuffer );
	glBindFramebuffer( GL_FRAMEBUFFER, _defaultFramebuffer );
	
	// Create color render buffer and allocate backing store.
	glGenRenderbuffers( 1, &_colorRenderbuffer );
	glBindRenderbuffer( GL_RENDERBUFFER, _colorRenderbuffer );
	
	EAGLRenderContext_RenderbufferStorage( _renderContext, GL_RENDERBUFFER, _params._view );

	glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &_framebufferWidth );
	glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &_framebufferHeight );
	
	glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderbuffer );
	
	// depth buffer
	glGenRenderbuffers( 1, &_depthRenderbuffer );
	glBindRenderbuffer( GL_RENDERBUFFER, _depthRenderbuffer );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, _framebufferWidth, _framebufferHeight );
	glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderbuffer );
	
	// stencil buffer
	glGenRenderbuffers( 1, &_stencilRenderbuffer );
	glBindRenderbuffer( GL_RENDERBUFFER, _stencilRenderbuffer );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_STENCIL_INDEX8, _framebufferWidth, _framebufferHeight );
	glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _stencilRenderbuffer );
	
	if( glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE )
	{
		Platform::ShowError( _S("Frame buffer invalid status") );
	}

	_renderTargetSizeInPixels.x = _framebufferWidth;
	_renderTargetSizeInPixels.y = _framebufferHeight;
}

//-------------------------------------------------------------------------------------
void EAGLRender::EaglSetRenderTarget( EAGLTexture* pTexture )
{
	if( pTexture == NULL )
	{
		glFramebufferRenderbuffer( 
			GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0, 
			GL_RENDERBUFFER, 
			_colorRenderbuffer
		);		
	}
	else
	{
		glFramebufferTexture2D( 
			GL_FRAMEBUFFER, 
			GL_COLOR_ATTACHMENT0, 
			GL_TEXTURE_2D, 
			((EAGLTexture*)pTexture)->GetHandle(), 
			0
		);
	}

	if( glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE )
	{
		Platform::ShowError( _S("Frame buffer invalid status") );
	}
}


//-------------------------------------------------------------------------------------
void EAGLRender::FreeFrameBuffers()
{
	EAGLRenderContext_SetCurrent( _renderContext ); 
	
	if (_defaultFramebuffer)
	{
		glDeleteFramebuffers(1, &_defaultFramebuffer);
		_defaultFramebuffer = 0;
	}
	
	if (_colorRenderbuffer)
	{
		glDeleteRenderbuffers(1, &_colorRenderbuffer);
		_colorRenderbuffer = 0;
	}
}

//-------------------------------------------------------------------------------------
EAGLRender::~EAGLRender()
{
	delete _pRenderState;
	
	FreeFrameBuffers();
	EAGLRenderContext_Free( _renderContext );
}

//-------------------------------------------------------------------------------------
EAGLRender::EAGLRender() :
	_BaseClass( Rd3::RenderType::E_EAGL ),
	_defaultFramebuffer( 0 ),
	_colorRenderbuffer( 0 ),
	_depthRenderbuffer( 0 ),
	_stencilRenderbuffer( 0 )
{
	_pRenderState = new EAGLRenderState( this );
}

//-------------------------------------------------------------------------------------
Rd3::Effect* EAGLRender::CreateEffectFromString(
											const sString& objectName,
											const Rd3::Def& def,
											const sString& effectCode,
											const StreamArchive& archive
											   ) throws_error
{
	if( objectName.Length() > 0 && _effectResPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);
	
	EAGLEffect* effect = NULL;
	try
	{
		effect = new EAGLEffect( this, objectName );
		effect->LoadFromString( effectCode, def, archive );
		
		if( objectName.Length() > 0 )
			_effectResPool.Add( effect );
	}
	catch(...)
	{
		if( effect )
			effect->UnuseResource();
		
		throw;
	}
	
	return effect;
}

//-------------------------------------------------------------------------------------
Rd3::Effect* EAGLRender::CreateEffectFromFile(
										  const sString& objectName,
										  const Rd3::Def& def,
										  const sString& fileName,
										  const StreamArchive& archive
										  ) throws_error
{
	if( objectName.Length() > 0 && _effectResPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);
	
	EAGLEffect* effect = NULL;
	try
	{
		effect = new EAGLEffect( this, objectName );
		effect->LoadFromFile( fileName, def, archive );
		
		if( objectName.Length() > 0 )
			_effectResPool.Add( effect );
	}
	catch(...)
	{
		if( effect )
			effect->UnuseResource();
		throw;
	}
	
	return effect;
}

//-------------------------------------------------------------------------------------
Rd3::VertexBuffer* EAGLRender::CreateVertexBuffer(
											  const sString& objectName,
											  const Rd3::VertexPList& points
											  ) throws_error
{
	if( objectName.Length() > 0 && _vertexBufferPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);
	
	EAGLVertexBuffer* vb = NULL;
	try
	{
		vb = new EAGLVertexBuffer( this, objectName, points );
		
		if( objectName.Length() > 0 )
			_vertexBufferPool.Add( vb );
	}
	catch(...)
	{
		if (vb)
			vb->UnuseResource();
	
		throw;
	}
	
	return vb;
}

//-------------------------------------------------------------------------------------
Rd3::VertexBuffer* EAGLRender::CreateVertexBuffer(
											  const sString& objectName,
											  const Rd3::VertexPList& points, 
											  const Rd3::VertexCList& diffuseColor
											  ) throws_error
{
	if( objectName.Length() > 0 && _vertexBufferPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);
	
	EAGLVertexBuffer* vb = NULL;
	try
	{
		vb = new EAGLVertexBuffer( this, objectName, points, diffuseColor );
		
		if( objectName.Length() > 0 )
			_vertexBufferPool.Add( vb );
	}
	catch(...)
	{
		if (vb)
			vb->UnuseResource();
		throw;
	}
	
	return vb;	
}

//-------------------------------------------------------------------------------------
Rd3::VertexBuffer* EAGLRender::CreateVertexBuffer(
											  const sString& objectName,
											  const Rd3::VertexPList& points,
											  const Rd3::VertexTxCoord& txCoord
											  ) throws_error
{
	if( objectName.Length() > 0 && _vertexBufferPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);
	
	EAGLVertexBuffer* vb = NULL;
	try
	{
		vb = new EAGLVertexBuffer( this, objectName, points, txCoord );
		
		if( objectName.Length() > 0 )
			_vertexBufferPool.Add( vb );
	}
	catch(...)
	{
		if (vb)
			vb->UnuseResource();
		throw;
	}
	
	return vb;		
}

//-------------------------------------------------------------------------------------
Rd3::VertexBuffer* EAGLRender::CreateVertexBuffer(
											  const sString& objectName,
											  const Rd3::VertexPList& points,
											  const Rd3::VertexNList& normals
											  ) throws_error
{
	if( objectName.Length() > 0 && _vertexBufferPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);
	
	EAGLVertexBuffer* vb = NULL;
	try
	{
		vb = new EAGLVertexBuffer( this, objectName, points, normals );
		
		if( objectName.Length() > 0 )
			_vertexBufferPool.Add( vb );
	}
	catch(...)
	{
		if (vb)
			vb->UnuseResource();
		throw;
	}
	
	return vb;		
}

//-------------------------------------------------------------------------------------
Rd3::Texture* EAGLRender::CreateTextureFromFile(
											const sString& objectName,
											const sString& fileName,
											const StreamArchive& archive,
											Rd3::TextureType::TextureType type,
											const Rd3::TextureParams& params
											) throws_error
{
	if( objectName.Length() > 0 && _textureResPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);

	
	EAGLTexture* pTexture = NULL;
	try
	{
		pTexture = new EAGLTexture( this, objectName, type, params );
		pTexture->LoadFromFile( fileName, archive );
		
		if( objectName.Length() > 0 )
			_textureResPool.Add( pTexture );
	}
	catch (...)
	{
		if( pTexture )
			pTexture->UnuseResource();
		throw;
	}
	
	return pTexture;
}

//-------------------------------------------------------------------------------------
Rd3::Texture* EAGLRender::EAGLCreateTexture( 
										 const sString& objectName,
										 GLuint textId, sInt width, sInt height,
										 Rd3::TextureType::TextureType type,
										 const Rd3::TextureParams& params
										)
{
	if( objectName.Length() > 0 && _textureResPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);
	
	
	EAGLTexture* pTexture = NULL;
	try
	{
		pTexture = new EAGLTexture( this, objectName, type, params );
		pTexture->SetHandle( textId, width, height );
		
		if( objectName.Length() > 0 )
			_textureResPool.Add( pTexture );
	}
	catch (...)
	{
		if( pTexture )
			pTexture->UnuseResource();
		throw;
	}
	
	return pTexture;	
}

//-------------------------------------------------------------------------------------
Rd3::Font* EAGLRender::CreateFontSystem(
									const sString& objectName,
									const sString& systemFontName,
									sInt fontSize
									) throws_error
{
	if( objectName.Length() > 0 && _fontResPool[objectName] != NULL ) 
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);
	
	EAGLFontSprite* pFont = NULL;
	
	try
	{
		pFont = new EAGLFontSprite( this, objectName );
		pFont->CreateFont( systemFontName, fontSize );
		
		if( objectName.Length() > 0 )
			_fontResPool.Add( pFont );
	}
	catch (...)
	{
		 if( pFont )
			 pFont->UnuseResource();
		throw;
	}
	
	return pFont;
}

//-------------------------------------------------------------------------------------
Rd3::IndexBuffer* EAGLRender::CreateIndexBuffer(
											const sString& objectName,
											const Rd3::IndexList& indexList
											) throws_error
{
	if( objectName.Length() > 0 && _indexBufferPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);
	
	EAGLIndexBuffer* pIndexBuffer = NULL;
	
	try 
	{
		pIndexBuffer = new EAGLIndexBuffer( this, objectName, indexList );
		
		if( objectName.Length() > 0 )
			_indexBufferPool.Add( pIndexBuffer );
	}
	catch (...)
	{
		if( pIndexBuffer )
			pIndexBuffer->UnuseResource();
		throw;
	}
	
	return pIndexBuffer;
}

//-------------------------------------------------------------------------------------
Rd3::VertexBuffer* EAGLRender::CreateVertexBuffer(
										 const sString& objectName,
										 const Rd3::VertexPList& points,
										 const Rd3::VertexNList& normals,
										 const Rd3::VertexTxCoord& txCoord
										 ) throws_error
{
	if( objectName.Length() > 0 && _vertexBufferPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
			_S("Duplicate object resource name :") + objectName 
		);
	
	EAGLVertexBuffer* vb = NULL;
	
	try
	{
		vb = new EAGLVertexBuffer( this, objectName, points, normals, txCoord );
		
		if( objectName.Length() > 0 )
			_vertexBufferPool.Add( vb );
	}
	catch(...)
	{
		if( vb )
			vb->UnuseResource();
		throw;
	}
	
	return vb;	
}

//-------------------------------------------------------------------------------------
Rd3::Texture* EAGLRender::CreateTexture(
									const sString& objectName,
									sInt width, sInt height,
									Rd3::TextureType::TextureType type,
									const Rd3::TextureParams& params
									) throws_error
{
	if( objectName.Length() > 0 && _textureResPool[objectName] != NULL )
		error_throw_arg( System::Errors::StringError ) 
		_S("Duplicate object resource name :") + objectName 
		);
	
	EAGLTexture* pTexture = NULL;
	try
	{
		pTexture = new EAGLTexture( this, objectName, type, width, height, params );
		
		if( objectName.Length() > 0 )
			_textureResPool.Add( pTexture );
	}
	catch (...)
	{
		if( pTexture )
			pTexture->UnuseResource();
		throw;
	}
	
	return pTexture;	
	
}


