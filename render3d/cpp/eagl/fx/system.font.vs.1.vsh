/////////////////////////////////////////////////////////////////////
//  File Name               : system.font.vs.1.vsh
//  Created                 : 11 1 2012   0:05
//  File path               : SLibF\render3d\include\eagl\fx
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
// Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

attribute vec4 position;
attribute vec2 tx1;

varying vec2 v_texCoord;

uniform mat4 rd_d2view;

void main()
{
    gl_Position = rd_d2view * position;
	v_texCoord = tx1;
}
