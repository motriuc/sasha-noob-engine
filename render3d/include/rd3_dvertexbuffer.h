/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_dvertexbuffer.h
//  Created                 : 4 3 2012   1:22
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
#ifndef _RD3_DVERTEX_BUFFER_INC_
#define _RD3_DVERTEX_BUFFER_INC_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

#include "rd3_resobj.h"

namespace Rd3
{

using namespace System::d3Math;
using namespace System::d2Math;

/**
 * DynamicVertexBuffer
 */
class DynamicVertexBuffer : public ResourceObject
{
private:
	typedef ResourceObject _BaseClass;
protected:
	static const sInt CacheVertexBufferSize = 128;

	/**
	 *
	 */
	DynamicVertexBuffer( Render* owner, const sString& objectName, VertexBufferStream::Set vbset );
public:
	/**
	 *
	 */
	sUInt GetCount() const;

	/**
	 * 
	 */
	sUInt GetSize() const;

	/**
	 * 
	 */
	sUInt GetVertexSize() const;

	/**
	 *
	 */
	virtual sBool BeginAdd( sInt vertexCount ) = 0;
	virtual void EndAdd() = 0;
	virtual void Flush() = 0;

	void AddVertex( const d3Vector& p );
	void AddVertex( const d3Vector& p, const d2Vector& tx1 );
	void SetNormal( const d3Vector& n );
	void SetTx1( const d2Vector& v );
	void SetTx2( const d2Vector& v );
	void SetDiffiuseColor( const sRGBColor c );
protected:
	d3Vector	_points[CacheVertexBufferSize];
	d3Vector	_normal[CacheVertexBufferSize];
	sRGBColor	_diffuseColor[CacheVertexBufferSize];
	d2Vector	_tx1[CacheVertexBufferSize];
	d2Vector	_tx2[CacheVertexBufferSize];

	sInt	_cacheCurrentVertex;

	sUInt	_vertexCount;
	sUInt	_vertexSize;
	sUInt	_maxVertexCount;

	VertexBufferStream::Set _vbset;
};

#include "rd3_dvertexbuffer.inl"

}

#endif // _RD3_DVERTEX_BUFFER_INC_