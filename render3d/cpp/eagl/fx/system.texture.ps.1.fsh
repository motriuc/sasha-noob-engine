//
//  system.texture.ps.1.fsh
//  render3d
//
//  Created by Alexandru Motriuc on 11/01/12.
//  Copyright 2012 Home. All rights reserved.
//

varying lowp vec4 v_color;
varying lowp vec2 v_texCoord;

uniform sampler2D rd_tx1;
uniform mediump vec4 rd_light1_specular;

void main()
{	
	lowp vec4 txColor = texture2D( rd_tx1, v_texCoord );
	
	lowp float fColor = v_color.x + v_color.y;
	lowp float fSpecular = v_color.z;
	
	gl_FragColor = clamp( txColor * fColor + fSpecular * rd_light1_specular, 0.0, 1.0 );
}