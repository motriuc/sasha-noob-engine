// sne.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "sne.h"
#include "sne_app.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	SNEApplication app( hInstance );
	return app.Run();
}
