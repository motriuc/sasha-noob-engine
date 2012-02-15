
#ifdef _S_SYS_INC_
	#error don't include s_system.h befor this header
#endif

#define _use_sError_
#define _use_sVector_
#define _use_sMap_
#define _use_sEvent_
#define _use_d3Math_
#define _use_d2Math_
#define _use_Streams_
#define _use_Xml_
#define _use_Cont_Utils_

#include "s_system.h"
#include "rd3_conf.h"
#include "rd3_types.h"
#include "rd3_def.h"
#include "rd3_perf_counters.h"


#ifdef _SPL_MAC
	#include "platform_eagl_context.h"
#endif
