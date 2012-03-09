//
//  system.solid.ps.2.fsh
//  render3d
//
//  Created by Alexandru Motriuc on 11/01/12.
//  Copyright 2012 Home. All rights reserved.
//

varying lowp	vec3 v_normals;
varying mediump vec3 v_position; 

uniform mediump vec4 rd_light1_pos;
uniform lowp	vec4 rd_light1_specular;
uniform lowp	vec4 rd_light1_diffuse;
uniform lowp	vec4 rd_light1_ambient;

uniform mediump vec4 rd_camera_position;

uniform lowp vec4 rd_color_specular;
uniform lowp vec4 rd_color_diffuse;
uniform lowp vec4 rd_color_ambient;

uniform mediump float material_coef_diffuse;
uniform mediump float material_coef_phong;
uniform mediump float material_coef_phong_exp;

void main()
{
	lowp vec3 vLightToPoint = normalize( v_position - rd_light1_pos.xyz );
	lowp float fDifColor = dot( v_normals, -vLightToPoint ) * material_coef_diffuse;
	
	// specular
	lowp vec3 vPointToCamera = normalize( rd_camera_position.xyz - v_position );
	lowp vec3 vReflection = reflect( vLightToPoint, v_normals );
	lowp float fPhongValue = clamp( dot( vReflection, vPointToCamera ), 0.0, 1.0 );
	
	lowp float fSpecular =  material_coef_phong * pow( fPhongValue, material_coef_phong_exp );

	lowp vec4 dif1 = rd_light1_diffuse * rd_color_diffuse;
	lowp vec4 spec1 = rd_color_specular * rd_light1_specular;
	lowp vec4 amb1 = rd_color_ambient * rd_light1_ambient; 
	
	gl_FragColor = clamp( amb1 + spec1* fSpecular + dif1 * fDifColor, 0.0, 1.0 );
}