////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_light.h
//	Created            : 5 2 2012   17:25
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\render3d\include
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
#ifndef _RD3_LIGHT_INC_
#define _RD3_LIGHT_INC_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#define MAX_LIGHT_BUFFER	64

#include "rd3_lightpoint.h"

namespace Rd3
{

/**
 * Light
 */
class Light
{
public:
	/**
	 *
	 */
	Light();
	
	/**
	 *
	 */
	explicit Light( const LightPoint& src );
	
	/**
	 *
	 */
	Light( const Light& src );
	
	/**
	 *
	 */
	void operator = ( const Light& src );
	
	/**
	 *
	 */
	void operator = ( const LightPoint& src );

	/**
	 *
	 */
	void LoadFromXml( const Xml::BaseDomNode& node, const Def& def ) throws_error;
	
	/**
	 *
	 */
	d3Float GetVisibilityFactor( const d3Vector& p ) const;
	
	/**
	 *
	 */
	LightType::LightType GetType() const;

	/**
	 *
	 */
	const LightPoint& lightPoint() const;
private:
	LightType::LightType	_type;
	SBYTE					_lightBuffer[MAX_LIGHT_BUFFER];
private:
	LightPoint& lightPoint();
	
	void Assign( const LightPoint& src );
	void Assign( const Light& src );
	void Free();
};

	
/**
 * LightList
 */
class LightList
{
public:
	/**
	 *
	 */
	LightList();
	
	/**
	 *
	 */
	void LoadFromXml( const Xml::BaseDomNode& node, const Def& def ) throws_error;
	
	/**
	 *
	 */
	void AddLight( const Light& light );
	
	/**
	 *
	 */
	sInt Size() const;
	
	/**
	 *
	 */
	const Light& operator [] ( sInt i ) const;
	
private:
	sVector<Light>		_lightList;
};
	
#include "rd3_light.inl"	
}

#endif // _RD3_LIGHT_INC_