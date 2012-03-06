//  File Name               : dx9_msg_keyboardq.cpp
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

#include "rd3afx.h"

#include "dx9/dx9_conf.h"
#include "dx9/dx9_msg_keyboardq.h"

using namespace Rd3::KeyboardKeys;

/////////////////////////////////////////////////////////////////////
// DirectInputDevice
/////////////////////////////////////////////////////////////////////
class DirectInputDevice
{
public:
	DirectInputDevice() : _pDI( NULL )
	{
	}

	~DirectInputDevice()
	{
		if( _pDI )
		{
			_pDI->Release();
		}
	}

	LPDIRECTINPUT8 GetHandle()
	{
		if( _pDI == NULL ) 
		{
			HRESULT hr = ::DirectInput8Create(
				AppEnviroment::Instance().GetAppInstance(),
				DIRECTINPUT_VERSION,
				IID_IDirectInput8,
				(LPVOID*)&_pDI,
				NULL
			);

			if( FAILED( hr ) )
			{
				System::Platform::ShowError( _S("Can't initialize Direct input") );
			}
		}
		return _pDI;
	}

	LPDIRECTINPUT8 operator->()
	{
		return GetHandle();
	}
  
	static DirectInputDevice& Instance()
	{
		static DirectInputDevice gl_D3D;
		return gl_D3D;
	}

private:
	LPDIRECTINPUT8          _pDI;
};


/////////////////////////////////////////////////////////////////////
// DiKeys
/////////////////////////////////////////////////////////////////////
class DiKeys
{
public:
	DiKeys()
	{
		for( sInt i = 0; i < COUNT; i++ )
			_diKeys[i] = 0;

		// F keys
		_diKeys[E_F1]  = DIK_F1;
		_diKeys[E_F2]  = DIK_F2;
		_diKeys[E_F3]  = DIK_F3;
		_diKeys[E_F4]  = DIK_F4;
		_diKeys[E_F5]  = DIK_F5;
		_diKeys[E_F6]  = DIK_F6;
		_diKeys[E_F7]  = DIK_F7;
		_diKeys[E_F8]  = DIK_F8;
		_diKeys[E_F9]  = DIK_F9;
		_diKeys[E_F10] = DIK_F10;
		_diKeys[E_F11] = DIK_F11;
		_diKeys[E_F12] = DIK_F12;

		_diKeys[E_UP]    = DIK_UP;
		_diKeys[E_DOWN]  = DIK_DOWN;
		_diKeys[E_LEFT]  = DIK_LEFT;
		_diKeys[E_RIGHT] = DIK_RIGHT;

		_diKeys[E_PAGE_UP]     = DIK_PRIOR;
		_diKeys[E_PAGE_DOWN]   = DIK_NEXT;

		_diKeys[E_Q] = DIK_Q;
		_diKeys[E_W] = DIK_W;
		_diKeys[E_E] = DIK_E;
		_diKeys[E_R] = DIK_R;
		_diKeys[E_T] = DIK_T;
		_diKeys[E_Y] = DIK_Y;
		_diKeys[E_U] = DIK_U;
		_diKeys[E_I] = DIK_I;
		_diKeys[E_O] = DIK_O;
		_diKeys[E_P] = DIK_P;

		_diKeys[E_A] = DIK_A;
		_diKeys[E_S] = DIK_S;
		_diKeys[E_D] = DIK_D;
		_diKeys[E_F] = DIK_F;
		_diKeys[E_G] = DIK_G;
		_diKeys[E_H] = DIK_H;
		_diKeys[E_J] = DIK_J;
		_diKeys[E_K] = DIK_K;
		_diKeys[E_L] = DIK_L;

		_diKeys[E_Z] = DIK_Z;
		_diKeys[E_X] = DIK_X;
		_diKeys[E_C] = DIK_C;
		_diKeys[E_V] = DIK_V;
		_diKeys[E_B] = DIK_B;
		_diKeys[E_N] = DIK_N;
		_diKeys[E_M] = DIK_M;
    
		_diKeys[E_0] = DIK_0;
		_diKeys[E_1] = DIK_1;
		_diKeys[E_2] = DIK_2;
		_diKeys[E_3] = DIK_3;
		_diKeys[E_4] = DIK_4;
		_diKeys[E_5] = DIK_5;
		_diKeys[E_6] = DIK_6;
		_diKeys[E_7] = DIK_7;
		_diKeys[E_8] = DIK_8;
		_diKeys[E_9] = DIK_9;

		_diKeys[E_LEFT_CONTROL]  = DIK_LCONTROL;
		_diKeys[E_RIGHT_CONTROL] = DIK_RCONTROL;
    
		_diKeys[E_LEFT_ALT]      = DIK_LMENU;
		_diKeys[E_RIGHT_ALT]     = DIK_RMENU;
	}
  
	void TranslateFromDI( SBYTE* pKeys, const SBYTE* pDIKeys )
	{
		for( sInt i = 0; i < COUNT; i++ )
		{
			SBYTE v = _diKeys[i];
			if( v )
				pKeys[i] = pDIKeys[v];
		}
	}

private:
	SBYTE _diKeys[COUNT];
};

static DiKeys DIKeyCodes;

//------------------------------------------------------------------
Dx9KeyboardMsgQueue::Dx9KeyboardMsgQueue( Rd3::Render* owner, const sString& objectName ) :
	_BaseClass( owner, objectName )
{
	for( sInt i = 0; i < Rd3::KeyboardKeys::COUNT; ++i )
	{
		_keyPressed1[i] = 0;
		_keyPressed2[i] = 0;
	}

	_pKeyPressed = _keyPressed2;
	_pKeyPressedPrev = _keyPressed1;

	HRESULT hr = DirectInputDevice::Instance().GetHandle()->CreateDevice( GUID_SysKeyboard, &_pDIDevice, NULL );

	if( FAILED( hr ) )
    {
		System::Platform::ShowWarning( _S("Can't initialize Direct Input device") );
	}

	if( _pDIDevice )
	{
		hr = _pDIDevice->SetDataFormat( &c_dfDIKeyboard ); 
		__S_ASSERT( SUCCEEDED( hr ) );

		hr = _pDIDevice->SetCooperativeLevel( 
			AppEnviroment::Instance().GetMainWindowHandle(),
			DISCL_NONEXCLUSIVE | DISCL_FOREGROUND
		);
		__S_ASSERT( SUCCEEDED( hr ) );
	}
}

//------------------------------------------------------------------
void Dx9KeyboardMsgQueue::ProcessMessages( Rd3::EngineData& edata )
{
	if( _pDIDevice == NULL )
		return;
		
	SBYTE buffer[256];
	HRESULT hr = _pDIDevice->GetDeviceState( sizeof(buffer),(LPVOID)&buffer );

	if( FAILED( hr ) )
	{
		_pDIDevice->Acquire();
	}
	else
	{
		T::SwapValues( _pKeyPressed, _pKeyPressedPrev );

		DIKeyCodes.TranslateFromDI( _pKeyPressed, buffer );

		Rd3::KeyboardEvent keyEvent( _pKeyPressed, _pKeyPressedPrev );
		SendMessage( edata, keyEvent );
	}
}

//------------------------------------------------------------------
Dx9KeyboardMsgQueue::~Dx9KeyboardMsgQueue()
{
	if( _pDIDevice )
		_pDIDevice->Release();

}

