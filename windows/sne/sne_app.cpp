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

//------------------------------------------------------------------
static SNEApplication* _pWindowToCreate = NULL;
//------------------------------------------------------------------
SNEApplication::SNEApplication( HINSTANCE hInstance ) :
	_hWindow( 0 ),
	_hBaseWinProc( &DefWindowProc ),
	_pRender( NULL )
{
	AppEnviroment::Instance().SetAppInstance( hInstance );
}

//------------------------------------------------------------------
SNEApplication::~SNEApplication()
{
	delete _pEngine;
	delete _pRender;
}

//------------------------------------------------------------------
void SNEApplication::OnCreateWindow()
{
	__S_ASSERT( _pRender == NULL );

	Rd3::DX9RenderCreateParams createParams( _hWindow );

	try
	{
		_pRender = Rd3::Render::CreateRender( createParams );
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
			// do idle
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

	HWND hWnd = ::CreateWindowEx(
		0,
		className,
		_S("sne-engine"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT ,
		CW_USEDEFAULT ,
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
