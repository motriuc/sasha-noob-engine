//
//  system.texture.vs.1.qh.vsh
//  render3d
//
//  Created by Alexandru Motriuc on 22/03/12.
//  Copyright 2012 Home. All rights reserved.
//

attribute vec4 position;
attribute vec4 normals;
attribute vec2 tx1;

varying vec2 v_texCoord;
varying vec3 v_normals;
varying vec3 v_position; 
 
// 
uniform mat4 rd_worldviewprojection;
uniform mat4 rd_world;
uniform mat4 rd_worldnormal;


void main()
{	
	v_texCoord = tx1;
	v_position = (rd_world*position).xyz;
	v_normals = normalize( (rd_worldnormal*normals).xyz );
	
	gl_Position = rd_worldviewprojection * position;
}
