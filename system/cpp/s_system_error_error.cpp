/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_error_error.cpp
//  Created                 : 28 6 2007   16:03
//  File path               : SLibF\system\Cpp
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

#define _use_sError_
#include "s_system.h"

namespace System { namespace Errors {
	
using namespace Types;

//------------------------------------------------------------------
Error::Error( Error* pPrevError ) :
	_pPrevError( pPrevError )
#ifdef _DEBUG
	,_file( NULL ), _line( 0 )
#endif
{
	if( _pPrevError == this )
		_pPrevError = NULL;
}

//------------------------------------------------------------------
#ifdef _DEBUG

Error::Error( const sChar* file, sInt line,  Error* pPrevError ) :
	_pPrevError( pPrevError )
{
	_file = file;
	_line = line;

	if( _pPrevError == this )
		_pPrevError = NULL;
}

#endif
	
//------------------------------------------------------------------
sString Error::ToString()	const
{
	if( _pPrevError == NULL )
		return Description();

	return Format( _S("{1}[{2}]") ) % Description() % _pPrevError->ToString();
}
	
//------------------------------------------------------------------
sString Error::Description() const
{
#ifdef _DEBUG
	if( _file == NULL )
		return _S("");
	
	return Format( _S("@: {1}({2})") ) % _file % _line;
#else
	return _S("");
#endif
}

//------------------------------------------------------------------
Error::~Error()
{
	if( _pPrevError )
		delete _pPrevError;
}

}
}