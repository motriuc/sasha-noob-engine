/////////////////////////////////////////////////////////////////////
//  File Name               : system.font.vs.2.vsh
//  Created                 : 26 03 2012
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

uniform mat4 rd_worldviewprojection;

void main()
{
    gl_Position = rd_worldviewprojection * position;
	v_texCoord = tx1;
}
