////////////////////////////////////////////////////////////////////////
//  File Name          : rd3_register_types.cpp
//  Created            : 3 3 2012   23:04
//  Author             : Alexandru Motriuc  
//  File Path          : SLibF\render3d\include
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
#include "rd3afx.h"
#include "rd3_font_sprite.h"

#include "rd3_primitive.h"
#include "rd3_primitive_arrow.h"
#include "rd3_primitive_cone.h"
#include "rd3_primitive_sphere.h"
#include "rd3_primitive_torus.h"

#include "rd3_material.h"
#include "rd3_material_flatcolor.h"
#include "rd3_material_solid.h"
#include "rd3_material_texture.h"

namespace Rd3
{
//-----------------------------------------------------------------------
void RegisterTypes()
{
	// fonts 
	AUTO_REGISTER_FONT_FACTORY(			_S("sprite"),		FontSprite )
	
	// primitives
	AUTO_REGISTER_PRIMITIVE_FACTORY(	_S("arrow"),	PrimitiveArrow )
	AUTO_REGISTER_PRIMITIVE_FACTORY(	_S("cone"),		PrimitiveCone )
	AUTO_REGISTER_PRIMITIVE_FACTORY(	_S("sphere"),	PrimitiveSphere )
	AUTO_REGISTER_PRIMITIVE_FACTORY(	_S("torus"),	PrimitiveTorus )

	// materials
	AUTO_REGISTER_MATERIAL_FACTORY(		_S("flatcolor"),	FlatColorMaterial )
	AUTO_REGISTER_MATERIAL_FACTORY(		_S("solid"),		SolidMaterial )
	AUTO_REGISTER_MATERIAL_FACTORY(		_S("texture"),		TextureMaterial )
}


}