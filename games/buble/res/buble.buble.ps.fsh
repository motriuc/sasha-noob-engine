//
//  buble.main.ps.fsh
//  render3d
//
//  Created by Alexandru Motriuc on 11/01/12.
//  Copyright 2012 Home. All rights reserved.
//

varying lowp vec2 v_texCoord;
uniform sampler2D rd_tx1;


void main()
{
	gl_FragColor =  texture2D( rd_tx1, v_texCoord );
}