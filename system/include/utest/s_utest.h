/////////////////////////////////////////////////////////////////////
//  File Name               : s_utest.h
//  Created                 : 14 6 2013   1:24
//  File path               : SLibF\system\include\utest
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//      Utils for multithreaded computing
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////


#include <stdio.h>

#define BEGIN_TEST( _name, _description ) \
	void test_##_name( int& _____testCount, int& _____failTestCount ) \
	{ \
		bool _____failed = false; \
		char*_____description =  _description; \
		printf( "\n[Begin Test %s]\n", _____description ); \
		{
	

#define CHECK( _name ) \
	{ \
		char* ____cond_name = ""; \
		_____testCount++; \
		bool _____cond = true; \
		printf( "    %d. Check %s : ", _____testCount, _name ); 


#define CONDITION( _cond ) \
		if( _____cond ) \
		{ \
			____cond_name = #_cond; \
		} \
		_____cond = _____cond && _cond; 

#define END \
		if( _____cond ) \
		{ \
			printf( "Ok\n" ); \
		} \
		else \
		{ \
			_____failTestCount++; \
			printf( "Fail - '%s'\n", ____cond_name ); \
		} \
	}

		
#define END_TEST \
		} \
		printf( "[End Test %s]\n", _____description ); \
	}


#define RUN_TEST( _name ) \
		test_##_name( _____testCount, _____failTestCount );

#define BEGIN_RUN_TESTS() \
	{ \
		int _____testCount = 0; \
		int _____failTestCount = 0; \
		\
		printf("-------------------------- Begin Runing Unit tests ------------------------\n");


#define END_RUN_TESTS \
		printf("\n------------------------ End Runing Unit tests ---------------------------\n"); \
		printf(" Tests %d, Failed %d\n", _____testCount ,_____failTestCount ); \
		printf("--------------------------------------------------------------------------\n"); \
	}