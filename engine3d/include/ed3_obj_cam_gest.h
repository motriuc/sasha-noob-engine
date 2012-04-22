////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_obj_cam_gest.h
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

#ifndef _ED3_OBJ_CAM_GEST_INC_
#define _ED3_OBJ_CAM_GEST_INC_

#include "ed3_object.h"
#include "rd3_msg_gesture_detect.h"

namespace Ed3
{

/**
 * d3CameraGestureObject
 */
class d3CameraGestureObject : public d3Object
{
private:
	typedef d3Object _BaseClass;
public:
	d3CameraGestureObject( );
	
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
	d3Vector	_move;

	Rd3::GestureDetect	_gestureDetect;

	void OnGestureEvent( Rd3::EngineData& edata, const Rd3::GestureEvent& event );

	void OnGestureTap( Rd3::EngineData& edata, const d3Point& position );
	void OnGestureSwipe( Rd3::EngineData& edata, const d3Vector& delta );
};
	
	
}

#endif // _ED3_OBJ_CAM_GEST_INC_