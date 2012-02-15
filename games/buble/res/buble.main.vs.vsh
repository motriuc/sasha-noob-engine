//
//  buble.main.vs.vsh
//  render3d
//
//  Created by Alexandru Motriuc on 11/01/12.
//  Copyright 2012 Home. All rights reserved.
//

attribute vec4 position;
attribute vec2 tx1;

varying vec2 v_texCoord;
uniform mat4 rd_viewprojection;

void main()
{
	v_texCoord = tx1;
    gl_Position = rd_viewprojection*position;
}
