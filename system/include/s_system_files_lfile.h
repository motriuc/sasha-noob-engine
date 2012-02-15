/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_files_lfile.h
//	Created                 : 28 6 2007   17:51
//	File path               : SLibF\system\Include
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
 *	FileOpenMode
 */
namespace FileOpenMode
{
	/**
	 *	Specifies how the operating system should open a file
	 */
	enum FileOpenMode
	{
		/**
		 *	Specifies that the operating system should create a new file.
		 *	If the file already exists, it will be overwritten
		 */
		eCreate				= 0,

		/**
		 *	Specifies that the operating system should create a new file.
		 *	If the file already exists, an Error is generated.
		 */
		eCreateNew			,
		
		/**
		 *	Specifies that the operating system should open an existing file.
		 *	The ability to open the file is dependent on the the value specified 
		 *	by FileAccess. A Error is thrown if the file does not exist.
		 */
		eOpen				,

		/**
		 *	Specifies that the operating system should open a file if it exists; 
		 *	otherwise, a new file should be created.
		 */
		eOpenOrCreate		,

		/**
		 *	Opens the file if it exists and seeks to the end of the file, 
		 *	or creates a new file.
		 */
		eAppend,

		/**
		 *	Specifies that the operating system should open an existing file. 
		 *	Once opened, the file should be truncated so that its size is zero bytes.
		 */
		eTruncate,

		// 
		_PLATFORM COUNT
	};
}

/**
 *	FileAccessMode
 */
namespace FileAccessMode
{
	/**
	 *	Defines constants for read, write, or read/write access to a file.
	 */
	enum FileAccessMode
	{
		eRead		= 0,
		eWrite		,
		eReadWrite	,

		//
		_PLATFORM COUNT
	};
}

/**
 *	FileShareMode
 */
namespace FileShareMode
{
	/**
	 *	FileShareMode
	 */
	enum FileShareMode
	{
		eNone		= 0,
		eRead		,
		eWrite		,
		eReadWrite	,

		_PLATFORM COUNT
	};
}

/**
 *	Local system file class
 */
class LFile : private class_nocopy
{
public:
	/**
	 *	Constructor
	 */
	LFile();

	/**
	 *	Destructor
	 */
	~LFile();

	/**
	 *	open file
	 *	@param pFileName [in]
	 *	@return errors: FileOpenError
	 */
	 void Open( 
		const sChar* pFileName,
		FileOpenMode::FileOpenMode openMode = FileOpenMode::eOpen,
		FileAccessMode::FileAccessMode accessMode = FileAccessMode::eRead,
		FileShareMode::FileShareMode shareMode = FileShareMode::eRead
	) throws_error;

	/**
	 *	Close File
	 */
	void Close();

	/**
	 *	Read from file
	 *	@param pBuf [out]
	 *	@return read length
	 *	@return errors: FileReadError
	 */
	 sUInt Read( void* pBuf, sUInt uLength ) const throws_error;

	/**
	 *	Write to file
	 *	@param pBuf [in]
	 *	@return write length
	 *	@return errors: FileWriteError
	 */
	sUInt Write( const void* pBuf, sUInt uLength ) throws_error;

	/**
	 *	Return file Size
	 */
	sUInt Size() const;

	/**
	 *	Return file position
	 */
	sUInt Position() const;

	/**
	 *	Seek in file
	 */
	sUInt Seek( 
		sInt uPos, 
		SeekType::SeekType ePosType = SeekType::eFromBegin
	);

private:

#ifdef _SPL_WIN32
	HANDLE	_hFile;
#endif
	
#ifdef _SPL_MAC
	FILE*	_hFile;
#endif	
};