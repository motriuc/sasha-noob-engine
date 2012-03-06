/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_msg_keyboardq.h
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

#include "rd3_msg_keyboardq.h"

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

/**
 * Dx9KeyboardMsgQueue
 */
class Dx9KeyboardMsgQueue : public Rd3::KeyboardMsgQueue
{
private:
	typedef Rd3::KeyboardMsgQueue _BaseClass;
public:

	Dx9KeyboardMsgQueue( Rd3::Render* owner, const sString& objectName );
	~Dx9KeyboardMsgQueue();

	virtual void ProcessMessages( Rd3::EngineData& edata );
private:
	LPDIRECTINPUTDEVICE8  _pDIDevice;
	SBYTE*                _pKeyPressed;
	SBYTE*				  _pKeyPressedPrev;
	SBYTE				  _keyPressed1[Rd3::KeyboardKeys::COUNT];
	SBYTE				  _keyPressed2[Rd3::KeyboardKeys::COUNT];
};