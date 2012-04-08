/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_ui_msg.h
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
#ifndef _ED3_UI_MSG_INC_
#define _ED3_UI_MSG_INC_

namespace Ed3
{

class d2Object;

/**
 * UiMessage
 */
class UiMessage
{
public:
	enum Type
	{
		eButton		= 0,
		eEdit
	};

	enum Action
	{
		eClick			= 0,
		eTextChanged
	};

	UiMessage() {}

	UiMessage( Type type, Action action, d2Object* from ) :
		_type( type ),
		_action( action ),
		_from( from )
	{
	}

	Type GetType() const		{ return _type; }
	Action GetAction() const	{ return _action; }
	d2Object* Sender() const	{ return _from; }
private:
	Type		_type;
	Action		_action;
	d2Object*	_from;
};

}

#endif // _ED3_UI_MSG_INC_