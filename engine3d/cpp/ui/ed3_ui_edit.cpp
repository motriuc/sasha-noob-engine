/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_ui_edit.cpp
//  Created             : 1 4 2012
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
#include "ed3_ui_edit.h"
#include "ed3_edata.h"

#include "rd3_render.h"

namespace Ed3
{
//-------------------------------------------------------------------
uiEdit::uiEdit( const sString& name ) :
	_BaseClass( name, sTrue ),
	_text( _S("<Text>") ),
	_pressed( sFalse ),
	_textChanged( sFalse )
{
}

//-------------------------------------------------------------------
uiEdit::~uiEdit()
{
}

//-------------------------------------------------------------------
void uiEdit::Initialize( Rd3::Render& render ) throws_error
{
	_BaseClass::Initialize( render );
	
	if( !_uiFont )
		_uiFont = render.UseFont( _S("system.font.default") );
	
	_editService = render.GetService<Rd3::TextEditService>( _S("engine.service.textedit") );
}

//-------------------------------------------------------------------
void uiEdit::DeleteBack()
{
	if( _text.Length() > 0 )
	{
		_text = _text.SubString( 0, _text.Length() - 1 );
		_textChanged = sTrue;
	}
}
	
//-------------------------------------------------------------------
void uiEdit::AddText( const sString& text )
{
	_text += text;
	_textChanged = sTrue;
}

//-------------------------------------------------------------------
void uiEdit::AI( d3EngineData& edata )
{
	if( GetUIQueue() )
	{
		if( _textChanged )
		{
			UiMessage msg( UiMessage::eEdit, UiMessage::eTextChanged, this );
			GetUIQueue()->SendMessage( edata, msg );
			_textChanged = sFalse;
		}
	}
}
	
//-------------------------------------------------------------------
sBool uiEdit::LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	if( _BaseClass::LoadFromXMLSubnode( element, loadParams ) )
		return sTrue;

	return sFalse;
}

//-------------------------------------------------------------------
void uiEdit::Render2D( const d3RenderData& renderData )
{
	d2Vector textSize = _uiFont().GetTextSize( _text );

	d2Vector pos( - textSize.x / textSize.y, 1.0f );
	RenderText( _text, pos, 2.0f, _uiFontColor );
}

//-------------------------------------------------------------------
void uiEdit::OnGestureEvent( Rd3::EngineData& edata, const Rd3::GestureEvent& e )
{
	if( e.Taps().Size() != 1 )
		return;
		
	d3Vector pos = e.Taps()[0].Position();
	if( e.GetType() == Rd3::GestureEvent::E_Begin )
	{
		d2Rectangle rect = GetRectangle();
		_pressed = rect.Intersect( d2Vector( pos.x, pos.y ) );
		
		if( !_pressed && _editService )
		{
			_editService().EndEdit( this );
		}
			
	}
	else if( e.GetType() == Rd3::GestureEvent::E_End )
	{
		if( _pressed )
		{
			d2Rectangle rect = GetRectangle();
			if( rect.Intersect( d2Vector( pos.x, pos.y ) ) )
			{
				if( GetUIQueue() )
				{
					UiMessage msg( UiMessage::eEdit, UiMessage::eClick, this );
					GetUIQueue()->SendMessage( edata, msg );
				}
				
				if( _editService )
					_editService().BeginEdit( this );
			}
			_pressed = sFalse;
		}
	}
}	
	
}