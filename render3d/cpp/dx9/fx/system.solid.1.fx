/////////////////////////////////////////////////////////////////////
//  File Name               : system.solid.1.fx
//  Created                 : 9 3 2012
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
float4x4 rd_world;
float4x4 rd_worldnormal;

float material_coef_diffuse;
float material_coef_phong;
float material_coef_phong_exp;
float material_coef_ambient;

float4 rd_light1_pos;
float4 rd_camera_position;
float4 rd_light1_specular;
float4 rd_light1_diffuse;
float4 rd_light1_ambient;

float4 rd_color_specular;
float4 rd_color_diffuse;
float4 rd_color_ambient;

struct VS_IN
{
	float4 Position			: POSITION;
	float4 vObjectNormal	: NORMAL;
	float2 vObjectTexture	: TEXCOORD0;
};

struct VS_OUT
{
	float4 Position			: POSITION;
	float3 vObjectNormal	: NORMAL;
	float3 vPosWorld		: TEXCOORD0;
	float2 vTex				: TEXCOORD1;
};

VS_OUT VSNormal( VS_IN v )
{
	VS_OUT result; 
	result.Position			= mul( v.Position, rd_worldviewprojection );
	result.vObjectNormal	= normalize( mul( v.vObjectNormal, rd_worldnormal ).xyz );
	result.vPosWorld		= mul( v.Position, rd_world ).xyz;
	result.vTex				= v.vObjectTexture;
	return result;
}

float4 PSNormal( VS_OUT v ) : COLOR
{
	float3 vLightToPoint = normalize( v.vPosWorld - rd_light1_pos.xyz );
	float fDifColor = dot( v.vObjectNormal, -vLightToPoint ) * material_coef_diffuse;

	// specular
	float3 vPointToCamera = normalize( rd_camera_position.xyz -  v.vPosWorld );
	float3 vReflection = reflect( vLightToPoint, v.vObjectNormal );
	float fPhongValue = saturate( dot( vReflection, vPointToCamera ) );
	
	float fSpecular =  material_coef_phong * pow( fPhongValue, material_coef_phong_exp );

	float4 specColor = ( rd_light1_specular * rd_color_specular ) * fSpecular;
	float4 difColor = ( rd_light1_diffuse * rd_color_diffuse ) * fDifColor;
	float4 ambColor = ( rd_light1_ambient * rd_color_ambient ) * material_coef_ambient;

	return saturate( difColor + specColor + ambColor );
}

technique Default
{
	pass p0
	{
		VertexShader = compile _S_VS_VERSION VSNormal();
 		PixelShader = compile _S_PS_VERSION PSNormal();
	}
}
