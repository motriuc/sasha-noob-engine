////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_perf_counters.h
//	Created            : 20 1 2012   23:04
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\render3d\include
//  System independent : 0%
//  Library            : 
//
//	Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////

#ifndef _RD3_PERF_COUNTERS_H_
#define _RD3_PERF_COUNTERS_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
#error rd3_conf.h must be included
#endif

namespace Rd3
{

/**
 * PerformanceCounter
 */
class PerformanceCounter
{
public:
	/**
	 *
	 */
	PerformanceCounter();
	
	/**
	 * PerformanceCounter
	 */
	PerformanceCounter( const sString& name, const sString& units = _S(""), const sString& description = _S("") );
	
	/**
	 *
	 */
	void operator += ( sInt n );
	void operator -= ( sInt n );

	void operator += ( sFloat n );
	void operator -= ( sFloat n );

	void operator += ( sDouble n );
	void operator -= ( sDouble n );
	
	/**
	 *
	 */
	void operator = ( sInt n );
	void operator = ( sFloat n );
	void operator = ( sDouble n );
	
	/**
	 *
	 */
	void StartTimer();
	
	/**
	 *
	 */
	void StopTimer();
	
	/**
	 *
	 */
	void ResetTimer();
	
	/**
	 *
	 */
	static sInt Register( const PerformanceCounter& perfc );
	
	/**
	 *
	 */
	static PerformanceCounter& Counter( sInt idc );
	
	/**
	 *
	 */
	sInt ValueInt() const;
	
	/**
	 *
	 */
	sDouble ValueDouble() const;
	
private:
	sInt	_intCounter;
	sFloat	_floatCounter;
	sDouble	_doubleCounter;
	
	sDouble _timerStart;
	sDouble _currentTime;
	
	sInt	_id;
	
	sString	_name;
	sString _units;
	sString _description;
	
	static sVector<PerformanceCounter>	_counters;

};
	
#include "rd3_perf_counters.inl"
	
}


#ifdef _D3_DEBUG_RENDER_ENABLE_COUNTERS

	#define COUNTER_DECLARE( _c, _name, _units, _desc ) \
		namespace Rd3_Counters \
		{ \
			System::Types::sInt _c = \
				Rd3::PerformanceCounter::Register( Rd3::PerformanceCounter( _name, _units, _desc ) ); \
		}

	#define COUNTER_USE( _c ) \
		namespace Rd3_Counters \
		{ \
			extern System::Types::sInt _c; \
		}

	#define COUNTER_INT_INC( _c, _v ) \
		{ \
			Rd3::PerformanceCounter::Counter( Rd3_Counters::_c ) += (System::Types::sInt)(_v); \
		}

	#define COUNTER_INT_SET( _c, _v ) \
		{ \
			Rd3::PerformanceCounter::Counter( Rd3_Counters::_c ) = (System::Types::sInt)(_v); \
		}

	#define COUNTER_INT_VALUE( _c ) \
		( Rd3::PerformanceCounter::Counter( Rd3_Counters::_c ).ValueInt() )

	#define COUNTER_DOUBLE_VALUE( _c ) \
		( Rd3::PerformanceCounter::Counter( Rd3_Counters::_c ).ValueDouble() )


	#define COUNTER_TIME_RESET( _c ) \
		{ \
			Rd3::PerformanceCounter::Counter( Rd3_Counters::_c ).ResetTimer(); \
		}

	#define COUNTER_TIME_START( _c ) \
		{ \
			Rd3::PerformanceCounter::Counter( Rd3_Counters::_c ).StartTimer(); \
		}

	#define COUNTER_TIME_STOP( _c ) \
		{ \
			Rd3::PerformanceCounter::Counter( Rd3_Counters::_c ).StopTimer(); \
		}


#else

	#define COUNTER_USE( _c )
	#define COUNTER_DECLARE( _c, _t )
	
	#define COUNTER_INC_INT( _c, _v )
	#define COUNTER_INT_SET( _c, _v )

	#define COUNTER_TIME_RESET( _c )
	#define COUNTER_TIME_START( _c )
	#define COUNTER_TIME_STOP( _c )

#endif // _D3_DEBUG_RENDER_ENABLE_COUNTERS


#endif

