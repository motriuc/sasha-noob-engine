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

#define _use_Files_
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
	_hInstance( 0 ),
	_pCmdParams( NULL )
{
#ifdef _SPL_WIN32

	// Get CommandLines
	SWCHAR* pCommandLine = ::GetCommandLineW();
	sInt count;

	SWCHAR** pCommands = CommandLineToArgvW( pCommandLine, &count );

	if( pCommands )
	{
		__S_ASSERT( count >= 1 );

		_fileName = Files::Name::GetFileName( pCommands[0] );
		_runPath =  Files::Name::GetFilePath( pCommands[0] );
 
		_iCmdCount = count - 1;

		if( _iCmdCount > 0 )
		{
			_pCmdParams = new sString[_iCmdCount];
			for( sInt i = 0; i < _iCmdCount; i++ )
				_pCmdParams[i] = pCommands[i+1];
		}
		::GlobalFree( pCommands );
	}
#endif	// _SPL_WIN32

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
const Types::sString& AppEnviroment::GetCommandLineArgument( Types::sInt i ) const
{
  __S_ASSERT( i >= 0 );
  __S_ASSERT( i < _iCmdCount );

  return _pCmdParams[i];
}

//------------------------------------------------------------------
AppEnviroment::~AppEnviroment()
{
	delete[] _pCmdParams;
}

}
