/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_msg_gesture.h
//	Created                 : 10 2 2012   19:58
//	File path               : SLibF\render3d\include
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//	Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

#ifndef _RD3_MSG_GESTUREQ_INC_
#define _RD3_MSG_GESTUREQ_INC_

#include "rd3_msg.h"
#include "rd3_msg_gesture.h"

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

namespace Rd3
{

/**
 *GestureMsg
 */
class GestureMsgQueue : public MessageQueueT<GestureEvent>
{
private:	
	typedef MessageQueueT<GestureEvent> _BaseClass;	
public:
	/**
	 *
	 */
	GestureMsgQueue( Render* owner, const sString& objectName );
};
	
}

#endif // _RD3_MSG_GESTUREQ_INC_