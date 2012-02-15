////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_lightpoint.h
//	Created            : 29.1.2011   17:25
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

#include "rd3_def.h"

namespace Rd3
{
	
using namespace System::d3Math;
using namespace System;

/////////////////////////////////////////////////
// Light schema
//
// <>
//		<color.diffuse>
//		<color.ambient>
//		<color.specular>
//		<position>
//		<attenuation>
//		<maxdistance>
// </>
	
/**
 * LightPoint
 */
class LightPoint
{
public:
	LightPoint();
	
	LightPoint( const sRGBColor color, const d3Vector& pos );

	sRGBColor GetDiffuzeColor() const;
	sRGBColor GetSpecularColor() const;
	sRGBColor GetAmbientColor() const;
	const d3Vector& GetPosition() const;
	d3Float GetAttenuation() const;
	
	/**
	 *
	 */
	void LoadFromXml( const Xml::BaseDomNode& node, const Def& def );
	
	/**
	 *
	 */
	d3Float GetVisibilityFactor( const d3Vector& p ) const;
private:
	sRGBColor	_diffuseColor;
	sRGBColor	_specularColor;
	sRGBColor	_ambientColor;
	d3Vector	_position;
	d3Float		_attenuation;
	d3Float		_maxLigtiningDistance;    // 0 means infinite	
};

#include "rd3_lightpoint.inl"

}