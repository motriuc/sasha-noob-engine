/////////////////////////////////////////////////////////////////////
//  File Name               : system.d2.texture.1.fx
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

float4x4 rd_d2view;
float4	 rd_color_diffuse;

texture2D rd_tx1<>;

sampler LinearSampler =
sampler_state
{
    Texture = <rd_tx1>;
    MinFilter = Point;
    MagFilter = Point; 
};

struct VS_IN
{
	float4 Position	: POSITION;
	float2 Texture	: TEXCOORD0;
};

struct VS_OUT
{
	float4 Position			: POSITION;
	float2 Texture			: TEXCOORD0;
};

VS_OUT VSNormal( VS_IN v )
{
	VS_OUT result; 
	result.Position			= mul( v.Position, rd_d2view );
	result.Texture			= v.Texture;
	return result;
}

float4 PSNormal( VS_OUT v ) : COLOR
{
	float4 txColor = tex2D( LinearSampler, v.Texture );
	return txColor * rd_color_diffuse;
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
