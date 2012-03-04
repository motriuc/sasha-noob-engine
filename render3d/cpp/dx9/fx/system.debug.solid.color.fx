/////////////////////////////////////////////////////////////////////
//  File Name               : system.debug.solid.color.fx
//  Created                 : 4 3 2012  
//  File path               : SLibF\render3d\cpp\dx9\fx
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//      Solid render shader for debug purposes
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////


float4x4 rd_worldviewprojection<>;

struct VSINPUT
{
	float4 Position : POSITION;
	float4 Diffuze  : COLOR0;
};

VSINPUT VSNormal( VSINPUT v )
{
	v.Position = mul( v.Position, rd_worldviewprojection );
	return v;
}

float4 PSNormal( VSINPUT v ) : COLOR
{
	return v.Diffuze;
}

technique Default
{
	pass p0
	{
		VertexShader = compile _S_VS_VERSION VSNormal();
 		PixelShader = compile _S_PS_VERSION PSNormal();
	}
}

