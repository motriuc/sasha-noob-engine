/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_error_error.h
//  Created                 : 27 6 2007   20:12
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

// _use_sError_

/**
 *	Error class
 */
class Error : public Obj::Object, private class_nocopy
{
	_SLIB_RUNTIME( System::Errors, Error, System::Obj::Object )

protected:
	/**
	 *	
	 */
	Error( Error* pPrevError = NULL );

	/**
	 *
	 */
#ifdef _DEBUG
	Error( const sChar* file, sInt line, Error* pPrevError = NULL );
#endif

public:
	/**
	 *	
	 */
	virtual ~Error();

	/**
	 *	return full error
	 */
	virtual sString ToString()	const;

	/**
	 *	return error description
	 */
	virtual sString Description() const;

private:
	Error*	_pPrevError;

#ifdef _DEBUG
	_PLATFORM sInt			_line;
	_PLATFORM const sChar*	_file;				
#endif
};
