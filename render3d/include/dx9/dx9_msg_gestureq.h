/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_msg_gestureq.h
//  Created                 : 12 3 2012
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
 * Dx9GestureMsgQueue
 */
class Dx9GestureMsgQueue : public Rd3::GestureMsgQueue
{
private:
	typedef Rd3::GestureMsgQueue _BaseClass;
public:
	Dx9GestureMsgQueue( Rd3::Render* owner, const sString& objectName, HWND hRenderWindow );

	~Dx9GestureMsgQueue();
	virtual void ProcessMessages( Rd3::EngineData& edata );
private:
	LPDIRECTINPUTDEVICE8  _pDIDevice;
	DIMOUSESTATE	_prevState;
	HWND			_hRenderWindow;

	d3Vector		GetCursorPosition();
};

