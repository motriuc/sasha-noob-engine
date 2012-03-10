/////////////////////////////////////////////////////////////////////
//  File Name               : sne_app.cpp
//  Created                 : 1 3 2012   
//  File path               : SLibF\windows\sne
//  Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
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

#include "stdafx.h"
#include "sne_app.h"
#include "rd3_create_rparam.h"
#include "rd3_render.h"
#include "ed3_engine.h"
#include "ed3_primitive_lua.h"
#include "dx9/dx9_conf.h"
#include "dx9/dx9_msg_keyboardq.h"

//------------------------------------------------------------------
static SNEApplication* _pWindowToCreate = NULL;
//------------------------------------------------------------------
SNEApplication::SNEApplication( HINSTANCE hInstance ) :
	_hWindow( 0 ),
	_hBaseWinProc( &DefWindowProc ),
	_pRender( NULL ),
	_pEngine( NULL ),
	_pKeyMessageQ( NULL ),
	_viewWidth( 640 ),
	_viewHeight( 480 )
{
	AppEnviroment& env = AppEnviroment::Instance();
	env.SetAppInstance( hInstance );
	
	// parse arg parameters
	sInt i = 0;
	while( i < env.GetCommandLineArgumentCount() )
	{
		sString param = env.GetCommandLineArgument( i );

		// 2 parameters flags
		if( i + 1 < env.GetCommandLineArgumentCount() )
		{
			if( param == _S("-w") )
			{
				_viewWidth = env.GetCommandLineArgument( i + 1 ).ToInt();
			}
			else if( param == _S("-h") )
			{
				_viewHeight = env.GetCommandLineArgument( i + 1 ).ToInt();
			}
			else
				--i;

			++i;
		}

		++i;
	}
}

//------------------------------------------------------------------
SNEApplication::~SNEApplication()
{
	if( _pKeyMessageQ )
	{
		_pKeyMessageQ->UnuseResource();
	}

	delete _pEngine;
	delete _pRender;
}

//------------------------------------------------------------------
void SNEApplication::OnCreateWindow()
{
	__S_ASSERT( _pRender == NULL );

	Rd3::DX9RenderCreateParams createParams( _hWindow );
	createParams.SetFromCommandLine();

	try
	{
		_pRender = Rd3::Render::CreateRender( createParams );
		_pKeyMessageQ = new Dx9KeyboardMsgQueue( _pRender, _S("engine.msg.key") );
		_pRender->AddMessageQueue( _pKeyMessageQ );

		_pEngine = new Ed3::d3Engine( _pRender );

		LoadWorld();
	}
	catch( Errors::Error* error )
	{
		Platform::ShowError( error->ToString() );
		delete error;
	}
}

//------------------------------------------------------------------
void SNEApplication::LoadWorld() throws_error
{
	if( AppEnviroment::Instance().GetCommandLineArgumentCount() < 1 )
	{
		error_throw_arg( Errors::StringError )
			_S("No world to load")
		);
	}
	
	sString fullPath = Files::Name::GetFullPath( AppEnviroment::Instance().GetCommandLineArgument( 0 ) );
	sString worldPath = Files::Name::GetFilePath( fullPath );
	sString name = Files::Name::GetFileName( fullPath );

	_pEngine->Archive().AddProvider( new Streams::FolderArchiveProvider( _S("loaded://"),  worldPath ) );
	_pEngine->Archive().SetNameAlias( _S("gameres"), _S("//loaded:/") );

	_pEngine->LoadWorld( _S("%gameres%/") + name  );
}

//------------------------------------------------------------------
void SNEApplication::RenderFrame()
{
	if( _pEngine != NULL )
		_pEngine->RenderFrame();
}

//------------------------------------------------------------------
int SNEApplication::Run()
{
	win_CreateSWindow();

	MSG msg;

	for(;;)
	{
		if( ::PeekMessage( &msg, NULL, 0,0, PM_NOREMOVE ) )
		{
			if( !::GetMessage( &msg, NULL, 0, 0 ) )
			{
				return msg.wParam;
			}

			::TranslateMessage( &msg );
			::DispatchMessage( &msg );
		}
		else
		{
			RenderFrame();
		}
	}

	return (int) msg.wParam;
}

//------------------------------------------------------------------
HWND SNEApplication::win_CreateSWindow()
{
	__S_ASSERT( _hWindow == 0 );

	sString className = _S("SNE-ENGINE-WINDOW-CLASS");

	WNDCLASSEX	wcex;

	if( !::GetClassInfoEx( AppEnviroment::Instance().GetAppInstance(), className, &wcex ) )
	{
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= (WNDPROC) win_StartWinProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= AppEnviroment::Instance().GetAppInstance();
		wcex.hIcon			= 0;
		wcex.hCursor		= LoadCursor( NULL, IDC_ARROW );
		wcex.hbrBackground	= NULL;
		wcex.lpszMenuName	= 0;
		wcex.lpszClassName	= className;
		wcex.hIconSm		= 0;
		wcex.cbSize			= sizeof(WNDCLASSEX);

		if( !::RegisterClassEx( &wcex ) )
			return NULL;
	}

	_pWindowToCreate = this;

	RECT rc = { 0, 0, _viewWidth, _viewHeight };
	::AdjustWindowRect( &rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE );

	sString caption = _S("sne-engine ") + sString::IntToString( _viewWidth ) + _S("x") + sString::IntToString( _viewHeight );

	HWND hWnd = ::CreateWindowEx(
		0,
		className,
		caption,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, 
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		0,
		AppEnviroment::Instance().GetAppInstance(),
		NULL
	);

	return hWnd;
}

//------------------------------------------------------------------
sBool SNEApplication::MainProc( UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& result )
{
	switch( uMsg )
	{
	case WM_CREATE:
		OnCreateWindow();
		break;
	case WM_SIZE:
		if( _pRender != NULL )
		{
			RECT rc;
			::GetClientRect( _hWindow, &rc );
			_pRender->WindowResized( d2Math::d2Vector( (d2Float)( rc.right - rc.left ), (d2Float)( rc.bottom - rc.top ) ) );
		}
		break;
	case WM_CLOSE:
		::PostQuitMessage( 0 );
		break;

	default:
		return sFalse;
	}
	return sTrue;
}

//------------------------------------------------------------------
LRESULT CALLBACK SNEApplication::win_StartWinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	__S_ASSERT( _pWindowToCreate != NULL );
	
	_pWindowToCreate->_hWindow = hWnd;
	AppEnviroment::Instance().SetMainWindowHandle( hWnd );

	::SetWindowLong( hWnd, GWL_USERDATA,(LONG) _pWindowToCreate );
	_pWindowToCreate = NULL;

	::SetWindowLong( hWnd, GWL_WNDPROC, (LONG) win_MainWinProc );

	return win_MainWinProc( hWnd, uMsg, wParam, lParam );
}

//------------------------------------------------------------------
LRESULT CALLBACK SNEApplication::win_MainWinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	SNEApplication* app = (SNEApplication*) GetWindowLong( hWnd, GWL_USERDATA );

	LRESULT result = 0;
	if( app->MainProc( uMsg, wParam, lParam, result ) )
		return result;

	__S_ASSERT( app != NULL );
	return ::CallWindowProc( app->_hBaseWinProc, hWnd, uMsg, wParam, lParam );
}
