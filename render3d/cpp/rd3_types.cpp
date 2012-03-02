/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_types.cpp
//	Created                 : 20 1 2011   0:05
//	File path               : SLibF\render3d\cpp
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
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
#include "rd3afx.h"

using namespace System;

namespace Rd3 { 

//-------------------------------------------------------------------	
namespace RenderType
{

	const sChar* GetName( RenderType type )
	{
		__S_ASSERT( type >= 0 );
		__S_ASSERT( type < COUNT );
    
		static const sChar* names[] = {
			_S("DX9"),
			_S("DX10"),
			_S("OPENGL"),
			_S("EAGL")
		};

		return names[type];
	}
}

//-------------------------------------------------------------------
namespace ResourceType
{
	const sChar* GetPrefix( ResourceType type )
	{
		__S_ASSERT( type >= 0 );
		__S_ASSERT( type < COUNT );

		static sChar pStr[][3] = 
		{
			_S("vb"),
			_S("ib"),
			_S("tx"),
			_S("ef"),
			_S("mt"),
			_S("ft")
		};

		return pStr[type];
	}

	// 
	ResourceType GetType( const sString& name )
	{
		__S_ASSERT( sFalse );
		return UNKNOWN;
	}

}

//-------------------------------------------------------------------	
namespace TextureParameter
{
	TextureParameter GetType( const sChar* pChars )
	{
		for( sInt i = 0; i < COUNT; i++ )
		{
			if( Chars::CompareNoCase( GetName( (TextureParameter)i ), pChars ) == 0 )
				return (TextureParameter)i;
		}
		return UNKNOWN;
	}
}
	
//-------------------------------------------------------------------
namespace MatrixParameter
{
	MatrixParameter GetType( const sChar* pChars )
	{
		for( sInt i = 0; i < COUNT; i++ )
		{
			if( Chars::CompareNoCase( GetName( (MatrixParameter)i ), pChars ) == 0 )
				return (MatrixParameter)i;
		}
		return UNKNOWN;
	}
}

//-------------------------------------------------------------------	
namespace VectorParameter
{
	VectorParameter GetType( const sChar* pChars )
	{
		for( sInt i = 0; i < COUNT; i++ )
		{
			if( Chars::CompareNoCase( GetName( (VectorParameter)i ), pChars ) == 0 )
				return (VectorParameter)i;
		}
		return UNKNOWN;
	}
}

//-------------------------------------------------------------------	
namespace FloatParameter
{
	FloatParameter GetType( const sChar* pChars )
	{
		for( sInt i = 0; i < COUNT; i++ )
		{
			if( Chars::CompareNoCase( GetName( (FloatParameter)i ), pChars ) == 0 )
				return (FloatParameter)i;
		}
		return UNKNOWN;
	}
}

//-------------------------------------------------------------------	
namespace BoolParameter
{
	BoolParameter GetType( const sChar* pChars )
	{
		for( sInt i = 0; i < COUNT; i++ )
		{
			if( Chars::CompareNoCase( GetName( (BoolParameter)i ), pChars ) == 0 )
				return (BoolParameter)i;
		}
		return UNKNOWN;
	}
}

//-------------------------------------------------------------------
namespace AttributeParameter
{
	AttributeParameter GetType( const sChar* pChars )
	{
		for( sInt i = 0; i < COUNT; i++ )
		{
			if( Chars::CompareNoCase( GetName( (AttributeParameter)i ), pChars ) == 0 )
				return (AttributeParameter)i;
		}
		return UNKNOWN;
	}
}

//-------------------------------------------------------------------	
namespace TextureType 
{
	TextureType GetType( const sChar* pChars )
	{
		for( sInt i = 0; i < COUNT; i++ )
		{
			if( Chars::CompareNoCase( GetName( (TextureType)i ), pChars ) == 0 )
				return (TextureType)i;
		}
		return UNKNOWN;
	}
}

//-------------------------------------------------------------------
namespace  TextureFilteringType
{
	TextureFilteringType GetType( const sChar* pChars )
	{
		for( sInt i = 0; i < COUNT; i++ )
		{
			if( Chars::CompareNoCase( GetName( (TextureFilteringType)i ), pChars ) == 0 )
				return (TextureFilteringType)i;
		}
		return UNKNOWN;
	}
}

//-------------------------------------------------------------------
namespace TextureAddressingType
{
	TextureAddressingType GetType( const sChar* pChars )	
	{
		for( sInt i = 0; i < COUNT; i++ )
		{
			if( Chars::CompareNoCase( GetName( (TextureAddressingType)i ), pChars ) == 0 )
				return (TextureAddressingType)i;
		}
		return UNKNOWN;
	}
}
	
//-------------------------------------------------------------------
namespace VertexBufferStream
{
	Type GetType( const sChar* pChars )
	{
		Type typeList[] = 
		{
			E_XYZ,
			E_NORMAL,
			E_TX1,
			E_TX2
		};
		
		for( sInt i = 0; i < COUNT; i++ )
		{
			if( Chars::CompareNoCase( GetName( (Type)i ), pChars ) == 0 )
				return typeList[i];
		}
		return UNKNOWN;
	}
	
	Set GetTypeSet( const sString& typeSet )
	{
		Set set = UNKNOWN;
		
		sInt from = 0;
		sString split;
		
		while( typeSet.Split( _S('|'), from, split ) )
		{
			set |= GetType( split );
		}
		
		return set;
	}
}

//-------------------------------------------------------------------------------
} // Rd3 