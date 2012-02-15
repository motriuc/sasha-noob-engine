//
//  system.flatcolor.ps.1.fsh
//  render3d
//
//  Created by Alexandru Motriuc on 11/01/12.
//  Copyright 2012 Home. All rights reserved.
//

uniform lowp vec4 rd_color1;

uniform lowp	vec4 rd_light1_ambient;
uniform lowp	vec4 rd_light1_specular;
uniform mediump	vec4 rd_light1_pos;
uniform mediump	vec4 rd_camera_position;

// material params
uniform mediump float material_coef_diffuse;
uniform mediump float material_coef_phong;
uniform mediump float material_coef_phong_exp;
uniform mediump float material_coef_ambient;

varying mediump	vec3 v_normals; 
varying mediump vec3 v_position;

void main()
{	
	mediump vec3 vLightToPoint = normalize( v_position - rd_light1_pos.xyz );
	mediump float fDifColor = dot( v_normals, -vLightToPoint ) * material_coef_diffuse;
	
	// specular
	mediump vec3 vPointToCamera = normalize( rd_camera_position.xyz - v_position );
	mediump vec3 vReflection = reflect( vLightToPoint, v_normals );
	mediump float fPhongValue = clamp( dot( vReflection, vPointToCamera ), 0.0, 1.0 );
	
	mediump float fSpecular =  material_coef_phong * pow( fPhongValue, material_coef_phong_exp );
	
	mediump float fColor = material_coef_ambient + fDifColor;
	
	gl_FragColor =  clamp( rd_color1*fColor + fSpecular * rd_light1_specular, 0.0, 1.0 );
}