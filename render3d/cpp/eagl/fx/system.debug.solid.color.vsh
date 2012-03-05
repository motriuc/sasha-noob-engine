/////////////////////////////////////////////////////////////////////
//  File Name               : system.debug.solid.color.vsh
//  Created                 : 11 1 2012   0:05
//  File path               : SLibF\render3d\cpp\eagl\fx
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
attribute vec4 color_diffuse;

varying vec4 v_color;

uniform mat4 rd_worldviewprojection;

void main()
{
    gl_Position = rd_worldviewprojection * position;
	v_color = color_diffuse;
}
