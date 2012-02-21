//
//  system.after.effect.color.ps.fsh
//  render3d
//
//  Created by Alexandru Motriuc on 11/01/12.
//  Copyright 2012 Home. All rights reserved.
//

varying lowp vec2 v_texCoord;
uniform sampler2D rd_tx1;

uniform lowp float lumR;
uniform lowp float lumG;
uniform lowp float lumB;

uniform lowp float contrast;	


void main()
{
	lowp vec4 color = texture2D( rd_tx1, v_texCoord );
	color.x *= lumR;
	color.y *= lumG;
	color.z *= lumB;
	
	color -= 0.5;
	color *= contrast;
	color += 0.5;
	
	gl_FragColor = clamp( color, 0.0, 1.0 ); 
}