//
//  system.texture.vs.0.vsh
//  render3d
//
//  Created by Alexandru Motriuc on 14/03/12.
//  Copyright 2012 Home. All rights reserved.
//

attribute vec4 position;
attribute vec2 tx1;

varying vec3 v_position;
varying vec2 v_texCoord;

// 
uniform mat4 rd_worldviewprojection;

void main()
{
	v_texCoord = tx1;
	gl_Position =   rd_worldviewprojection* position;
}
