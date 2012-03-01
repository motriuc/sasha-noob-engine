/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_appenv.cpp
//  Created                 : 1 3 2012   22:25
//  File path               : SLibF\system\Cpp
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

#include "s_system.h"

namespace System
{
using namespace Types;

//------------------------------------------------------------------
AppEnviroment& AppEnviroment::Instance()
{
	static AppEnviroment env;
	return env;
}

//------------------------------------------------------------------
AppEnviroment::AppEnviroment() :
	_iCmdCount( 0 ),
	_hInstance( 0 )
{
}

#ifdef _SPL_WIN32

//------------------------------------------------------------------
void AppEnviroment::SetAppInstance( HINSTANCE hInst )
{
	__S_ASSERT( _hInstance == 0 );
	_hInstance = hInst;
}

#endif // _SPL_WIN32

//------------------------------------------------------------------
AppEnviroment::~AppEnviroment()
{
}

}
