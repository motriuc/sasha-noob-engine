////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_world.h
//	Created            : 20 1 2012   19:09
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


#if !defined(_ED3_WORLD_H_)
#define _ED3_WORLD_H_

#include "ed3_cont_object.h"
#include "ed3_resloader.h"
#include "rd3_light.h"
#include "ed3_prerender.h"
#include "rd3_after_effect.h"

namespace Ed3 
{

class d3PhysicsWorld;
	
///////////////////////////////////////////////////////////
// <world name=""> : d3ObjectContiner
//		<resources>
//			d3ResourceLoader
//		</resources>
//	
//		<lights.static>
//		<camera/>
// </world> 
	
/**
 * d3World
 */
class d3World : public d3ObjectContiner
{
private:
	typedef d3ObjectContiner _BaseClass;
public:
	/**
	 *
	 */
	d3World();
	~d3World();
	
	/**
	 *
	 */
	const d3Camera& GetCamera() const { return _camera; }
	d3Camera& GetCamera() { return _camera; }
	
	/**
	 *
	 */
	const Rd3::LightList& GetStaticLights() const	{ return _staticLights; }
	
	/**
	 *
	 */
	void RenderWorld( Rd3::WorldRenderState& rstate, Rd3::EngineDataForRender& edata );
	
	/**
	 *
	 */
	const d3ObjectClassNames& ObjectClassNames() const	{ return _objectClassNames; }
	
	
	void SetAfterEffect( Rd3::AfterEffect* p );
	Rd3::AfterEffect* GetAfterEffect()				{ return _afterEffect; }
	
#ifdef ED3_ENGINE_USE_PHYSICS	
	/**
	 *
	 */
	d3PhysicsWorld* GetPhysics()					{ return _physicsWorld; }
#endif // ED3_ENGINE_USE_PHYSICS
protected:
	
	/**
	 *
	 */
	virtual void Initialize( Rd3::Render& render ) throws_error;
	
	virtual void AI( d3EngineData& edata );
	
	/**
	 *
	 */
	virtual void LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	
	/**
	 *
	 */
	virtual sBool LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	
private:
	d3ResourceLoader	_resources;
	d3Camera			_camera;
	Rd3::LightList		_staticLights;
	d3PreRenderList		_preRenders;
	d3ObjectClassNames	_objectClassNames;
	d3ObjectClass		_defaultRenderClass;
	
	Rd3::use_resource<Rd3::AfterEffect> _afterEffect;
	
#ifdef ED3_ENGINE_USE_PHYSICS
	d3PhysicsWorld*		_physicsWorld;
	
	void LoadPhysicsFromXml( const Xml::BaseDomNode& element, LoadDataParams& loadParams );
#endif	
};

}

#endif // _ED3_WORLD_H_
