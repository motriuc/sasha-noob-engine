/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_error_win32err.h
//	Created                 : 27 6 2007   20:14
//	File path               : SLibF\system\Include
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//	Library                 : 
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

// _use_sError_

/**
 *	Win32 Error
 */
class Win32Error : public Error
{
	_SLIB_RUNTIME( System::Errors, Win32Error, System::Errors::Error )
public:

	/**
	 *	
	 */
	Win32Error( Error* pPrevError = NULL );

#ifdef _DEBUG
	/**
	 *	Debug constructor
	 */
	Win32Error( const sChar* file, sInt line, Error* pPrevError = NULL );
#endif

	/**
	 *	
	 */
	virtual sString Description() const;
private:
	SDWORD _le;
};
