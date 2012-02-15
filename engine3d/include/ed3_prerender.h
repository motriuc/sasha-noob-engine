////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_prerender.h
//	Created            : 15 02 2012   19:09
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\engine3d\include
//  System independent : 0%
//  Library            : 
//
//	Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////

#ifndef _ED3_PRERENDER_H_
#define _ED3_PRERENDER_H_

#ifndef _ED3_CONF_H_
	#error ed3_conf.h must be included
#endif

#include "ed3_types.h"
#include "rd3_texture.h"
#include "ed3_obj_class.h"

namespace Ed3 
{

class d3World;
	
/**
 * d3PreRender
 */
class d3PreRender
{
public:	
	d3PreRender();
	
	/**
	 *
	 */
	void Initialize( Rd3::Render& render );
	
	/**
	 *
	 */
	void LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;

	/**
	 *
	 */
	void Render( Rd3::WorldRenderState& rstate, Rd3::EngineDataForRender& edata, d3World& world );
	
private:
	sInt	_width;
	sInt	_height;
	
	Rd3::use_resource<Rd3::Texture>	_texture;
	d3ObjectClass					_renderClass;
	
};
	
/**
 * d3PreRenderList
 */
class d3PreRenderList
{
public:
	void Initialize( Rd3::Render& render );
	
	/**
	 *
	 */
	void LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	
	/**
	 *
	 */
	void Render( Rd3::WorldRenderState& rstate, Rd3::EngineDataForRender& edata, d3World& world );
	
	~d3PreRenderList();
private:
	sVector<d3PreRender*>	_preRenderList;
};
	
}
#endif // _ED3_PRERENDER_H_
