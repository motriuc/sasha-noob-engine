
#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif


//////////////////////////////////////////////////////
// Render Macros
//////////////////////////////////////////////////////
// 
// #define _S_VS_VERSION  vs_1_0 | vs_2_0 | vs_3_0 : is current Vertex Shader Max Version
// #define _S_PS_VERSION  ps_1_0 | ps_2_0 | ps_3_0 : is current Pixel Shader Max Version
//
// #define _S_VS_1_0 if suports vs_1_0
// #define _S_VS_2_0 if suports vs_2_0
// #define _S_VS_3_0 if suports vs_3_0
//
// #define _S_PS_1_0 if suports ps_1_0
// #define _S_PS_2_0 if suports ps_2_0
// #define _S_PS_3_0 if suports ps_3_0

// Light types macros
// #define _S_Light_Type_Point    
// #define _S_Light_Type_Spot


#define _S_VS_VERSION           _S("_S_VS_VERSION")
#define _S_PS_VERSION           _S("_S_PS_VERSION")
#define _S_VS_1_0               _S("_S_VS_1_0")
#define _S_VS_1_1               _S("_S_VS_1_1")
#define _S_VS_2_0               _S("_S_VS_2_0")
#define _S_VS_3_0               _S("_S_VS_3_0")
#define _S_PS_1_0               _S("_S_PS_1_0")
#define _S_PS_1_1               _S("_S_PS_1_1")
#define _S_PS_2_0               _S("_S_PS_2_0")
#define _S_PS_3_0               _S("_S_PS_3_0")

#define _S_Light_Type_Point     _S("_S_Light_Type_Point")
#define _S_Light_Type_Spot      _S("_S_Light_Type_Spot")

