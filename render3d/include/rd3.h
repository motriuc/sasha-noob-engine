/////////////////////////////////////////////////////////////////////
//  File Name               : rd3.h
//	Created                 : 20 1 2011   0:05
//	File path               : SLibF\render3d\include
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//	Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

#if !defined(_RD3_H_)
#define _RD3_H_

#ifdef _S_SYS_INC_
	#error don't include s_system.h befor this header
#endif

/////////////////////////////////////////////

#ifndef _use_Streams_
	#define _use_Streams_
#endif

#ifndef _use_sVector_
	#define _use_sVector_
#endif

#ifndef _use_sMap_
	#define _use_sMap_
#endif

#ifndef _use_d3Math_
	#define _use_d3Math_
#endif

#ifndef _use_d2Math_
	#define _use_d2Math_
#endif

#ifndef _use_Xml_
	#define _use_Xml_
#endif

#ifndef _use_sEvent_
	#define _usse_sEvent_
#endif

#ifndef _use_Cont_Utils_
	#define _use_Cont_Utils_
#endif 

#include "s_system.h"

//////////////////////////////////////////////

#include "rd3_conf.h"
#include "rd3_types.h"

namespace Rd3
{
	class Render;
	class Def;
	class RenderState;
	class ResourceObject;
	class Texture;
	class VertexBuffer;
	class IndexBuffer;
	class Effect;
	class Mesh;
	class Material;
	class LightSelection;
	class EngineDataForRender;
	class WorldRenderState;
}

#endif // !defined(_RD3_H_)
