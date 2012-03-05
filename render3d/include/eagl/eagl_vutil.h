/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_vutil.h
//  Created                 : 5 3 2012   13:05
//  File path               : SLibF\render3d\include\eagl
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
#ifndef _EAGL_VUTIL_INC_
#define _EAGL_VUTIL_INC_

#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

namespace VUtil
{

	//-------------------------------------------------------------------
	inline void AddVector( void*& pBuffer, const d3Vector& v )
	{
		GLfloat* pV = (GLfloat*)( pBuffer );
		
		*pV = v.x;		++pV; 
		*pV = v.y;		++pV; 
		*pV = v.z;		++pV; 
		
		pBuffer = pV;
	}
	
	//-------------------------------------------------------------------
	inline void AddVector( void*& pBuffer, const d2Vector& v )
	{
		GLfloat* pV = (GLfloat*)( pBuffer );
		
		*pV = v.x;		++pV; 
		*pV = v.y;		++pV; 
		
		pBuffer = pV;
	}
	
	//-------------------------------------------------------------------
	inline void AddTexCoord( void*& pBuffer, const d2Vector& v )
	{
		GLfloat* pV = (float*)( pBuffer );
		
		*pV = v.x;		++pV; 
		*pV = v.y;		++pV; 
		
		pBuffer = pV;
	}
	
	//-------------------------------------------------------------------
	inline void AddColor( void*& pBuffer, sRGBColor c )
	{
		GLubyte* pC = (GLubyte*)( pBuffer );
		
		*pC = RGBColor::GetByteR( c );  ++pC;
		*pC = RGBColor::GetByteG( c );  ++pC;
		*pC = RGBColor::GetByteB( c );  ++pC;
		*pC = RGBColor::GetByteA( c );  ++pC;
		
		pBuffer = pC;
	}
}

#endif // _EAGL_VUTIL_INC_

