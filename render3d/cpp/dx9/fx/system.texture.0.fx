/////////////////////////////////////////////////////////////////////
//  File Name               : system.texture.0.fx
//  Created                 : 11 3 2012
//  File path               : SLibF\render3d\cpp\dx9\fx
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

float4x4 rd_worldviewprojection<>;

float material_coef_ambient;

texture2D rd_tx1<>;

sampler LinearSampler =
sampler_state
{
    Texture = <rd_tx1>;
    MinFilter = Linear;
    MagFilter = Linear; 
};

struct VS_IN
{
	float4 Position			: POSITION;
	float2 vObjectTexture	: TEXCOORD0;
};

struct VS_OUT
{
	float4 Position			: POSITION;
	float2 vTex				: TEXCOORD0;
};

VS_OUT VSNormal( VS_IN v )
{
	VS_OUT result; 
	result.Position			= mul( v.Position, rd_worldviewprojection );
	result.vTex				= v.vObjectTexture;
	return result;
}

float4 PSNormal( VS_OUT v ) : COLOR
{
	float4 color = tex2D( LinearSampler, v.vTex );
	return saturate( color * material_coef_ambient );
}

technique Default
{
	pass p0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;

		VertexShader = compile _S_VS_VERSION VSNormal();
 		PixelShader = compile _S_PS_VERSION PSNormal();
	}
}
