/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_vutil.h
//  Created                 : 21 1 2011   13:05
//  File path               : SLibF\render3d\include\dx9
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
#ifndef _DX9_VUTIL_INC_
#define _DX9_VUTIL_INC_

#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

namespace VUtil
{

//-------------------------------------------------------------------
inline void AddVector( void*& pBuffer, const System::d3Math::d3Vector& v )
{
	float* pV = (float*)( pBuffer );

	*pV = v.x;		++pV; 
	*pV = v.y;		++pV; 
	*pV = v.z;		++pV; 

	pBuffer = pV;
}

//-------------------------------------------------------------------
inline void AddVector( void*& pBuffer, const System::d2Math::d2Vector& v )
{
	float* pV = (float*)( pBuffer );

	*pV = v.x;		++pV; 
	*pV = v.y;		++pV; 

	pBuffer = pV;
}

//-------------------------------------------------------------------
inline void AddTexCoord( void*& pBuffer, const System::d2Math::d2Vector& v )
{
	float* pV = (float*)( pBuffer );

	*pV = v.x;		++pV; 
	*pV = v.y;		++pV; 

	pBuffer = pV;
}

//-------------------------------------------------------------------
inline void AddColor( void*& pBuffer, sRGBColor c )
{
	DWORD* pDW = (DWORD*)(pBuffer);

	*pDW = c;		++pDW;

	pBuffer = pDW;
}

}

#endif // _DX9_VUTIL_INC_

