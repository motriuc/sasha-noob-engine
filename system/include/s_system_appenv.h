/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_appenv.h
//  Created                 : 1 3 2012
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

/**
 * App run enviroment
 */
class AppEnviroment : private class_nocopy
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

	_PLATFORM HWND GetMainWindowHandle() const						{ return _hMainWindow; }
	_PLATFORM void SetMainWindowHandle( HWND hWnd )					{ _hMainWindow = hWnd; }
#endif

private:
	Types::sString		_fileName;
	Types::sString		_runPath;
	Types::sInt			_iCmdCount;
	Types::sString*		_pCmdParams;	
#ifdef _SPL_WIN32
	HINSTANCE			_hInstance;
	HWND				_hMainWindow;
#endif 	
private:
	AppEnviroment();
};
