/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_object.h
//  Created             : 19 1 2012
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

#if !defined(_ED3_OBJECT_H_)
#define _ED3_OBJECT_H_

/**
 * Check configuration file include
 */
#ifndef _ED3_CONF_H_
  #error ed3_conf.h must be included
#endif

#include "ed3_types.h"
#include "ed3_obj_class.h"

#ifdef ED3_ENGINE_USE_LUA
	#include "ed3_lua.h"
#endif

#ifdef _D3_DEBUG_RENDER
	#include "rd3_dvertexbuffer.h"
	#include "rd3_effect.h"
#endif

namespace Ed3 
{

class d3EngineData;
class d3RenderData;
class d3ObjectContiner;
class d3World;
class phShape;
	
namespace ObjectType
{
	enum ObjectType
	{
		E_OBJECT,
		E_CONTINER,
		E_WORLD,
		
		COUNT,
		UNKNOWN
	};
}
	
//////////////////////////////////////////////////////
// d3Object schema 
//////////////////////////////////////////////////////
// <object name="a name">
//		<transformation/>
//		<bbox type="auto" />
//		<light.static.use /> // apply global static lights
// </object>


/**
 * Render Object
 */
class d3Object : public Obj::Object
{
	_SLIB_RUNTIME( Ed3, d3Object, Obj::Object )
public:
	d3Object( ObjectType::ObjectType type = ObjectType::E_OBJECT, const sString& name = _S("") );

	/**
	 * Initialize object	
	 */
	void DoInitialize( Rd3::Render& render ) throws_error;
	void DoUninitalize( Rd3::Render& render );
	
	/**
	 * Render the object
	 */
	void DoRender( const d3RenderData& renderData );
	
	/**
	 * Do AI
	 */
	void DoAI( d3EngineData& edata );
	
	/**
	 * load from xml see object schema
	 */
	void DoLoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	
	/**
	 *
	 */
	void DoLoadFromXMLFile( const sString& path, LoadDataParams& loadParams ) throws_error;
public:
	
	/**
	 * Retruns true if the object is visible ()
	 */
	sBool IsVisible() const;

	/**
	 * Return true if the object is suspended
	 */
	sBool IsSuspended() const;
	
	/**
	 * Returns true if the objet has transfirmation matrix
	 */
	sBool HasTransformationMatrix() const;
	
	/**
	 *
	 */
	sBool HasBoundingBox() const;

	/**
	 * Get transformaton matrix
	 */
	const d3Matrix& GetTransformationMatrix() const;

	/**
	 * Set transformation matrix
	 */
	void SetTransformationMatrix( const d3Matrix& m );
	
	/**
	 *
	 */
	void GetAbsoluteTransformationMatrix( d3Matrix& m ) const;

	/**
	 *
	 */
	void ApplyTranformation( const d3Matrix& m );

	/**
	 *
	 */
	const d3AABBox& GetBoundingBox() const;
  
	/**
	 * returns Object Name
	 */
	const sString& GetName() const;

	/**
	 * returns engine object type
	 */
	ObjectType::ObjectType GetType() const;
	
	/**
	 *
	 */
	d3ObjectContiner* GetParent();
	const d3ObjectContiner* GetParent() const;
	d3World* GetWorld();

	/**
	 * 
	 */
	virtual ~d3Object();
	
public:

protected:
	/**
	 * Object States 
	 */
	enum ObjectState
	{
		OBS_NONE					= 0x00000000,
		OBS_VISIBLE					= 0x00000001,      // draw
		OBS_SUSPEND					= 0x00000002,      // don't do AI
		OBS_BOUNDINGBOX				= 0x00000004,
		OBS_TRANSFORMATION_MATRIX	= 0x00000008,
		OBS_AI						= 0x00000010,
		OBS_COMPUTE_AUTO_BBOX		= 0x00000020,
		OBS_USE_WORLD_STATIC_LIGHTS = 0x00000040
	};
	
	/**
	 *
	 */
	void SetState( sUInt uState );
	
	/**
	 *
	 */
	sBool HasState( ObjectState uState ) const;
	
	/**
	 *
	 */
	void AddState( ObjectState uState );
	
	/**
	 *
	 */
	void RemoveState( ObjectState uState );
	
protected:
	virtual void Initialize( Rd3::Render& render ) throws_error;
	virtual void Uninitialize( Rd3::Render& render );

	virtual void Render( const d3RenderData& renderData ) {};
	virtual void AI( d3EngineData& edata ) {}
	virtual void ComputeBoundingBox( d3AABBox& b );
	
	virtual void LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	virtual sBool LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;

#ifdef ED3_ENGINE_USE_LUA
	virtual void InitLuaFunctions();
#endif
	
private:
	enum ObjectActionState
	{
		OBAS_INIT       = 0,
		OBAS_LOADING    = 1,
		OBAS_SAVING     = 2,
		OBAS_IDLE       = 3,
		OBAS_RENDER     = 4,
		OBAS_AI         = 5,
		OBAS_FREE		= 6
	};
	
	ObjectActionState				_objectActionState;	
	d3AABBox                        _boundingBox;
	sString                         _name;
	d3ObjectContiner*               _parent;
	d3Matrix                        _transformationMatrix;
	sUInt                           _objectState;
	ObjectType::ObjectType			_type;
	
#ifdef ED3_ENGINE_USE_PHYSICS
	phShape*						_phAutoShape;
#endif // ED3_ENGINE_USE_PHYSICS
	
protected:	
	d3ObjectClass					_objectClass;
	
#ifdef ED3_ENGINE_USE_LUA	
	LuaObject						_luaObject;
	sBool							_luaHasAI;
	sBool							_luaHasInit;
	sBool							_luaHasKeyboardEvent;
#endif // ED3_ENGINE_USE_LUA
		
private:
	void ApplyLights( const d3RenderData& renderData );
	void ApplyLights( const d3RenderData& renderData, const Rd3::LightSelection& lights );
	
#ifdef ED3_ENGINE_USE_LUA	
	void LoadLua( const sString& path, LoadDataParams& loadParams ) throws_error;
	
	void LuaCallInit( Rd3::Render& render );
	void LuaCallAI( d3EngineData& edata );
	void LuaKeyboardMessage( Rd3::EngineData& edata, const Rd3::KeyboardEvent& key );
	
#endif // ED3_ENGINE_USE_LUA
	
#ifdef ED3_ENGINE_USE_PHYSICS	
	void LoadFromXML_PhysicsShapes( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
#endif // ED3_ENGINE_USE_PHYSICS
	
	void SetActionState( ObjectActionState s );
	
	friend class d3ObjectContiner;

#ifdef _D3_DEBUG_RENDER
protected:
	mutable Rd3::use_resource<Rd3::DynamicVertexBuffer>	_debug_vb;
	mutable Rd3::use_resource<Rd3::Effect>				_debug_effect_solid;

	void debug_InitResources( Rd3::Render& render );
	virtual void debug_Render( const d3RenderData& renderData );
	
	void debug_Draw( const d3RenderData& renderData, const d3AABBox& b, sRGBColor cl ) const;
	void debug_Draw( const d3RenderData& renderData, const d3LineSegment& segment, sRGBColor cl ) const;
#endif
};

#include "ed3_object.inl"

}

#endif // !defined(_SD3_OBJECT_H_)
