////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_object_register.cpp
//  Created            : 20 3 2012 
//  Author             : Alexandru Motriuc  
//  File Path          : SLibF\engine3d\cpp
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
#include "ed3afx.h"
#include "rd3_primitive.h"

#include "ed3_primitive_lua.h"
#include "ed3_obj_cam_gest.h"
#include "ed3_obj_cam_key.h"
#include "ed3_obj_factory.h"
#include "ed3_obj_mesh.h"
#include "ed3_obj_texture.h"
#include "ed3_ui_txbutton.h"

namespace Ed3
{

//----------------------------------------------------------------------
void RegisterEngineTypes()
{
	AUTO_REGISTER_PRIMITIVE_FACTORY( _S("lua"),	                          PrimitiveLua )
	AUTO_REGISTER_D3OBJECT_FACTORY( _S("engine.object.gesturecamera") ,   d3CameraGestureObject )
	AUTO_REGISTER_D3OBJECT_FACTORY( _S("engine.object.keyboardcamera") ,  d3CameraKeyboardObject )

	AUTO_REGISTER_D3OBJECT_FACTORY( _S("engine.object.mesh") ,            d3MeshObject )	
	AUTO_REGISTER_D3OBJECT_FACTORY( _S("engine.object.texture") ,         d3TextureObject )

	// UI
	AUTO_REGISTER_D3OBJECT_FACTORY( _S("engine.ui.txbutton"),             uiTxButton );
}

}
