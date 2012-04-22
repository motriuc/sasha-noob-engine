/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_ui_button.h
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

#ifndef _ED3_UI_BUTTON_INC_
#define _ED3_UI_BUTTON_INC_

#include "ed3_object_d2.h"

namespace Ed3
{

/**
 * uiButton
 */
class uiButton : public d2Object
{
	_SLIB_RUNTIME( Ed3, uiButton, d2Object )
public:
	/**
	 *
	 */
	uiButton( const sString& name  );

	/**
	 *
	 */
	~uiButton();

	/**
	 *
	 */
	sBool IsUp() const { return _pressed; }
protected:
	virtual void OnGestureEvent( Rd3::EngineData& edata, const Rd3::GestureEvent& e );
	
private:
	sBool	_pressed;
};

}

#endif // _ED3_UI_BUTTON_INC_