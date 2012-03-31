/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_mem.inl
//  Created                 : 15 6 2007   22:07
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

inline void Copy( void* pDestination, const void* pSource, sUInt uCount )
{
	memcpy( pDestination, pSource, uCount );
}

inline void Set( void* pDestination, SBYTE ch, sUInt nCount )
{
	memset( pDestination, ch, nCount );
}

inline sInt Compare( const void* pA, const void* pB, sUInt uCount )
{
	return memcmp( pA, pB, uCount );
}

inline sUInt GetHashCode( const void* pBuf, sUInt nCount )
{
	return GetDWHashCode( pBuf, nCount );
}
