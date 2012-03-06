/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_msg_keyboardq.h
//  Created                 : 6 3 2012   19:58
//  File path               : SLibF\render3d\include
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
#ifndef _RD3_MSG_KEYBOARDQ_INC_
#define _RD3_MSG_KEYBOARDQ_INC_

#include "rd3_msg.h"
#include "rd3_msg_keyboard.h"

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
class KeyboardMsgQueue : public MessageQueueT<KeyboardEvent>
{
private:	
	typedef MessageQueueT<KeyboardEvent> _BaseClass;	
public:
	/**
	 *
	 */
	KeyboardMsgQueue( Render* owner, const sString& objectName ) :
		_BaseClass( owner, objectName )
	{
	}
};

}

#endif // _RD3_MSG_KEYBOARDQ_INC_