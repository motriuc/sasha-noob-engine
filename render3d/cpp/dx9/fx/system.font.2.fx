/////////////////////////////////////////////////////////////////////
//  File Name               : system.texture.2.fx
//  Created                 : 23 3 2012  
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
float4 rd_color1;

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
	result.Position			= mul( v.Position, rd_worldviewprojection );
	result.Texture			= v.Texture;
	return result;
}

float4 PSNormal( VS_OUT v ) : COLOR
{
	float alpha = tex2D( LinearSampler, v.Texture ).x;
	return float4( rd_color1.xyz, alpha );
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
