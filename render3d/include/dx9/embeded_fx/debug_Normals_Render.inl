/////////////////////////////////////////////////////////////////////
//  File Name               : debug_Normals_Render.inl
//	Created                 : 20 1 2011   0:05
//	File path               : SLibF\render3d\include\dx9\embeded_fx
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//	Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      render shader for renderign normlas
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////


// Effect resource name: System.Debug.Fx.RenderNormals
sChar _debug_Render_Normals[] = _S("\
\
float4x4 WorldViewProjection<>; \
\
\
struct VSINPUT \
{\
  float4 Position : POSITION; \
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
	return float4( 1.0f, 1.0f, 0.0f, 1.0f ); \
} \
\
technique Default \n\
{ \
	pass p0 \n\
	{ \
		VertexShader = compile _S_VS_VERSION VSNormal(); \n\
 		PixelShader = compile _S_PS_VERSION PSNormal(); \n\
    \
	} \
} \
");
