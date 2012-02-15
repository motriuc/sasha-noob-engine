/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_error_win32hresult.h
//  Created                 : 25 8 2007   11:22
//  File path               : SLibF\system\Include
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

// _use_sError_


class HRESULTError : public Error
{
	_SLIB_RUNTIME( System::Errors, HRESULTError, System::Errors::Error )
public:

	/**
	 *	
	 */
	HRESULTError( Error* pPrevError = NULL, HRESULT hr = 0 );

#ifdef _DEBUG
	/**
	 *	Debug constructor
	 */
	HRESULTError( const sChar* file, sInt line, Error* pPrevError = NULL, HRESULT hr = 0 );
#endif

	/**
	 *	
	 */
	virtual sString Description() const;
private:
	HRESULT _hr;
};

