////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_obj_cam_key.h
//  Created            : 6 3 2012   19:09
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

#ifndef _ED3_OBJ_CAM_KEY_INC_
#define _ED3_OBJ_CAM_KEY_INC_

#include "ed3_object.h"

namespace Ed3
{

/**
 * d3CameraKeyboardObject
 */
class d3CameraKeyboardObject : public d3Object
{
private:
	typedef d3Object _BaseClass;
public:
	d3CameraKeyboardObject();
	
protected:
	/**
	 *
	 */
	virtual void Initialize( Rd3::Render& render ) throws_error;
	virtual void Uninitialize( Rd3::Render& render );
	
	/**
	 *
	 */
	virtual void Render( const d3RenderData& renderData );
	
	/**
	 *
	 */
	virtual void AI( d3EngineData& edata );
	
	/**
	 *
	 */
	virtual void LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
private:
	d3Float		_moveStep;
	d3Float		_rotateStep;
	void OnKeyboardMessage( Rd3::EngineData& edata, const Rd3::KeyboardEvent& key );
};

}

#endif // _ED3_OBJ_CAM_KEY_INC_