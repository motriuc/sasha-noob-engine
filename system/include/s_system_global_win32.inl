/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_global_win32.inl
//  Created                 : 28 6 2007   17:07
//  File path               : SLibF\system\Include
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

inline void ShowWarning( const sString& message )
{
	ShowWarning( message.c_str() );
}

inline void DebugWarning( const sString& message )
{
	DebugWarning( message.c_str() );
}

inline void ShowError( const sString& message )
{
	ShowError( message.c_str() );
}

inline void ShowMessage( const sString& message )
{
	ShowMessage(  message.c_str() );
}

inline void ShowWarning( const sChar* pMessage )
{
	::MessageBox( NULL, pMessage, _S("Warning"), MB_OK | MB_ICONWARNING );
}

inline void DebugWarning( const sChar* pMessage )
{
	::OutputDebugString( _S("SLIB-Warning : ") + sString( pMessage ) + _S("\n") );
}

inline void ShowError( const sChar* pMessage )
{
	::MessageBox( NULL, pMessage, _S("Error"), MB_OK | MB_ICONERROR );
}

inline void ShowMessage( const sChar* pMessage )
{
	::MessageBox( NULL, pMessage, _S("Info"), MB_OK | MB_ICONINFORMATION );
}

inline sUInt GetTick()
{
	return ::GetTickCount();
}

inline sDouble GetTickD()
{
	static sDouble delta = 0.0;

	LARGE_INTEGER lInt;
	static LARGE_INTEGER base;

	if( delta == 0.0 )
	{
		__S_VERIFY( QueryPerformanceFrequency( &lInt ) );
		QueryPerformanceCounter( &base );
		delta = (sDouble)lInt.QuadPart;
	}

	__S_VERIFY( QueryPerformanceCounter( &lInt ) );
	sDouble r =  (lInt.QuadPart - base.QuadPart ) / delta;

	return r;
}

inline void Exit( sInt returnCode )
{
	::ExitProcess( returnCode );
}
