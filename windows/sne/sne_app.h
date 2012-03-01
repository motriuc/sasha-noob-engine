/////////////////////////////////////////////////////////////////////
//  File Name               : sne_app.h
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
#pragma once

namespace Ed3
{
	class d3Engine;
}

/**
 * SNEApplication
 */
class SNEApplication
{
public:
	SNEApplication( HINSTANCE hInstance );
	~SNEApplication();

	int Run();
protected:
	void OnCreateWindow();
	void RenderFrame();
private:
	HWND win_CreateSWindow();

	sBool MainProc( UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& result );

	static LRESULT CALLBACK win_StartWinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	static LRESULT CALLBACK win_MainWinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
private:
	HWND		_hWindow;
	WNDPROC		_hBaseWinProc;

	Rd3::Render*	_pRender;
	Ed3::d3Engine*	_pEngine;
};