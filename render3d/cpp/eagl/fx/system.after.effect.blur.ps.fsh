//
//  system.after.effect.blur.ps.fsh
//  render3d
//
//  Created by Alexandru Motriuc on 11/01/12.
//  Copyright 2012 Home. All rights reserved.
//

varying lowp vec2 v_texCoord;
uniform sampler2D rd_tx1;

uniform mediump float pixelW;
uniform mediump float pixelH;		


void main()
{
	mediump float dw = pixelW;
	mediump float dh = pixelH;
	 
	mediump vec4 v0 = texture2D( rd_tx1, v_texCoord );
	v0 += texture2D( rd_tx1, v_texCoord + vec2( dw, 0.0 ) );
	
	v0 += texture2D( rd_tx1, v_texCoord + vec2( -dw, 0.0 ) );
	v0 += texture2D( rd_tx1, v_texCoord + vec2( 0.0, dh ) );
	v0 += texture2D( rd_tx1, v_texCoord + vec2( 0.0, -dh ) );
	v0 += texture2D( rd_tx1, v_texCoord + vec2( 0.0, dh ) );

	v0 += texture2D( rd_tx1, v_texCoord + vec2( -dw, -dh ) );
	v0 += texture2D( rd_tx1, v_texCoord + vec2( dw, dh ) );
	v0 += texture2D( rd_tx1, v_texCoord + vec2( -dw, dh ) );
	v0 += texture2D( rd_tx1, v_texCoord + vec2( dw, -dh ) );


	
	gl_FragColor = v0 / 9.0; 
}