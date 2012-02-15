/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_vertexbuffer.h
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

#ifndef _DX9_VERTEXBUFFER_H_
#define _DX9_VERTEXBUFFER_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
  #error rd3_conf.h must be included
#endif

#include "rd3_vertexbuffer.h"

/**
 *
 */
class Dx9VertexBuffer : public Rd3::VertexBuffer
{
private:
	typedef Rd3::VertexBuffer _BaseClass;
public:
	/**
	 *
	 */
	Dx9VertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p
	) throws_error;

	/**
	 *
	 */
	Dx9VertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexTxCoord& tx
	) throws_error;

	/**
	 *
	 */
	Dx9VertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexTxCoord& tx1,
		const Rd3::VertexTxCoord& tx2
	) throws_error;

	/**
	 *
	 */
	Dx9VertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexCList& diffuseColor,
		const Rd3::VertexTxCoord& tx1,
		const Rd3::VertexTxCoord& tx2
	) throws_error;

	/**
	 *
	 */
	Dx9VertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexCList& diffuseColor
	) throws_error;

	/**
	 *
	 */
	Dx9VertexBuffer( 
		Rd3::Render* owner,  
		const sString& objectName, 
		const Rd3::VertexPList& p,
		const Rd3::VertexNList& n,
		const Rd3::VertexCList& diffuseColor
	) throws_error;


	/**
	 *
	 */
	~Dx9VertexBuffer();

	/**
	 *
	 */
	DWORD GetFVF() const { return _dwFVF; }

	/**
	 *
	 */
	LPDIRECT3DVERTEXBUFFER9 GetHandle() const { return _pVertexBuffer; }

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

private:
	LPDIRECT3DVERTEXBUFFER9		_pVertexBuffer;
	DWORD						_dwFVF;
	sInt						_pointOffset;
	sInt						_normalOffset;

	/**
	 *
	 */
	void GetVectorList( sInt offset, System::d3Math::d3VectorList& v ) const;
};

#endif // _DX9_VERTEXBUFFER_H_
