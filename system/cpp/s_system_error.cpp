/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_error.cpp
//  Created                 : 27 6 2007   11:27
//  File path               : SLibF\system\Cpp
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//	Library                 : 
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

#define _use_sError_
#include "s_system.h"

namespace System { namespace Errors {

using namespace Types;

/*******************************************************************/
/* StringError                                                     */
/*******************************************************************/
	
//-------------------------------------------------------------------
StringError::StringError( Error* pPrevError, const sString& desc ) : 
	_BaseClass( pPrevError ),
	_desc( desc )
{

}

//-------------------------------------------------------------------
#ifdef _DEBUG
StringError::StringError( const sChar* file, sInt line, Error* pPrevError, const sString& desc ) :
	_BaseClass( file, line, pPrevError ),
	_desc( desc )
{
}
#endif // _DEBUG

//-------------------------------------------------------------------
sString StringError::Description() const
{
	return Format( _S("'{1}' {2}") ) % _desc % Error::Description();
}

/********************************************************************/
/* _SPL_WIN32                                                       */
/********************************************************************/

#ifdef _SPL_WIN32 

/********************************************************************/
/* Win32Error                                                       */
/********************************************************************/

//-------------------------------------------------------------------
Win32Error::Win32Error( Error* pPrevError ) :
	_BaseClass( pPrevError )
{
	_le = GetLastError();
}

//-------------------------------------------------------------------
#ifdef _DEBUG
Win32Error::Win32Error( const sChar* file, sInt line, Error* pPrevError ) : 
	_BaseClass( file, line, pPrevError )
{
	_le = GetLastError();
}

#endif // _DEBUG

//-------------------------------------------------------------------
sString Win32Error::Description() const
{
	sString ret( _S("Unknown error") );
	
	LPVOID lpMsgBuf;
	
	if ( ::FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			_le,
			MAKELANGID(	LANG_NEUTRAL, SUBLANG_DEFAULT ), // Default language
			(sChar*) &lpMsgBuf,
			0,
		NULL )
	)
	{
		ret = (sChar*)lpMsgBuf;
		::LocalFree( lpMsgBuf );
	}

	return ret + Error::Description();
}

/*******************************************************************/
/* HRESULTError                                                    */
/*******************************************************************/

//-------------------------------------------------------------------	
HRESULTError::HRESULTError( Error* pPrevError, HRESULT hr ) :
	_BaseClass( pPrevError ),
	_hr( hr )
{
}

//-------------------------------------------------------------------
sString HRESULTError::Description() const
{
	return Format( _S("hr:{1} {2}") ) % (sUInt)_hr % _BaseClass::Description();
}
	
//-------------------------------------------------------------------
#ifdef _DEBUG
HRESULTError::HRESULTError( const sChar* file, sInt line, Error* pPrevError, HRESULT hr ) :
	_BaseClass( file, line, pPrevError ),
	_hr( hr )
{
}
#endif // _DEBUG

#endif // _SPL_WIN32

}}