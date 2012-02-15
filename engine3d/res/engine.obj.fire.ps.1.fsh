//
//  engine.obj.fire.ps.1.fsh
//  render3d
//
//  Created by Alexandru Motriuc on 11/01/12.
//  Copyright 2012 Home. All rights reserved.
//

varying lowp vec2 v_texCoord;

uniform highp float rd_time;

// effect uniforms
uniform mediump float sideFade;
uniform mediump float sideFadeSharpness;
uniform mediump float wobbleScale;
uniform mediump float burnSpeed;
uniform mediump float yFade;
uniform mediump float xScale;
uniform mediump float yScale;

// engine uniforms
uniform lowp sampler2D rd_tx1;
uniform lowp sampler2D rd_tx2;


const mediump float c6 = 6.0;
const mediump float c2 = 2.0;
const mediump float c7 = 7.0;
/**
 * saturate
 */
lowp float saturate( mediump float inValue)
{
   return clamp( inValue, 0.0, 1.0 );
}

void main()
{
   // Wobble for the noise to get a more realistic appearance
   mediump float wobbX = c2 * cos(c6 * v_texCoord.x + rd_time);
   
   mediump float wobbY = c7 * (1.0 - v_texCoord.y) * (1.0 - v_texCoord.y);
   mediump float wobble = sin(rd_time + wobbX + wobbY);
 
   mediump vec2 coord;
 
   // Wobble more in the flames than at the base
   coord.x = xScale * v_texCoord.x + wobbleScale * (v_texCoord.y + 1.0) * wobble;
 
   // Create an upwards movement
   coord.y = yScale * v_texCoord.y - burnSpeed * rd_time;
 
   mediump float noisy = texture2D(rd_tx1, coord).x;

   // Define the shape of the fire
   mediump float t = sideFadeSharpness * (1.0 - sideFade * v_texCoord.x * v_texCoord.x);

   // Get the color out of it all
   mediump float heat = saturate(t + noisy - yFade * v_texCoord.y);
   
   lowp vec4 flame = texture2D(rd_tx2, vec2(heat,0.0));
   
   gl_FragColor = vec4( flame.rgb, flame.r );
}
