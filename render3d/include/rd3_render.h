/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_render.h
//  Created                 : 20 1 2011   0:05
//  File path               : SLibF\render3d\include
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
#ifndef _RD3_RENDER_H_
#define _RD3_RENDER_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

#include "rd3_resobj.h"
#include "rd3_msg.h"
#include "rd3_resloader.h"

namespace Rd3
{

using namespace System::Streams;
using namespace System::d2Math;
	
/**
 * Render
 */ 
class Render
{
public:
	/**
	 * Creates render 
	 */
	static Render* CreateRender( const RenderCreateParams& params ) throws_error; 

	/**
	 * Destuctor
 	 */
	virtual ~Render();

	/**
	 * Initialize the render
	 * and fills the def with hardware specific defs
	 */
	virtual void Initialize( Def& def, const StreamArchive& archive ) throws_error;
	
	///////////////////////////////////////////////////////////
	// Get info 
public:	
	/**
	 * Return render type
	 */
	RenderType::RenderType GetRenderType() const				{ return _renderType; }
	
	///////////////////////////////////////////////////////////
	// Rendering
public:	
	/**
	 * Returns current render state
	 */
	WorldRenderState* RenderState()								{ return _pRenderState; }
			
	/**
	 * returns screen size in pixels
	 */
	d2Vector GetScreen_SizeInPixels() const						{ return _screenSizeInPixels; }
	
	////////////////////////////////////////////////////////////
	// Resources
public:
	
	/**
	 * Effect
	 */
	Effect* GetEffect( const sString& effectName )				{ return reinterpret_cast<Effect*>( _effectResPool[effectName] ); }
	Effect* UseEffect( const sString& effectName ) throws_error;
	
	/**
	 * Texture
	 */
	Texture* GetTexture( const sString& textureName )			{ return reinterpret_cast<Texture*>( _textureResPool[textureName] );}
	Texture* UseTexture( const sString& textureName ) throws_error;
	
	/**
	 * Font
	 */
	Font* GetFont( const sString& fontName )					{ return reinterpret_cast<Font*>( _fontResPool[fontName] ); }
	Font* UseFont( const sString& fontName ) throws_error;

	/**
	 * Mesh
	 */
	Mesh* GetMesh( const sString& meshName )					{ return reinterpret_cast<Mesh*>( _meshResPool[meshName] ); }
	Mesh* UseMesh( const sString& meshName ) throws_error;
	
	/**
	 * Vb
	 */
	VertexBuffer* GetVb( const sString& vbName )			{ return reinterpret_cast<VertexBuffer*>( _vertexBufferPool[vbName] ); }
	VertexBuffer* UseVb( const sString& vbName ) throws_error;
	
	/**
	 * Ib
	 */
	IndexBuffer* GetIb( const sString& ibName )				{ return reinterpret_cast<IndexBuffer*>( _indexBufferPool[ibName] ); }
	IndexBuffer* UseIb( const sString& ibName ) throws_error;
	
	/**
	 * Ef
	 */
	AfterEffect* GetAfterEffect( const sString& eName )		{ return reinterpret_cast<AfterEffect*>( _aftereffectResPool[eName] ); }
	AfterEffect* UseAfterEffect( const sString& eName ) throws_error;
	
	/////////////////////////////////////////////////////////////
	// Create Vb
public:
	
	/**
	 *
	 */
	virtual VertexBuffer* CreateVertexBufferFromFile(
		const sString& objectName,
		const sString& path,
		const StreamArchive& archive
	) throws_error;
	
	/**
	 *
	 */
	virtual VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const VertexPList& points 
	) throws_error = 0;

	/**
	 *
	 */
	virtual VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const VertexPList& points,
		const VertexTxCoord& txCoord
	) throws_error = 0;

	/**
	 *
	 */
	virtual VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const VertexPList& points,
		const VertexNList& normals
	) throws_error = 0;
	
	/**
	 *
	 */
	virtual VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const VertexPList& points,
		const VertexNList& normals,
		const VertexTxCoord& txCoord
	) throws_error = 0;
	
	/**
	 *
	 */
	virtual VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const VertexPList& points,
		const VertexTxCoord& txCoord1,
		const VertexTxCoord& txCoord2
	) throws_error = 0;

	/**
	 *
	 */
	virtual VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const VertexPList& points,
		const VertexCList& diffuseColor,
		const VertexTxCoord& txCoord1,
		const VertexTxCoord& txCoord2
	) throws_error = 0;

	/**
	 *
	 */
	virtual VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const VertexPList& points,
		const VertexCList& diffuseColor
	) throws_error = 0;

	/**
	 *
	 */
	virtual VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const VertexPList& points,
		const VertexNList& normals,
		const VertexCList& diffuseColor
	) throws_error = 0;

	/////////////////////////////////////////////////////////
	// Create Index buffer
public:
	
	/**
	 *
	 */
	virtual IndexBuffer* CreateIndexBuffer(
		const sString& objectName,
		const IndexList& indexList
	) throws_error = 0;

	/**
	 *
	 */
	virtual IndexBuffer* CreateIndexBufferFromFile(
		const sString& objectName,
		const sString& path,
		const StreamArchive& archive
	) throws_error;
	
	//////////////////////////////////////////////////////////
	// Create Texture
public:
	
	/**
	 *
	 */
	virtual Texture* CreateTexture(
		const sString& objectName,
		sInt width, sInt height,
		TextureType::TextureType type = TextureType::E_IMAGE,
		const TextureParams& params = TextureParams()
	) throws_error = 0;

	/**
	 *
	 */
	virtual Texture* CreateTextureFromFile(
		const sString& objectName,
		const sString& fileName,
		const StreamArchive& archive,
		TextureType::TextureType type = TextureType::E_IMAGE,
		const TextureParams& params = TextureParams()
	) throws_error = 0;
	
	///////////////////////////////////////////////////////////
	// Create effect
public:
	
	/**
	 *
	 */
	virtual Effect* CreateEffectFromString(
		const sString& objectName,
		const Def& def,
		const sString& effectCode,
		const StreamArchive& archive
	) throws_error = 0;

	/**
	 *
	 */
	virtual Effect* CreateEffectFromFile(
		const sString& objectName,
		const Def& def,
		const sString& fileName,
		const StreamArchive& archive
	) throws_error = 0;

	///////////////////////////////////////////////////////////
	// Create font
public:
	/**
	 *
	 */
	virtual Font* CreateFontSystem(
		const sString& objectName,
		const sString& systemFontName,
		sInt fontSize
	) throws_error = 0;

	/**
	 *
	 */
	Font* CreateFontFromFile(
		const sString& objectName,
		const sString& fileName,
		const Def& def,
		const StreamArchive& archive
	);
	
	///////////////////////////////////////////////////////////
	// Create mesh
public:
	
	Mesh* CreateMeshFromFile( 
		const sString& objectName,
		const sString& fileName,
		const Def& def,
		const StreamArchive& archive
	);
	
	///////////////////////////////////////////////////////////
	// Create affter effect
public:	
	AfterEffect* CreateAfterEffectFromFile( 
		const sString& objectName,
		const sString& fileName,
		const Def& def,
		const StreamArchive& archive
	);
	
	///////////////////////////////////////////////////////////
	// Message Q
public:
	void AddMessageQueue( MessageQueue* pMsgQ );
	MessageQueue* GetMessageQueue( const sString& name )			{ return reinterpret_cast<MessageQueue*> ( _messageQResPool[name] ); }
	
	template< typename _Type >
	void MessageQueue_RegisterEvent( const sString& name, const Events::sEvent1<_Type&>& e )
	{
		typedef MessageQueueT<_Type> MsgQ;
		
		MsgQ* pMsg = reinterpret_cast<MsgQ*>( GetMessageQueue( name ) );
		if( pMsg == NULL )
		{
			error_throw_arg( Errors::StringError )
				_S("Message Q : " ) + name + _S(" not found.")
			);
		}
		
		pMsg->UseResource();
		pMsg->Register( e );
	}

	template< typename _Type >
	void MessageQueue_UnregisterEvent( const sString& name, const Events::sEvent1<_Type&>& e )
	{
		typedef MessageQueueT< _Type > MsgQ;
		
		MsgQ* pMsg = reinterpret_cast<MsgQ*>( GetMessageQueue( name ) );
		if( pMsg == NULL )
		{
			error_throw_arg( Errors::StringError )
				_S("Message Q : " ) + name + _S(" not found.")
			);
		}
		
		pMsg->UnuseResource();
		pMsg->Unregister( e );
	}
	
protected:
	Render( const RenderType::RenderType type );

	WorldRenderState*		_pRenderState;
	d2Vector				_screenSizeInPixels;

	/**
	 * Resource Pools
	 */
	TypedResourcePool		_effectResPool;
	TypedResourcePool		_textureResPool;

	TypedResourcePool		_vertexBufferPool;
	TypedResourcePool		_indexBufferPool;
	TypedResourcePool		_meshResPool;
	
	TypedResourcePool		_fontResPool;
	TypedResourcePool		_messageQResPool;
	TypedResourcePool		_aftereffectResPool;
	
	ResourceLoader			_renderResources;
private:
	RenderType::RenderType  _renderType;
	
	void NotifyFreeResource( ResourceObject* pRes );
	
	VertexBuffer* CreateVertexBufferFromVBFile( 
		const sString& objectName,
		const sString& path,
		const StreamArchive& archive
	) throws_error;

	IndexBuffer* CreateIndexBufferFromVBFile( 
		const sString& objectName,
		const sString& path,
		const StreamArchive& archive
	) throws_error;
	
	friend class ResourceObject;
};


}

#endif // _RD3_RENDER_H_
