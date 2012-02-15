/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_stream_archive.cpp
//  Created                 : 16 1 2012   13:01
//  File path               : SLibF\system\Cpp
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

#define _use_Streams_

#include "s_system.h"

namespace System
{
namespace Streams
{

const sChar* rootPrefix = _S("//");
const sChar AliasChar	= _S('%');
	
//------------------------------------------------------------------------------------
sBool StreamArchive::IsPathFromRoot( const sString& path )
{
	return path.BeginsWith( rootPrefix );
}

//------------------------------------------------------------------------------------
sString StreamArchive::PathRemoveProvider( const sString& path, const sString& providerName )
{
	return path.SubString( Chars::Length( rootPrefix ) + providerName.Length() );
}

//------------------------------------------------------------------------------------
void StreamArchive::AddProvider( IStreamArchiveProvider* provider )
{
	__S_ASSERT( provider != NULL );
	__S_ASSERT( FindProviderFor( provider->GetProviderPrefix() ) == NULL );

	_providers.Add( provider );
}

//------------------------------------------------------------------------------------
const IStreamArchiveProvider* StreamArchive::FindProviderFor( const sString& path ) const
{
	for( int i = 0; i < _providers.Size(); i++ )
	{
		IStreamArchiveProvider* provider = _providers[i];

		if( path.BeginsWith( rootPrefix + provider->GetProviderPrefix() ) )
			return provider;
	}

	return NULL;
}

//------------------------------------------------------------------------------------
const IInputStream* StreamArchive::Open( const sString& path ) const throws_error
{
	sString thePath = ParseNameAliases( path );
	
	if( IsPathFromRoot( thePath ) )
		return OpenFromFullPath( thePath );

	for( int i = _paths.Size() - 1; i >= 0; --i )
	{
		sString fullpath = _paths[i] + thePath;
		const IStreamArchiveProvider* provider = FindProviderFor( fullpath );

		if( provider == NULL )
			continue;

		sString provpath = PathRemoveProvider( fullpath, provider->GetProviderPrefix() );

		if( provider->IsAvailable( provpath ) )
			return provider->Open( provpath );
	}

	error_throw_arg( StreamNotFoundError )
		thePath
	);
}

//------------------------------------------------------------------------------------
IInputStream* StreamArchive::Open( const sString& path ) throws_error
{
	return const_cast<IInputStream*>(
		const_cast<const StreamArchive*>( this )->Open( path )
	);
}
	
//------------------------------------------------------------------------------------
const IInputStream* StreamArchive::OpenFromFullPath( const sString& path ) const throws_error
{
	const IStreamArchiveProvider* provider = FindProviderFor( path );
	if( provider == NULL )
		error_throw_arg( StreamNotFoundError )
			path
		);

	return provider->Open( PathRemoveProvider( path, provider->GetProviderPrefix() ) );
}

//------------------------------------------------------------------------------------
void StreamArchive::SetNameAlias( const sString& alias, const sString& name )
{
	_nameAlias.Add( alias, name );
}
	
//------------------------------------------------------------------------------------
sString StreamArchive::ParseNameAliases( const sString& path ) const
{
	sInt pos = 0;
	sString ret;
	
	for(;;)
	{
		sInt sp1 = path.Find( pos, AliasChar );
		if ( sp1 < 0 )
		{
			ret += path.SubString( pos );
			break;
		}
		
		sInt sp2 = path.Find( sp1+1, AliasChar );
		
		if( sp2 < 0 )
		{
			ret += path.SubString( pos );
			break;
		}
		
		sString replaceString;
		
		if ( sp2 - sp1 > 1 )
		{
			sString alias = path.SubString( sp1 + 1, sp2 - sp1 - 1 );
			
			_nameAlias.Lookup( alias, replaceString );
		}
		else
			replaceString = AliasChar;
		
		ret += path.SubString( pos, sp1 - pos );
		ret += replaceString;
		
		pos = sp2 + 1;
	}
	
	return ret;
}
	
	
//------------------------------------------------------------------------------------
StreamArchive::~StreamArchive()
{
	for( int i = 0; i < _providers.Size(); i++ )
		delete _providers[i];
}

}
}
