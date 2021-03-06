/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_render.h
//	Created                 : 20 1 2011   0:05
//	File path               : SLibF\render3d\include\dx9
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

#ifndef _DX9_RENDER_H_
#define _DX9_RENDER_H_

#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

#include "rd3_render.h"
#include "dx9/dx9_types.h"

/**
 * forward declarations
 */
namespace Rd3
{
class DX9RenderCreateParams;
}

/**
 *
 */
class Dx9Render : public Rd3::Render
{

private:
	typedef Rd3::Render _BaseClass;
public:
	static Rd3::Render* Create( const Rd3::DX9RenderCreateParams& param ) throws_error;
	/**
	 *
	 */
	static LPDIRECT3DDEVICE9 GetDX9Device( Rd3::Render* pRender );

	/**
	 * Initialize the render
	 */
	virtual void Initialize( Rd3::Def& def, const Rd3::StreamArchive& archive ) throws_error;


	/////////////////////////////////////////////////////////////
	// Create Vb
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
		const Rd3::VertexNList& normals
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
	) throws_error;

	/**
	 *
	 */
	virtual Rd3::VertexBuffer* CreateVertexBuffer(
		const sString& objectName,
		const Rd3::VertexPList& points,
		const Rd3::VertexCList& diffuseColor,
		const Rd3::VertexTxCoord& txCoord1,
		const Rd3::VertexTxCoord& txCoord2
	) throws_error;

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
	) throws_error;

	/////////////////////////////////////////////////////////
	// Create Index buffer
public:
	virtual Rd3::DynamicVertexBuffer* UseDynamicVertexBuffer( Rd3::VertexBufferStream::Set set ) throws_error;

	/////////////////////////////////////////////////////////
	// Create Index buffer
public:
	
	/**
	 *
	 */
	virtual Rd3::IndexBuffer* CreateIndexBuffer(
		const sString& objectName,
		const Rd3::IndexList& indexList
	) throws_error;
	
	//////////////////////////////////////////////////////////
	// Create Texture
public:
	
	/**
	 *
	 */
	virtual Rd3::Texture* CreateTexture(
		const sString& objectName,
		sInt width, sInt height,
		Rd3::TextureType::TextureType type,
		const Rd3::TextureParams& params
	) throws_error;

	/**
	 *
	 */
	virtual Rd3::Texture* CreateTextureFromFile(
		const sString& objectName,
		const sString& fileName,
		const Rd3::StreamArchive& archive,
		Rd3::TextureType::TextureType type,
		const Rd3::TextureParams& params
	) throws_error;
	
	///////////////////////////////////////////////////////////
	// Create effect
public:
	
	/**
	 *
	 */
	virtual Rd3::Effect* CreateEffectFromString(
		const sString& objectName,
		const Rd3::Def& def,
		const sString& effectCode,
		const Rd3::StreamArchive& archive
	) throws_error;

	/**
	 *
	 */
	virtual Rd3::Effect* CreateEffectFromFile(
		const sString& objectName,
		const Rd3::Def& def,
		const sString& fileName,
		const Rd3::StreamArchive& archive
	) throws_error;

	///////////////////////////////////////////////////////////
	// Create font
public:
	/**
	 *
	 */
	virtual Rd3::Font* CreateFontSystem(
		const sString& objectName,
		const sString& systemFontName,
		sInt fontSize
	) throws_error;


	virtual ~Dx9Render();

	void WindowResized( const d2Math::d2Vector& size );

public:
	LPDIRECT3DDEVICE9 GetHandle() const { return _pD3DDevice; }

	const struct Rd3::Dx9RenderParams& Params() { return _params; }

	void DeviceMonitor_AddResource( Rd3::ResourceObject* pRes );
	void DeviceMonitor_RemoveResource( Rd3::ResourceObject* pRes );
private:
	LPDIRECT3DDEVICE9           _pD3DDevice;
	struct Rd3::Dx9RenderParams _params;
	sVector<Rd3::ResourceObject*>	_deviceMonitorObjects;

	Dx9Render( LPDIRECT3DDEVICE9    pD3DDevice );

	void FillDeviceDef( Rd3::Def& def );
};


//////////////////////////////////////////////////////////////////////////////
// inline functions
inline LPDIRECT3DDEVICE9 Dx9Render::GetDX9Device( Rd3::Render* pRender )
{
	__S_ASSERT( pRender != NULL );
	__S_ASSERT( pRender->GetRenderType() == Rd3::RenderType::E_DX9 );

	return static_cast<Dx9Render*>( pRender )->_pD3DDevice;
}


#endif // _DX9_RENDER_H_
