/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_ui_button.cpp
//  Created             : 20 3 2012
//  Author              : Motriuc Alexandru
//  File Path           : SLibF\engine3d\cpp\ui
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

#include "ed3afx.h"
#include "ed3_ui_button.h"

namespace Ed3
{
//-------------------------------------------------------------------
uiButton::uiButton( const sString& name ) :
	_BaseClass( name, sTrue ),
	_pressed( sFalse )
{
}

//-------------------------------------------------------------------
uiButton::~uiButton()
{
}

//-------------------------------------------------------------------
void uiButton::OnGestureEvent( Rd3::EngineData& edata, const Rd3::GestureEvent& e )
{
	if( e.Taps().Size() != 1 )
		return;

	d3Vector pos = e.Taps()[0].Position();
	if( e.GetType() == Rd3::GestureEvent::E_Begin )
	{
		d2Rectangle rect = GetRectangle();
		_pressed = rect.Intersect( d2Vector( pos.x, pos.y ) );
	}
	else if( e.GetType() == Rd3::GestureEvent::E_End )
	{
		d2Rectangle rect = GetRectangle();
		if( rect.Intersect( d2Vector( pos.x, pos.y ) ) )
		{
			if( GetUIQueue() )
			{
				UiMessage msg( UiMessage::eButton, UiMessage::eClick, this );
				GetUIQueue()->SendMessage( edata, msg );
			}
		}
		_pressed = sFalse;
	}
}

}