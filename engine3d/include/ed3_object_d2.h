/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_object_d2.h
//  Created             : 20 3 2012
//  Author              : Motriuc Alexandru
//  File Path           : SLibF\engine3d\include
//  System independent  : 0%
//  Library             : 
//
//  Purpose:
//    
//
/////////////////////////////////////////////////////////////////////
//  Modification History :
//
/////////////////////////////////////////////////////////////////////

#ifndef _ED3_OBJECT_D2_INC_
#define _ED3_OBJECT_D2_INC_

/**
 * Check configuration file include
 */
#ifndef _ED3_CONF_H_
	#error ed3_conf.h must be included
#endif

#include "ed3_object.h"
#include "ed3_ui_msgq.h"

#include "rd3_dvertexbuffer.h"
#include "rd3_msg_gesture.h"
#include "rd3_material_texture.h"
#include "rd3_font.h"

namespace Ed3
{

/**
 * d2Object
 */
class d2Object : public d3Object
{
private:
	typedef d3Object _BaseClass;
public:
	/**
	 *
	 */
	d2Object( const sString& name = _S(""), sBool listenGestureEvents = sFalse );

	/**
	 *
	 */
	~d2Object();

	/**
	 * Obhect rectangle
	 */
	d2Rectangle GetRectangle() const	{ return d2Rectangle( d2Vector( -1.0f, -1.0f ), d2Vector( 1.0f, 1.0f ) );  }

protected:
	virtual void Initialize( Rd3::Render& render ) throws_error;
	virtual void Uninitialize( Rd3::Render& render );

	virtual void Render( const d3RenderData& renderData );
	virtual void AI( d3EngineData& edata );
	virtual void ComputeBoundingBox( d3AABBox& b );

	virtual void LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;

protected:
	// 2d specific functions
	void RenderTexture( const d2Point& posFrom, const d2Point& posTo, Rd3::Texture* pTexture, const d2Point& txFrom, const d2Point& txTo );

	// render textures
	void BeginRenderTexture( Rd3::Texture* pTexture, sInt count );
	void RenderTexture( const d2Point& posFrom, const d2Point& posTo, const d2Point& txFrom, const d2Point& txTo );
	void EndRenderTexture();

	void RenderText( const sString& text, const d2Point& point, d3Float height, sRGBColor color );

	virtual void OnGestureEvent( Rd3::EngineData& edata, const Rd3::GestureEvent& e ) {}
	virtual void Render2D( const d3RenderData& renderData ) = 0;

	UiMsgQueue* GetUIQueue() { return _uiQueue; }
private:
	d3Plane				_d2Plane;
	const d3RenderData*	_pRenderData;
	sBool				_listenGestureEvents;

	Rd3::use_resource<Rd3::DynamicVertexBuffer>	_vb;
	Rd3::use_resource<Rd3::TextureMaterial> _textureMaterial;
	Rd3::use_resource<UiMsgQueue>			_uiQueue;
protected:
	Rd3::use_resource<Rd3::Font>			_uiFont;
	sRGBColor								_uiFontColor;
private:
	void internal_OnGestureEvent( Rd3::EngineData& edata, const Rd3::GestureEvent& e );
};

}

#endif // _ED3_OBJECT_D2_INC_