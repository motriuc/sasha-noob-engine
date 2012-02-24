//
//  system.solid.ps.1.fsh
//  render3d
//
//  Created by Alexandru Motriuc on 11/01/12.
//  Copyright 2012 Home. All rights reserved.
//

varying lowp vec4 v_color;
//varying lowp vec2 v_texCoord;

uniform mediump vec4 rd_color_diffuse;
uniform mediump vec4 rd_color_specular;

void main()
{
	gl_FragColor = clamp( rd_color_specular* v_color.z + rd_color_diffuse * v_color.y, 0.0, 1.0 );
	//gl_FragColor = vec4( v_color.z, v_color.z,v_color.z,1.0 );
}