//
//  system.solid.vs.1.vsh
//  render3d
//
//  Created by Alexandru Motriuc on 11/01/12.
//  Copyright 2012 Home. All rights reserved.
//

attribute vec4 position;
attribute vec4 normals;

varying vec4 v_color;

// 
uniform mat4 rd_worldviewprojection;
uniform mat4 rd_world;
uniform mat4 rd_worldnormal;

uniform vec4 rd_light1_pos;
uniform vec4 rd_camera_position;

uniform float material_coef_diffuse;
uniform float material_coef_phong;
uniform float material_coef_phong_exp;

void main()
{
	vec3 v_position = (rd_world*position).xyz;
	vec3 v_normals = normalize( (rd_worldnormal*normals).xyz );

	vec3 vLightToPoint = normalize( v_position - rd_light1_pos.xyz );
	float fDifColor = dot( v_normals, -vLightToPoint ) * material_coef_diffuse;
	
	// specular
	vec3 vPointToCamera = normalize( rd_camera_position.xyz - v_position );
	vec3 vReflection = reflect( vLightToPoint, v_normals );
	float fPhongValue = clamp( dot( vReflection, vPointToCamera ), 0.0, 1.0 );
	
	float fSpecular =  material_coef_phong * pow( fPhongValue, material_coef_phong_exp );
	
	v_color = vec4( 0.0, fDifColor, fSpecular, 0.0 );
	
    gl_Position =   rd_worldviewprojection * position;
}
