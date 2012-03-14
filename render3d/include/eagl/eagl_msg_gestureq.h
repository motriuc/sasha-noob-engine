/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_msg_gestureq.h
//  Created                 : 14 3 2012
//  File path               : SLibF\render3d\include\dx9
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_msg_gestureq.h"

/**
 * EaglGestureMsgQueue
 */
class EaglGestureMsgQueue : public Rd3::GestureMsgQueue
{
private:
	typedef Rd3::GestureMsgQueue _BaseClass;
public:
	EaglGestureMsgQueue( Rd3::Render* owner, const sString& objectName );

	~EaglGestureMsgQueue();
	
	virtual void ProcessMessages( Rd3::EngineData& edata );
	
	void PostMessage( const Rd3::GestureEvent& event );
private:
	sVector<Rd3::GestureEvent>	_events;
};

