/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_msg.h
//  Created                 : 31 1 2011   19:58
//  File path               : SLibF\render3d\include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

#ifndef _RD3_MSG_INC_
#define _RD3_MSG_INC_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_resobj.h"

namespace Rd3
{
	
using namespace System;
	
/**
 * MessageQueue
 */
class MessageQueue : public ResourceObject
{
private:	
	typedef ResourceObject _BaseClass;
public:
	MessageQueue( Render* owner, const sString& objectName ) :
		_BaseClass( owner, objectName, ResourceType::E_MESSAGEQ )
	{
	}

	virtual void ProcessMessages( EngineData& edata ) {}
};

/**
 * MessageQueue
 */
template<typename _Type>	
class MessageQueueT : public MessageQueue
{
private:	
	typedef MessageQueue _BaseClass;
public:
	/**
	 *
	 */
	MessageQueueT( Render* owner, const sString& objectName ) :
		_BaseClass( owner, objectName )
	{
	}
	
	/**
	 * Register the event listener
	 */
	void Register( const Events::sEvent2<EngineData&, const _Type&>& e )
	{
		_eventList.Add( e );
	}
	
	/**
	 * Unregister a event listener
	 */
	void Unregister( const Events::sEvent2<EngineData&, const _Type&>& e )
	{
		for( sInt i = _eventList.Size() - 1; i>=0; --i )
		{
			if( _eventList[i] == e )
			{
				_eventList.RemoveAt( i );
				break;
			}
		}
	}
	
	/**
	 * Send the message
	 */
	void SendMessage( EngineData& edata, const _Type& msg )
	{
		for( sInt i = 0; i < _eventList.Size(); ++i ) 
		{
			_eventList[i]( edata, msg );
		}
	}
	
private:
	sVector< Events::sEvent2< EngineData&, const _Type&> >	_eventList;
};
	
	
}

#endif // _RD3_MSG_INC_