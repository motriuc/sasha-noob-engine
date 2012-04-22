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

class d3Object;

/**
 * UiMessage
 */
class UiMessage
{
public:
	enum Type
	{
		eButton		= 0,
		eEdit,
		eList,

		eCustom
	};

	enum Action
	{
		eClick			= 0,
		eTextChanged,
		eSelectionChanged,
		eAction
	};

	UiMessage() {}

	UiMessage( Type type, Action action, d3Object* from ) :
		_type( type ),
		_action( action ),
		_from( from )
	{
	}

	UiMessage( const sString& actionName, d3Object* from ) :
		_type( eCustom ),
		_action( eAction ),
		_actionName( actionName ),
		_from( from )
	{
	}

	Type GetType() const					{ return _type; }
	Action GetAction() const				{ return _action; }
	d3Object* Sender() const				{ return _from; }

	const sString& ActionName() const		{ return _actionName; }
private:
	Type		_type;
	Action		_action;
	d3Object*	_from;
	sString		_actionName;
};

}

#endif // _ED3_UI_MSG_INC_