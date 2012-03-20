/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_ui_msgq.h
//  Created             : 20 3 2012
//  Author              : Motriuc Alexandru
//  File Path           : SLibF\engine3d\include\ui
//  System independent  : 0%
//  Library             : 
//
//  Purpose:
//    
//
/////////////////////////////////////////////////////////////////////
//  Modification History :
//
/////////////////////////////////////////////////////////////////////
#ifndef _ED3_UI_MSGQ_INC_
#define _ED3_UI_MSGQ_INC_

#include "ed3_ui_msg.h"
#include "rd3_msg.h"

namespace Ed3
{

/**
 *GestureMsg
 */
class UiMsgQueue : public Rd3::MessageQueueT<UiMessage>
{
private:	
	typedef Rd3::MessageQueueT<UiMessage> _BaseClass;

public:
	static sString TypePrefix()
	{
		return _S("UiMsgQueue:");
	}

	/**
	 *
	 */
	UiMsgQueue( Rd3::Render* owner, const sString& objectName ) :
		_BaseClass( owner, objectName )
	{
	}
};

}

#endif // _ED3_UI_MSGQ_INC_