//  File Name               : dx9_msg_keyboardq.cpp
//  Created                 : 6 3 2012   19:58
//  File path               : SLibF\render3d\cpp\dx9
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

#include "dx9/dx9_conf.h"
#include "dx9/dx9_msg_gestureq.h"
#include "rd3_edata.h"

extern LPDIRECTINPUT8 GetDIDevice();

//------------------------------------------------------------------
Dx9GestureMsgQueue::Dx9GestureMsgQueue( Rd3::Render* owner, const sString& objectName, HWND hRenderWindow ) :
	_BaseClass( owner, objectName ),
	_pDIDevice( NULL ),
	_hRenderWindow( hRenderWindow )
{
	HRESULT hr = GetDIDevice()->CreateDevice( GUID_SysMouse, &_pDIDevice, NULL );

	if( FAILED( hr ) )
	{
		System::Platform::ShowWarning( _S("Can't initialize Mouse Direct Input device") );
	}

	if( _pDIDevice != NULL )
	{
		_pDIDevice->SetDataFormat( &c_dfDIMouse );
		__S_ASSERT( SUCCEEDED( hr ) );

		hr = _pDIDevice->SetCooperativeLevel( 
			AppEnviroment::Instance().GetMainWindowHandle(),
			DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
		);
		__S_ASSERT( SUCCEEDED( hr ) );
	}

	Memory::Set( &_prevState, 0, sizeof( DIMOUSESTATE ) );
}

//------------------------------------------------------------------
void Dx9GestureMsgQueue::ProcessMessages( Rd3::EngineData& edata )
{
	if( _pDIDevice == NULL )
		return;

	DIMOUSESTATE mouseState;

	HRESULT hr = _pDIDevice->GetDeviceState( sizeof(mouseState),(LPVOID)&mouseState );

	if( FAILED( hr ) )
	{
		_pDIDevice->Acquire();
	}
	else
	{
		if( Memory::Compare( &mouseState, &_prevState, sizeof( DIMOUSESTATE ) ) != 0  )
		{
			sDouble time = Platform::GetTickD();

			if( mouseState.rgbButtons[0] != _prevState.rgbButtons[0] )
			{
				if( mouseState.rgbButtons[0] > 0 )
				{
					Rd3::GestureEvent gvevent( Rd3::GestureEvent::E_Begin );
					gvevent.Add( Rd3::GestureTap( GetCursorPosition(), time ) );
					SendMessage( edata, gvevent );
				}
				else
				{
					Rd3::GestureEvent gvevent( Rd3::GestureEvent::E_End );
					gvevent.Add( Rd3::GestureTap( GetCursorPosition(), time ) );
					SendMessage( edata, gvevent );
				}
			}
			else
			{
				if( mouseState.rgbButtons[0] > 0 )
				{
					Rd3::GestureEvent gvevent( Rd3::GestureEvent::E_Move );
					gvevent.Add( Rd3::GestureTap( GetCursorPosition(), time ) );
					SendMessage( edata, gvevent );
				}
			}
		}

		_prevState = mouseState;
	}

}

//------------------------------------------------------------------
d3Vector Dx9GestureMsgQueue::GetCursorPosition()
{
	POINT pt;
	RECT rc;

	::GetCursorPos( &pt );

	::ScreenToClient( _hRenderWindow, &pt );
	::GetClientRect( _hRenderWindow, &rc );

	d3Float px = (d3Float)pt.x / ( rc.right - rc.left );
	d3Float py = (d3Float)pt.y / ( rc.bottom - rc.top );

	px = px * 2.0f - 1.0f;
	py = 1.0f - 2.0f*py;

	return d3Vector( px, py, 0.0f );
}

//------------------------------------------------------------------
Dx9GestureMsgQueue::~Dx9GestureMsgQueue()
{
	if( _pDIDevice )
		_pDIDevice->Release();
}

