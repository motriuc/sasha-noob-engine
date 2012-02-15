/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_error_strerr.h
//	Created                 : 27 6 2007   20:15
//	File path               : SLibF\system\include
//	Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
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

/**
 *	String error
 */
class StringError : public Error
{
	_SLIB_RUNTIME( System::Errors, StringError, System::Errors::Error )
public:
	explicit StringError( Error* pPrevError = NULL, const sString& desc = _S("")  );

#ifdef _DEBUG
	StringError( const sChar* file, sInt line, Error* pPrevError = NULL, const sString& desc = _S("") );
#endif

	virtual sString Description() const;
private:
	sString _desc;
};
