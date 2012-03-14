//
//  system.texture.ps.0.fsh
//  render3d
//
//  Created by Alexandru Motriuc on 14/03/12.
//  Copyright 2012 Home. All rights reserved.
//

varying lowp vec2 v_texCoord;

uniform sampler2D rd_tx1;

uniform lowp float material_coef_ambient;

void main()
{	
	lowp vec4 txColor = texture2D( rd_tx1, v_texCoord );
	
	gl_FragColor = clamp( txColor*material_coef_ambient , 0.0, 1.0 );
}