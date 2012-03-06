/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_msg_keyboard.h
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
#ifndef _RD3_MSG_KEYBOARD_INC_
#define _RD3_MSG_KEYBOARD_INC_

namespace Rd3
{

/**
 * keyboard keys
 */
namespace KeyboardKeys
{
	enum KeyboardKeys
	{
		E_F1        = 0,
		E_F2        ,
		E_F3        ,
		E_F4        ,
		E_F5        ,
		E_F6        ,
		E_F7        ,
		E_F8        ,
		E_F9        ,
		E_F10       ,
		E_F11       ,
		E_F12       ,
  
		E_0         ,
		E_1         ,
		E_2         ,
		E_3         ,
		E_4         ,
		E_5         ,
		E_6         ,
		E_7         ,
		E_8         ,
		E_9         ,

		E_UP        ,
		E_DOWN      ,
		E_LEFT      ,
		E_RIGHT     ,

		E_PAGE_UP,
		E_PAGE_DOWN,

		E_Q,
		E_W,
		E_E,
		E_R,
		E_T,
		E_Y,
		E_U,
		E_I,
		E_O,
		E_P,

		E_A,
		E_S,
		E_D,
		E_F,
		E_G,
		E_H,
		E_J,
		E_K,
		E_L,

		E_Z,
		E_X,
		E_C,
		E_V,
		E_B,
		E_N,
		E_M,

		E_LEFT_CONTROL,
		E_RIGHT_CONTROL,
  
		E_LEFT_ALT,
		E_RIGHT_ALT,

		COUNT
	};
}

/**
 * KeyboardEvent
 */
class KeyboardEvent
{
public:
	KeyboardEvent( const SBYTE* pressedKeys, const SBYTE* pressedKeysPrev ) :
		_pressedKeys( pressedKeys ),
		_pressedKeysPrev( pressedKeysPrev )
	{
		__S_ASSERT( _pressedKeys != NULL );
		__S_ASSERT( _pressedKeysPrev != NULL );
	}

	sBool IsKeyPressed( Rd3::KeyboardKeys::KeyboardKeys key ) const
	{
		return _pressedKeys[key] != 0;
	}

	sBool IsKeyJustPressed( Rd3::KeyboardKeys::KeyboardKeys key ) const
	{
		return _pressedKeys[key] != 0 && _pressedKeysPrev[key] == 0;
	}

private:
	const SBYTE*  _pressedKeys;  
	const SBYTE*  _pressedKeysPrev;
};

}

#endif // _RD3_MSG_KEYBOARD_INC_