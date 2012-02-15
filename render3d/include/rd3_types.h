/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_types.h
//	Created                 : 20 1 2011   0:05
//	File path               : SLibF\render3d\include
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
#ifndef _RD3_TYPE_H_
#define _RD3_TYPE_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif


namespace Rd3
{

using namespace System::Types;


/**
 * Vertex data list types
 */
typedef System::d3Math::d3VectorList	VertexPList;	 // position vertex list
typedef System::d3Math::d3VectorList	VertexNList;	 // normal vertex list
typedef System::Cnt::sVector<sRGBColor> VertexCList;	 // color param
typedef System::d3Math::d3IndexList		IndexList;		 // index list

typedef System::Cnt::sVector<System::d2Math::d2Vector>	VertexTxCoord; // texture coodinates

/**
 * Render Type
 */
namespace RenderType
{
	enum RenderType
	{
		E_DX9       = 0,
		E_DX10,
		E_OPENGL,
		E_EAGL,

		COUNT
	};
  
	const sChar* GetName( RenderType type );
};

/**
 * Resource types
 */
namespace ResourceType
{
	enum ResourceType
	{
		E_VERTEX_BUFFER    = 0,
		E_INDEX_BUFFER,
		E_TEXTURE,
		E_EFFECT,
		E_MATERIAL,
		E_FONT,
		E_MESSAGEQ,
		E_MESH,
	  
		COUNT,
		UNKNOWN
	};
  
	const sChar* GetPrefix( ResourceType type );

	ResourceType GetType( const sString& name );
}

/**
 * Vertex Buffer type
 */
namespace VertexBufferStream
{
	enum Type
	{
		E_XYZ		= 0x00000001,
		E_NORMAL	= 0x00000002,
		E_TX1		= 0x00000004,
		E_TX2		= 0x00000008,
		
		COUNT		= 4,
		UNKNOWN		= 0
	};
	
	typedef sUInt Set;
	
	inline const sChar* GetName( Type t )
	{
		__S_ASSERT( t >= 0 );
		__S_ASSERT( t < COUNT );
		
		static const sChar* pNames[] = 
		{
			_S("XYZ"),
			_S("NORMAL"),
			_S("TX1"),
			_S("TX2")
		};
		
		return pNames[t];
	}
	
	Type GetType( const sChar* pChars );
	Set GetTypeSet( const sString& typeSet );
}
	
/**
 * Texture Parameter
 */
namespace TextureParameter
{
	enum TextureParameter
	{
		E_TEX1 = 0,
		E_TEX2,
		E_TEX3,
		E_TEX4,
		E_TEX5,
		E_TEX6,
		E_TEX7,
		E_TEX8,
		E_NORMAL_MAP,
		E_HEIGHT_MAP,
		E_MASK,
		
		COUNT,
		UNKNOWN
	};

	inline const sChar* GetName( TextureParameter t )
	{
		__S_ASSERT( t >= 0 );
		__S_ASSERT( t < COUNT );

		static const sChar* pNames[] = 
		{
			_S("rd_tx1"),
			_S("rd_tx2"),
			_S("rd_tx3"),
			_S("rd_tx4"),
			_S("rd_tx5"),
			_S("rd_tx6"),
			_S("rd_tx7"),
			_S("rd_tx8"),
			_S("rd_normalMap"),
			_S("rd_heightMap"),
			_S("rd_smask")
		};

		return pNames[t];
	}

	TextureParameter GetType( const sChar* pChars );
}

/**
 * TextureFiltering
 */
namespace TextureFilteringType
{
	enum TextureFilteringType
	{
		E_NEAREST,
		E_LINIAR,
				
		COUNT,
		UNKNOWN
	};
	
	inline const sChar* GetName( TextureFilteringType t )
	{
		__S_ASSERT( t >= 0 );
		__S_ASSERT( t < COUNT );
		
		static const sChar* pNames[] = 
		{
			_S("nearest"),
			_S("liniar"),
		};
		
		return pNames[t];
	}
	
	TextureFilteringType GetType( const sChar* pChars );
}
	
/**
 * TextureAddressingType
 */
namespace TextureAddressingType
{
	enum TextureAddressingType
	{
		E_REPEAT,
		E_CLAMP,
		
		COUNT,
		UNKNOWN
	};
	
	inline const sChar* GetName( TextureAddressingType t )
	{
		__S_ASSERT( t >= 0 );
		__S_ASSERT( t < COUNT );
		
		static const sChar* pNames[] = 
		{
			_S("repeat"),
			_S("clamp"),
		};
		
		return pNames[t];
	}
	
	TextureAddressingType GetType( const sChar* pChars );	
}	
	
/**
 * Texture types
 */
namespace TextureType
{
	enum TextureType
	{
		E_IMAGE,		// Image texture
		E_ALPHA,

		COUNT,
		UNKNOWN
	};
	
	inline const sChar* GetName( TextureType t )
	{
		__S_ASSERT( t >= 0 );
		__S_ASSERT( t < COUNT );
		
		static const sChar* pNames[] = 
		{
			_S("image"),
			_S("alpha")
		};
		
		return pNames[t];
	}
	
	TextureType GetType( const sChar* pChars );	
}


/**
 * Matrix Parameter
 */
namespace MatrixParameter
{
	enum MatrixParameter
	{
		E_WORLD = 0,
		E_VIEW,
		E_PROJ,
		E_WORLD_VIEW,
		E_VIEW_PROJ,
		E_WORLD_VIEW_PROJ,
		E_WORLD_NORMAL,

		COUNT,
		UNKNOWN
	};

	inline const sChar* GetName( MatrixParameter p )
	{
		__S_ASSERT( p >= 0 );
		__S_ASSERT( p < COUNT );
    
		static const sChar* pNames[] = 
		{
			_S("rd_world"),
			_S("rd_view"),
			_S("rd_projection"),
			_S("rd_worldview"),
			_S("rd_viewprojection"),
			_S("rd_worldviewprojection"),
			_S("rd_worldnormal")
		};
		return pNames[p];
	}

	MatrixParameter GetType( const sChar* pChars );
}

/**
 * VectorParameter
 */
namespace VectorParameter
{
	enum VectorParameter
	{
		E_CAMERA_POS = 0,

		E_LIGHT1_POS,
		E_LIGHT2_POS,
		E_LIGHT3_POS,
		E_LIGHT4_POS,

		E_LIGHT1_DIR,
		E_LIGHT2_DIR,
		E_LIGHT3_DIR,
		E_LIGHT4_DIR,

		E_LIGHT1_DIFFUSE,
		E_LIGHT2_DIFFUSE,
		E_LIGHT3_DIFFUSE,
		E_LIGHT4_DIFFUSE,

		E_LIGHT1_SPECULAR,
		E_LIGHT2_SPECULAR,
		E_LIGHT3_SPECULAR,
		E_LIGHT4_SPECULAR,

		E_LIGHT1_AMBIENT,
		E_LIGHT2_AMBIENT,
		E_LIGHT3_AMBIENT,
		E_LIGHT4_AMBIENT,
		   
		E_COLOR1,
		E_COLOR2,
		
		COUNT,
		UNKNOWN
	};

	inline const sChar* GetName( VectorParameter p )
	{
		__S_ASSERT( p >= 0 );
		__S_ASSERT( p < COUNT );
    
		static const sChar* pNames[] = 
		{
			_S("rd_camera_position"),

			_S("rd_light1_pos"),
			_S("rd_light2_pos"),
			_S("rd_light3_pos"),
			_S("rd_light4_pos"),
      
			_S("rd_light1_dir"),
			_S("rd_light2_dir"),
			_S("rd_light3_dir"),
			_S("rd_light4_dir"),

			_S("rd_light1_diffuse"),
			_S("rd_light2_diffuse"),
			_S("rd_light3_diffuse"),
			_S("rd_light4_diffuse"),

			_S("rd_light1_specular"),
			_S("rd_light2_specular"),
			_S("rd_light3_specular"),
			_S("rd_light4_specular"),

			_S("rd_light1_ambient"),
			_S("rd_light2_ambient"),
			_S("rd_light3_ambient"),
			_S("rd_light4_ambient"),
			
			_S("rd_color1"),
			_S("rd_color2")
			
		};
		
		return pNames[p];

	}
	
	VectorParameter GetType( const sChar* pChars );
}

/**
 * float parameters
 */
namespace FloatParameter
{
	enum FloatParameter
	{
		// time
		E_TIME        = 0,
		E_DELTA_TIME,

		// light
		E_LIGHT1_ATENUATION,
		E_LIGHT2_ATENUATION,
		E_LIGHT3_ATENUATION,
		E_LIGHT4_ATENUATION,

		COUNT,
		UNKNOWN
	};

	inline const sChar* GetName( FloatParameter p )
	{
		__S_ASSERT( p >= 0 );
		__S_ASSERT( p < COUNT );
    
		static const sChar* pNames[] = 
		{
			_S("rd_time"),
			_S("rd_dtime"),

			_S("rd_light1_atenuation"),
			_S("rd_light2_atenuation"),
			_S("rd_light3_atenuation"),
			_S("rd_light4_atenuation")
		};
		return pNames[p];
	}

	FloatParameter GetType( const sChar* pChars );
}

/**
 * Bool Parameter
 */
namespace BoolParameter
{
	enum BoolParameter
	{
		// lights
		E_LIGHT1_ON   = 0,
		E_LIGHT2_ON   ,
		E_LIGHT3_ON   ,
		E_LIGHT4_ON   ,

		COUNT,
		UNKNOWN
	};

	inline const sChar* GetName( BoolParameter p )
	{
		__S_ASSERT( p >= 0 );
		__S_ASSERT( p < COUNT );
    
		static const sChar* pNames[] = 
		{
			_S("rd_light1on"),
			_S("rd_light2on"),
			_S("rd_light3on"),
			_S("rd_light4on"),
		};
		return pNames[p];
	}
	
	BoolParameter GetType( const sChar* pChars );
}
	
/**
 * AttributeParameter
 */
namespace AttributeParameter 
{
	enum AttributeParameter 
	{
		E_POSITION	= 0,
		E_NORMALS,
		E_COLOR_DIFUSE,
		E_TX1,
		E_TX2,
		
		COUNT,
		UNKNOWN
	};
	
	inline const sChar* GetName( AttributeParameter p )
	{
		__S_ASSERT( p >= 0 );
		__S_ASSERT( p < COUNT );
		
		static const sChar* pNames[] = 
		{
			_S("position"),
			_S("normals"),
			_S("color_diffuse"),
			_S("tx1"),
			_S("tx2"),
		};
		return pNames[p];
	}
	
	AttributeParameter GetType( const sChar* pChars );
}

/**
 *  PrimitiveType
 */
namespace PrimitiveType
{
	enum PrimitiveType
	{
		E_POINT_LIST = 0,
		E_LINE_LIST  ,
		E_LINE_STRIP,
		E_TRIANGLE_LIST,
		E_TRIANGLE_STRIP,
		E_TRIANGLE_FAN,

		COUNT,
		UNKNOWN
	};

	inline const sChar* GetName( PrimitiveType p )
	{
		__S_ASSERT( p >= 0 );
		__S_ASSERT( p < COUNT );
    
		static const sChar* pNames[] = 
		{
			_S("pointlist"),
			_S("linelist"),
			_S("linestrip"),
			_S("trianglelist"),
			_S("trianglestrip"),
			_S("trianglefan")
		};
		return pNames[p];
	}

	PrimitiveType GetType( const sChar* pChars );

	inline sInt GetNumberOfPrimitives( sInt count, PrimitiveType p )
	{
		__S_ASSERT( p >= 0 );
		__S_ASSERT( p < COUNT );

		static sInt _div[] = 
		{
			1,  // E_POINT_LIST
			2,  // E_LINE_LIST
			1,  // E_LINE_STRIP
			3,  // E_TRIANGLE_LIST
			1,  // E_TRIANGLE_STRIP
			1   // E_TRIANGLE_FAN
		};

		static sInt _add[] = 
		{
			0,  // E_POINT_LIST
			0,  // E_LINE_LIST
			-1, // E_LINE_STRIP
			0,  // E_TRIANGLE_LIST
			-2, // E_TRIANGLE_STRIP
			-2  // E_TRIANGLE_FAN
		};
		return count / _div[p] + _add[p];
	}
}

/**
 * LightType
 */
namespace LightType 
{
	enum LightType
	{
		E_NULL,
		E_POINT,
		
		COUNT,
		UNKNOWN
	};
}	
//
inline void RGBColorToVector( const sRGBColor c, System::d3Math::d3Vector& v )
{
	v.x = System::RGBColor::GetFloatR( c );
	v.y = System::RGBColor::GetFloatG( c );
	v.z = System::RGBColor::GetFloatB( c );
	v.w = System::RGBColor::GetFloatA( c );
}

	
namespace KeyboardKeys
{
	enum KeyboardKeys
	{
		E_F1        = 0,
		E_F2        ,
		E_F3        ,
		E_F4        ,
		E_F5        ,
		E_F6        ,
		E_F7        ,
		E_F8        ,
		E_F9        ,
		E_F10       ,
		E_F11       ,
		E_F12       ,
  
		E_0         ,
		E_1         ,
		E_2         ,
		E_3         ,
		E_4         ,
		E_5         ,
		E_6         ,
		E_7         ,
		E_8         ,
		E_9         ,

		E_UP        ,
		E_DOWN      ,
		E_LEFT      ,
		E_RIGHT     ,

		E_PAGE_UP,
		E_PAGE_DOWN,

		E_Q,
		E_W,
		E_E,
		E_R,
		E_T,
		E_Y,
		E_U,
		E_I,
		E_O,
		E_P,

		E_A,
		E_S,
		E_D,
		E_F,
		E_G,
		E_H,
		E_J,
		E_K,
		E_L,

		E_Z,
		E_X,
		E_C,
		E_V,
		E_B,
		E_N,
		E_M,

		E_LEFT_CONTROL,
		E_RIGHT_CONTROL,
  
		E_LEFT_ALT,
		E_RIGHT_ALT,

		COUNT
	};
}
	
/**
 * TextureParams
 */
class TextureParams
{
public:
	/**
	 *
	 */
	TextureParams();
	
	void SetMinFilter( TextureFilteringType::TextureFilteringType v );
	void SetMaxFilter( TextureFilteringType::TextureFilteringType v );
	void SetAddressU( TextureAddressingType::TextureAddressingType v );
	void SetAddressV( TextureAddressingType::TextureAddressingType v );
			
	TextureFilteringType::TextureFilteringType MinFilter() const;
	TextureFilteringType::TextureFilteringType MagFilter() const;
		
	TextureAddressingType::TextureAddressingType AddressU() const;
	TextureAddressingType::TextureAddressingType AddressV() const;
	
private:
	TextureFilteringType::TextureFilteringType		_minFilter;
	TextureFilteringType::TextureFilteringType		_magFilter;
	TextureAddressingType::TextureAddressingType	_addressU;
	TextureAddressingType::TextureAddressingType	_addressV;
};

#include "rd3_types.inl"
	
}

#endif // _RD3_TYPE_H_