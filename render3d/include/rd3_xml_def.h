////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_xml_def.h
//	Created            : 18 1 2012   23:04
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


#if !defined(_RD3_XMLDEFS_)
#define _RD3_XMLDEFS_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_def.h"

/************************************************************************/
/* XML Elements                                                         */
/************************************************************************/

#define ELEMENT_EFFECT			_S("effect")
#define ELEMENT_DEFAULT			_S("default")
#define ELEMENT_TRANSFORMATION	_S("transformation")
#define ELEMENT_MOVE			_S("move")
#define ELEMENT_ROTATE			_S("rotate")
#define ELEMENT_SCALE			_S("scale")
#define ELEMENT_BBOX			_S("bbox")
#define ELEMENT_CHILDREN		_S("children")
#define ELEMENT_BLENDING		_S("blending")
#define ELEMENT_TEXTURE			_S("texture")
#define ELEMENT_RESOURCES		_S("resources")
#define ELEMENT_CAMERA			_S("camera")
#define ELEMENT_TEXTURE_PARAMS	_S("texture.params")
#define ELEMENT_POSITION		_S("position")
#define ELEMENT_MESH			_S("mesh")
#define ELEMENT_MATERIAL		_S("material")
#define ELEMENT_VBUFFER			_S("vbuffer")
#define ELEMENT_IBUFFER			_S("ibuffer")
#define ELEMENT_PRERENDER		_S("prerender")
#define ELEMENT_PRIMITIVE		_S("primitive")
#define ELEMENT_FILTER			_S("filter")
#define ELEMENT_AFTER_EFFECT	_S("aftereffect")
#define ELEMENT_PHYSICS			_S("physics")
#define ELEMENT_GRAVITY			_S("gravity")
#define ELEMENT_PHYSICS_WORLD	_S("physics.world")
#define ELEMENT_PHYSICS_SHAPES	_S("physics.shapes")
#define ELEMENT_SHAPE			_S("shape")

#define ELEMENT_COLOR			_S("color")
#define ELEMENT_COLOR_DIFFUSE	_S("color.diffuse")
#define ELEMENT_COLOR_SPECULAR	_S("color.specular")
#define ELEMENT_COLOR_AMBIENT	_S("color.ambient")
#define ELEMENT_ATTENUATION		_S("attenuation")
#define ELEMENT_MAXDISTANCE		_S("maxdistance")
#define ELEMENT_LIGHT_POINT		_S("light.point")
#define ELEMENT_LIGHTS_STATIC	_S("lights.static")
#define ELEMENT_LIGHTS_STATIC_USE	_S("lights.static.use")


#define ATTR_SRC          _S("src")
#define ATTR_DST		  _S("dst")
#define ATTR_IFDEF        _S("ifdef")
#define ATTR_FILETYPE     _S("filetype")
#define ATTR_NAME         _S("name")
#define ATTR_FVF          _S("fvf")
#define ATTR_FIF          _S("fif")
#define ATTR_COUNT        _S("count")
#define ATTR_EFFECT       _S("effect")
#define ATTR_VALUE        _S("value")
#define ATTR_VERTEXBUFFER _S("vertexbuf")
#define ATTR_INDEXBUFFER  _S("indexbuf")
#define ATTR_PRIMITIVE    _S("primitive")
#define ATTR_TYPE         _S("type")
#define ATTR_X            _S("x")
#define ATTR_Y            _S("y")
#define ATTR_Z            _S("z")
#define ATTR_AX           _S("ax")
#define ATTR_AY           _S("ay")
#define ATTR_AZ           _S("az")
#define ATTR_R            _S("r")
#define ATTR_G            _S("g")
#define ATTR_B            _S("b")
#define ATTR_A            _S("a")
#define ATTR_ATENUATION   _S("atenuation")
#define ATTR_MAXDISTANCE  _S("maxdistance")
#define ATTR_TECHNIQUE    _S("technique")
#define ATTR_LUA          _S("lua")
#define ATTR_PS			  _S("ps")
#define ATTR_VS			  _S("vs")
#define ATTR_PATH		  _S("path")
#define ATTR_FILTER_MIN	  _S("filter.min")
#define ATTR_FILTER_MAG	  _S("filter.mag")
#define ATTR_ADDRESS_U	  _S("address.u")
#define ATTR_ADDRESS_V	  _S("address.v")
#define ATTR_MESH		  _S("mesh")
#define ATTR_WIDTH		  _S("width")
#define ATTR_HEIGHT		  _S("height")
#define ATTR_TEXTURE	  _S("texture")
#define ATTR_CLASS		  _S("class")
#define ATTR_LUA		  _S("lua")
#define ATTR_PARENT_ATTACH _S("parent.attach")
#define ATTR_INTENSITY	  _S("intensity")
#define ATTR_HARDNESS	  _S("hardness")

namespace Rd3 
{
	using namespace System::Types;
	using namespace System;
	using namespace System::d3Math;
	
/////////////////////////////////////////////////////
//

inline sBool XmlCheckDef( const Xml::BaseDomNode& node, const Def& def )
{
	sString val = node.GetAttributes()[ATTR_IFDEF];

	if( val.Length() <= 0 )
		return sTrue;

	return def.IsDefined( val );
}

//////////////////////////////////////////////////////
// color schema
//////////////////////////////////////////////////////
// Ex <aname r="1" g="0.5" b="0.1" a="1"/>
//
// The pColor size must at least 4 elements
void XmlLoad_ColorF( d3Float* pColor, const Xml::BaseDomNode& node, const Def& def );
void XmlLoad_ColorF( sRGBColor& color, const Xml::BaseDomNode& node, const Def& def );  


//////////////////////////////////////////////////////
// vector schema
//////////////////////////////////////////////////////
// Ex <aname x="1" y="0.5" z="0.1" />
//
// The pVector size must at least 3 elements
void XmlLoad_VectorF( d3Float* pVector, const Xml::BaseDomNode& node, const Def& def );

inline void XmlLoad_Vector( d3Vector& v, const Xml::BaseDomNode& node, const Def& def )
{
	XmlLoad_VectorF( v.v, node, def );
}
	
//////////////////////////////////////////////////////
// Transformation schema
//////////////////////////////////////////////////////
// Ex :
//
// <transformation type="cmd">
//    <move x="10" y="20" z="30"/>
//    <rotate ax="30" ay="40" az="100"/>
//    <scale ax="30" ay="40" az="100"/>
// </transformation>

// <transformation type="matrix">
//
// </transformation>
void XmlLoad_Transformation( d3Matrix& m, const Xml::BaseDomNode& node, const Def& def );


//////////////////////////////////////////////////////
// camera schema
//////////////////////////////////////////////////////
// Ex :
// 
// <camera>
//		<set2D /> 
// </camera>
void XmlLoad_Camera( d3Camera& c, const Xml::BaseDomNode& node, const Def& def );
	
	
//////////////////////////////////////////////////////
// texture params schema
//////////////////////////////////////////////////////
// Ex :
// 
// <texture.params filter.min="" filter.mag="" address.u="" address.v="" />
// </camera>
void XmlLoad_TextureParams( TextureParams& p, const Xml::BaseDomNode& node, const Def& def );
	
//////////////////////////////////////////////////////
// Bounding Box schema
//////////////////////////////////////////////////////
// <bbox type="auto" />
//

}

#endif // _RD3_XMLDEFS_
