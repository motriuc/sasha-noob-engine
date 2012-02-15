/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_render.h
//	Created                 : 11 1 2012   0:05
//	File path               : SLibF\render3d\include\eagl
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

#ifndef _EAGL_RENDER_H_
#define _EAGL_RENDER_H_

#ifndef _EAGL_CONF_H_
	#error eagl_conf.h must be included
#endif

#include "rd3_render.h"
#include "eagl_types.h"
#include "platform_eagl_context.h" 

class EAGLTexture;

/**
 * forward declarations
 */
namespace Rd3
{
	class EAGLRenderCreateParams;
}

/**
 * EAGLRender
 */
class EAGLRender : public Rd3::Render
{

private:
	typedef Rd3::Render _BaseClass;
private:
	EAGLRender();
public:
	static Rd3::Render* Create( const Rd3::EAGLRenderCreateParams& param ) throws_error;

	/**
	 * Initialize the render
	 */
	virtual void Initialize( Rd3::Def& def, const Streams::StreamArchive& archive ) throws_error;

public:	
	/**
	 *
	 */
	virtual Rd3::IndexBuffer* CreateIndexBuffer(
		const sString& objectName,
		const Rd3::IndexList& indexList
	) throws_error;
	
public:	
	/**
	 *
	 */
	virtual Rd3::VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points
	) throws_error;

	/**
	 *
	 */
	virtual Rd3::VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexTxCoord& txCoord
	) throws_error;

	/**
	 *
	 */
	virtual Rd3::VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexNList& normals,
		const Rd3::VertexTxCoord& txCoord
	) throws_error;
	
	/**
	 *
	 */
	virtual Rd3::VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexTxCoord& txCoord1,
		const Rd3::VertexTxCoord& txCoord2
	) throws_error  { return NULL; }

	/**
	 *
	 */
	virtual Rd3::VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexCList& diffuseColor,
		const Rd3::VertexTxCoord& txCoord1,
		const Rd3::VertexTxCoord& txCoord2
	) throws_error  { return NULL; }

	/**
	 *
	 */
	virtual Rd3::VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points, 
		const Rd3::VertexCList& diffuseColor
	) throws_error;

	/**
	 *
	 */
	virtual Rd3::VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexNList& normals,
		const Rd3::VertexCList& diffuseColor
	) throws_error { return NULL; }
	

	/**
	 *
	 */
	virtual Rd3::Texture* CreateTexture(
		const sString& objectName,
		sInt width, sInt height,
		Rd3::TextureType::TextureType type
	) throws_error;

	/**
	 *
	 */
	virtual Rd3::Texture* CreateTextureFromFile(
		const sString& objectName,
		const sString& fileName,
		const Streams::StreamArchive& archive,
		Rd3::TextureType::TextureType type = Rd3::TextureType::E_IMAGE,
		const Rd3::TextureParams& params = Rd3::TextureParams()
	) throws_error;
	
	/**
	 *
	 */
	virtual Rd3::Effect* CreateEffectFromString(
		const sString& objectName,
		const Rd3::Def& def,
		const sString& effectCode,
		const Streams::StreamArchive& archive
	) throws_error;

	/**
	 *
	 */
	virtual Rd3::Effect* CreateEffectFromFile(
		const sString& objectName,
		const Rd3::Def& def,
		const sString& fileName,
		const Streams::StreamArchive& archive
	) throws_error;

	/**
	 *
	 */
	virtual Rd3::Font* CreateFontSystem(
		const sString& objectName,
		const sString& systemFontName,
		sInt fontSize
	) throws_error;
	
	virtual ~EAGLRender();
	
public:
	/**
	 *
	 */
	_PLATFORM Rd3::Texture* EAGLCreateTexture( 
		const sString& objectName,
		GLuint textId, sInt width, sInt height,
		Rd3::TextureType::TextureType type,
		const Rd3::TextureParams& params
	);
public:
	const struct Rd3::EAGLRenderParams& Params() { return _params; }
	
public:
	_PLATFORM void SetAsCurrentContext();
	_PLATFORM void SetPresent();
	_PLATFORM void EaglSetRenderTarget( EAGLTexture* pTexture );
private:
	struct Rd3::EAGLRenderParams _params;
	EAGLRenderContext*			 _renderContext;
	
    GLint _framebufferWidth;
    GLint _framebufferHeight;
    
    GLuint _defaultFramebuffer;
	GLuint _colorRenderbuffer;
	GLuint _depthRenderbuffer;
	GLuint _stencilRenderbuffer;

private:	
	void FillDeviceDef( Rd3::Def& def );
	
	void InitCreateFrameBuffers( Rd3::Def& def ) throws_error;
	void InitSystemResources( Rd3::Def& def, const Streams::StreamArchive& archive ) throws_error;
	void FreeFrameBuffers();
};

/**
 * inlines
 */
inline void EAGLRender::SetAsCurrentContext()
{
	EAGLRenderContext_SetCurrent( _renderContext ); 

	glBindFramebuffer( GL_FRAMEBUFFER, _defaultFramebuffer );
	glViewport( 0, 0, _framebufferWidth, _framebufferHeight );
}

inline void EAGLRender::SetPresent()
{
	glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderbuffer);
	EAGLRenderContext_PresentRenderbuffer( _renderContext, GL_RENDERBUFFER );
}

#endif // _DX9_RENDER_H_
