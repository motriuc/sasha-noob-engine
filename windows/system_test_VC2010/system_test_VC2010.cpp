// system_test_VC2010.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define _use_sVector_
#define _use_sMap_

#include "s_system.h"

using namespace System;
using namespace System::Types;
using namespace System::Cnt; 

#include "utest\s_utest.h"
#include "utest\test_util_allocate_object.h"
#include "utest\test_ptr_shared.h"
#include "utest\test_ptr_weak.h"
#include "utest\test_t_typetraits.h"
#include "utest\test_vector.h"
#include "utest\test_map.h"s

int _tmain(int argc, _TCHAR* argv[])
{

	BEGIN_RUN_TESTS()
		RUN_TEST( ptr_shared )
		RUN_TEST( ptr_weak )
		RUN_TEST( type_traits )
		RUN_TEST( vector )
		RUN_TEST( map )
	END_RUN_TESTS
}

