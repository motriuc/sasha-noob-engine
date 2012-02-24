/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_vertexbuffer.h
//  Created                 : 18 1 2012   0:05
//  File path               : SLibF\render3d\include\eagl
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
// Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

#ifndef _EAGL_VERTEXBUFFER_H_
#define _EAGL_VERTEXBUFFER_H_

#ifndef _EAGL_CONF_H_
	#error eagl_conf.h must be included
#endif

#include "rd3_vertexbuffer.h"

/**
 * EAGLVertexBuffer
 */
_PLATFORM class EAGLVertexBuffer : public Rd3::VertexBuffer
{
private:
	typedef Rd3::VertexBuffer _BaseClass;
public:
	/**
	 * points
	 */
	EAGLVertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p
	) throws_error;
		
	/**
	 * points, difColor
	 */
	EAGLVertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexCList& diffuseColor
	) throws_error;

	/**
	 * points, normals
	 */
	EAGLVertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexNList& n
	) throws_error;
	
	/**
	 * points, normals, tx
	 */
	EAGLVertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexNList& n,
		const Rd3::VertexTxCoord& tx
	) throws_error;
	
	/**
	 * points, tx
	 */
	EAGLVertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexTxCoord& tx
	) throws_error;
	
	/**
	 * points, tx1, tx2
	 */
	EAGLVertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexTxCoord& tx1,
		const Rd3::VertexTxCoord& tx2
	) throws_error;

	/**
	 * points, difColor, tx1, tx2
	 */
	EAGLVertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexCList& diffuseColor,
		const Rd3::VertexTxCoord& tx1,
		const Rd3::VertexTxCoord& tx2
	) throws_error;

	/**
	 * points, normals, difColor
	 */
	EAGLVertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexNList& n,
		const Rd3::VertexCList& diffuseColor
	) throws_error;

	/**
	 * Sets vb to the attributes of the OpenGL pipeline
	 */
	 void SetAttributes( const sInt* attributesId ) const;
	
public:
	// from Rd3::VertexBuffer

	/**
	 *
	 */
	virtual void GetPoints( Rd3::VertexPList& points ) const;

	/**
	 *
	 */
	virtual void GetNormals( Rd3::VertexNList& normals ) const;

	/**
	 *
	 */
	virtual void GetDiffuseColor( Rd3::VertexCList& colors ) const;

protected:
	/**
	 *
	 */
	virtual ~EAGLVertexBuffer();
	
private:
	GLfloat*					_listPoints;
	GLfloat*					_listNormals;
	GLubyte*					_listDiffuseColor;
	GLfloat*					_listTx1;
	GLfloat*					_listTx2;
	
private:	
	GLfloat* AddVectors( const Rd3::VertexPList& points );
	GLfloat* AddTx( const Rd3::VertexTxCoord& tx );
	GLubyte* AddColors( const Rd3::VertexCList& colors );
};

#endif // _DX9_VERTEXBUFFER_H_
