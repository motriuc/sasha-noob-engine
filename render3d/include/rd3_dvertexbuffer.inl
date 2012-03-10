/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_dvertexbuffer.inl
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

inline sUInt DynamicVertexBuffer::GetCount() const
{
	return _vertexCount;
}

inline sUInt DynamicVertexBuffer::GetSize() const
{
	return _vertexSize * _vertexCount;
}

inline sUInt DynamicVertexBuffer::GetVertexSize() const
{
	return _vertexSize;
}

inline void DynamicVertexBuffer::AddVertex( const d3Vector& p, const d2Vector& tx1 )
{
	AddVertex( p );
	SetTx1( tx1 );
}

inline void DynamicVertexBuffer::AddVertex( const d3Vector& p )
{
	if( _cacheCurrentVertex >= CacheVertexBufferSize - 1 )
	{
		Flush();
		_cacheCurrentVertex = 0;
	}
	else
		++_cacheCurrentVertex;

	__S_ASSERT( _cacheCurrentVertex >= 0 );

	_points[_cacheCurrentVertex] = p;
}

inline void DynamicVertexBuffer::SetNormal( const d3Vector& n )
{
	__S_ASSERT( _cacheCurrentVertex < CacheVertexBufferSize );
	_normal[_cacheCurrentVertex] = n;
}

inline void DynamicVertexBuffer::SetTx1( const d2Vector& v )
{
	__S_ASSERT( _cacheCurrentVertex < CacheVertexBufferSize );
	_tx1[_cacheCurrentVertex] = v; 
}

inline void DynamicVertexBuffer::SetTx2( const d2Vector& v )
{
	__S_ASSERT( _cacheCurrentVertex < CacheVertexBufferSize );
	_tx2[_cacheCurrentVertex] = v; 
}

inline void DynamicVertexBuffer::SetDiffiuseColor( const sRGBColor c )
{
	__S_ASSERT( _cacheCurrentVertex < CacheVertexBufferSize );
	_diffuseColor[_cacheCurrentVertex] = c;
}
