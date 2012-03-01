/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_appenv.h
//  Created                 : 1 3 2012
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
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

/**
 * App run enviroment
 */
class AppEnviroment
{
public:
	static AppEnviroment& Instance();

	/**
	 * Get Run FileName
	 */
	const Types::sString& GetRunFileName() const                  { return _fileName; }

	/**
	 * Path to run
	 */
	const Types::sString& GetRunPath() const                      { return _runPath; }

	/**
	 * CMD line argument count
	 */
	Types::sInt GetCommandLineArgumentCount() const              { return _iCmdCount; }

	/**
	 * Get cmd argument
	 */
	const Types::sString& GetCommandLineArgument( Types::sInt i ) const;

	/**
	 * Destructor
	 */
	~AppEnviroment();

#ifdef _SPL_WIN32
	_PLATFORM HINSTANCE	GetAppInstance() const					{ __S_ASSERT( _hInstance != NULL ); return _hInstance; }
	_PLATFORM void SetAppInstance( HINSTANCE hInst );
#endif

private:
	Types::sString		_fileName;
	Types::sString		_runPath;
	Types::sInt			_iCmdCount;
	HINSTANCE			_hInstance;
private:
	AppEnviroment();
	AppEnviroment( const AppEnviroment& src );
	void operator = ( const AppEnviroment& src );
};
