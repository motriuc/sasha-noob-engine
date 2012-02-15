/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_indexbuffer.h
//	Created                 : 28 1 2011   20:05
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

#ifndef _RD3_INDEXBUFFER_H_
#define _RD3_INDEXBUFFER_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

#include "rd3_resobj.h"


namespace Rd3
{

/**
 * IndexBuffer
 */
class IndexBuffer : public ResourceObject
{
private:
	typedef ResourceObject _BaseClass;
public:
	/**
	 *
	 */
	sUInt GetCount() const                           { return _indexCount; }

	/**
	 * 
	 */
	sUInt GetSize() const                            { return _indexBufferSize; }

	/**
	 * 
	 */
	sUInt GetIndexSize() const                     { return _indexSize; }
	
	/**
	 *
	 */
	~IndexBuffer();
protected:
	IndexBuffer( Render* owner, const sString& objectName );
	
	void PostInit();
protected:
	sUInt                                   _indexCount;
	sUInt                                   _indexBufferSize;
	sUInt                                   _indexSize;
};

}

#endif // _RD3_INDEXBUFFER_H_