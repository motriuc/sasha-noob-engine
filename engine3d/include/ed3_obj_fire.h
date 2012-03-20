////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_obj_fire.h
//  Created            : 2 2 2012   19:09
//  Author             : Alexandru Motriuc  
//  File Path          : SLibF\engine3d\include
//  System independent : 0%
//  Library            : 
//
//  Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////

#ifndef _ED3_OBJ_FIRE_INC_
#define _ED3_OBJ_FIRE_INC_


#include "ed3_object.h"
#include "rd3_resobj.h"
#include "rd3_effect.h"

namespace Ed3
{
	
/**
 * d3FireObject
 */
class d3FireObject : public d3Object
{
private:
	typedef d3Object _BaseClass;
public:
	d3FireObject();
	
protected:
	/**
	 *
	 */
	virtual void Initialize( Rd3::Render& render ) throws_error;
	
	/**
	 *
	 */
	virtual void Render( const Ed3::d3RenderData& renderData );
	
private:
	Rd3::Effect::Float	sideFade;
	Rd3::Effect::Float	xScale;
	Rd3::Effect::Float	yScale;
	Rd3::Effect::Float	yFade;
	Rd3::Effect::Float	burnSpeed;
	Rd3::Effect::Float	wobbleScale;
	Rd3::Effect::Float	sideFadeSharpness;
	
	Rd3::use_resource<Rd3::VertexBuffer>	_vertexBuffer;
	Rd3::use_resource<Rd3::Texture>			_noiseTexture;
	Rd3::use_resource<Rd3::Texture>			_flameTexture;
	Rd3::use_resource<Rd3::Effect>			_fireEffect;
};
	
	
}

#endif // _ED3_OBJ_FIRE_INC_