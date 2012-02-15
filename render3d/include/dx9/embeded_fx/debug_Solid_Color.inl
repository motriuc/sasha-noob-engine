/////////////////////////////////////////////////////////////////////
//  File Name               : debug_Solid_Color.inl
//	Created                 : 20 1 2011   0:05
//	File path               : SLibF\render3d\include\dx9\embeded_fx
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//	Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      Solid render shader for debug purposes
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////


// Effect resource name: System.Debug.Fx.SolidVertexDiffuzeColor
sChar _debug_SolidColor[] = _S("\
\
float4x4 WorldViewProjection<>; \
\
\
struct VSINPUT \
{\
  float4 Position : POSITION; \
  float4 Diffuze  : COLOR0; \
}; \
\
VSINPUT VSNormal( VSINPUT v ) \
{ \
	v.Position = mul( v.Position, WorldViewProjection ); \
	return v; \
} \
\
float4 PSNormal( VSINPUT v ) : COLOR \
{ \
	return v.Diffuze; \
} \
\
technique Default \
{ \
	pass p0 \
	{ \
		VertexShader = compile _S_VS_VERSION VSNormal(); \
    \n\
    #ifdef _S_PS_VERSION \n\
		PixelShader = compile _S_PS_VERSION PSNormal(); \n\
    #endif \n\
    \
	} \
} \
");