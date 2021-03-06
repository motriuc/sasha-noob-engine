/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_stream_archive_provider_res.h
//  Created                 : 16 1 2012   13:01
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
 * ResourceArchiveProvider
 */
class ResourceArchiveProvider : public IStreamArchiveProvider
{
public:
	virtual sString GetProviderPrefix() const { return _S("res://"); }
	virtual IInputStream* Open( const sString& path ) throws_error;
	virtual const IInputStream* Open( const sString& path ) const throws_error;
	virtual sBool IsAvailable( const sString& path ) const;
};

/**
 * FolderArchiveProvider
 */
class FolderArchiveProvider : public IStreamArchiveProvider
{
public:
	FolderArchiveProvider( const sString& prefix, const sString& path );

	virtual sString GetProviderPrefix() const { return _prefix; }
	virtual IInputStream* Open( const sString& path ) throws_error;
	virtual const IInputStream* Open( const sString& path ) const throws_error;
	virtual sBool IsAvailable( const sString& path ) const;
private:
	sString _prefix;
	sString _path;
};