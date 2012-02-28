/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_vertexbuffer.h
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
#ifndef _RD3_VERTEXBUFFER_H_
#define _RD3_VERTEXBUFFER_H_

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
	
/**
 *
 */
class VertexBuffer : public ResourceObject
{
private:
	typedef ResourceObject _BaseClass;
public:
	/**
	 *
	 */
	sUInt GetCount() const                           { return _vertexCount; }

	/**
	 * 
	 */
	sUInt GetSize() const                            { return _vertexBufferSize; }

	/**
	 * 
	 */
	sUInt GetVertexSize() const                     { return _vertexSize; }

	/**
	 *
	 */
	virtual void GetPoints( VertexPList& points ) const = 0;

	/**
	 *
	 */
	virtual void GetNormals( VertexNList& normals ) const = 0;

	/**
	 *
	 */
	virtual void GetDiffuseColor( VertexCList& colors ) const = 0;
	
	/**
	 * 
	 */
	virtual void ComputeBoundingBox( d3AABBox& bbox ) const = 0;
	
	/**
	 *
	 */
	virtual void ComputeBoundingBox( d3AABBox& bbox, const d3Matrix& tran ) const = 0;
	
	~VertexBuffer();

protected:
	VertexBuffer( Render* owner, const sString& objectName );
	
	void PostInit();
protected:
	sUInt                                   _vertexCount;
	sUInt                                   _vertexBufferSize;
	sUInt                                   _vertexSize;
};

}

#endif // _RD3_VERTEXBUFFER_H_