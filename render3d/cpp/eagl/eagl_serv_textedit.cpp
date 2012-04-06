/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_serv_textedit.cpp
//  Created                 : 1 4 2012   19:58
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

#include "rd3afx.h"
#include "eagl_conf.h"
#include "eagl_serv_textedit.h"
#include "eagl_render.h"

//-------------------------------------------------------------------
EAGLTextEditService::EAGLTextEditService( Rd3::Render* pRender, const sString& objectName ) :
	_BaseClass( pRender, objectName ),
	_pCurrentTextEdit( NULL ),
	_backDeleteCount( 0 )
{
}

//-------------------------------------------------------------------
void EAGLTextEditService::BeginEdit( Rd3::ITextEdit* pEdit )
{
	_pCurrentTextEdit = pEdit;

	EAGLRender* pRender = reinterpret_cast<EAGLRender*>( GetOwner() );
	
	pRender->SoftwareKeyboard_Show();
	
}

//-------------------------------------------------------------------
void EAGLTextEditService::AddText( const sString& text )
{
	_text += text;
}

//-------------------------------------------------------------------
void EAGLTextEditService::Process( Rd3::EngineData& edata )
{
	if( _pCurrentTextEdit )
	{
		if( _backDeleteCount > 0 )
		{
			for( sInt i = 0; i < _backDeleteCount; ++i )
				_pCurrentTextEdit->DeleteBack();
			
			_backDeleteCount = 0;
		}
		
		if( _text.Length() > 0 )
		{
			_pCurrentTextEdit->AddText( _text );
			_text = _S("");
		}
	}
}

//-------------------------------------------------------------------
void EAGLTextEditService::DeleteBack()
{
	if( _text.Length() <= 0 )
	{
		_backDeleteCount++;
	}
	else 
	{
		_text = _text.SubString( 0,  _text.Length() - 1 );
	}
}

//-------------------------------------------------------------------
void EAGLTextEditService::EndEdit( Rd3::ITextEdit* pEdit )
{
	if( _pCurrentTextEdit == pEdit )
	{
		
		EAGLRender* pRender = reinterpret_cast<EAGLRender*>( GetOwner() );
		pRender->SoftwareKeyboard_Hide();
		_pCurrentTextEdit = NULL;
	}
}
