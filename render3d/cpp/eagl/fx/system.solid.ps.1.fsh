//
//  system.solid.ps.1.fsh
//  render3d
//
//  Created by Alexandru Motriuc on 11/01/12.
//  Copyright 2012 Home. All rights reserved.
//

varying lowp vec4 v_color;

uniform lowp vec4 rd_color_diffuse;
uniform lowp vec4 rd_color_specular;
uniform lowp vec4 rd_color_ambient;

uniform lowp vec4 rd_light1_diffuse;
uniform lowp vec4 rd_light1_specular;
uniform lowp vec4 rd_light1_ambient;

void main()
{
	lowp vec4 dif1 = rd_light1_diffuse * rd_color_diffuse;
	lowp vec4 spec1 = rd_color_specular * rd_light1_specular;
	lowp vec4 amb1 = rd_color_ambient * rd_light1_ambient; 
	
	gl_FragColor = clamp( amb1 + spec1* v_color.z + dif1 * v_color.y, 0.0, 1.0 );
}