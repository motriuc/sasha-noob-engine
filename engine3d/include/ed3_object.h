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

namespace Ed3 
{

class d3EngineData;
class d3RenderData;
class d3ObjectContiner;
class d3World;
	
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
class d3Object
{
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
	virtual void Uninitialize( Rd3::Render& render ) {}

	virtual void Render( const d3RenderData& renderData ) {};
	virtual void AI( d3EngineData& edata ) {}
	virtual void ComputeBoundingBox( d3AABBox& b );
	
	virtual void LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	virtual sBool LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;

private:
	d3AABBox                        _boundingBox;
	sString                         _name;
	d3ObjectContiner*               _parent;
	d3Matrix                        _transformationMatrix;
	sUInt                           _objectState;
	ObjectType::ObjectType			_type;
	
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
	
	ObjectActionState    _objectActionState;
protected:	
	d3ObjectClass		 _objectClass;
private:
	void ApplyLights( const d3RenderData& renderData );
	void ApplyLights( const d3RenderData& renderData, const Rd3::LightSelection& lights ); 
	
	void SetActionState( ObjectActionState s );
	
	friend class d3ObjectContiner;
};

#include "ed3_object.inl"

}

#endif // !defined(_SD3_OBJECT_H_)
