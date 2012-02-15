//
//  system.font.vs.1.vsh
//  render3d
//
//  Created by Alexandru Motriuc on 11/01/12.
//  Copyright 2012 Home. All rights reserved.
//

attribute vec4 position;
attribute vec2 tx1;

varying vec2 v_texCoord;

void main()
{
    gl_Position = position;
	v_texCoord = tx1;
}
