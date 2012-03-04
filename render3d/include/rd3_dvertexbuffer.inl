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

inline void DynamicVertexBuffer::AddVertex( const d3Vector& p )
{
	++_currentVertex;

	__S_ASSERT( _currentVertex >= 0 );

	if( _currentVertex >= VertexBufferSize )
	{
		Flush();
		_currentVertex = 0;
	}

	_points[_currentVertex] = p;
}

inline void DynamicVertexBuffer::SetNormal( const d3Vector& n )
{
	__S_ASSERT( _currentVertex < VertexBufferSize );
	_normal[_currentVertex] = n;
}

inline void DynamicVertexBuffer::SetTx1( const d2Vector& v )
{
	__S_ASSERT( _currentVertex < VertexBufferSize );
	_tx1[_currentVertex] = v; 
}

inline void DynamicVertexBuffer::SetTx2( const d2Vector& v )
{
	__S_ASSERT( _currentVertex < VertexBufferSize );
	_tx2[_currentVertex] = v; 
}

inline void DynamicVertexBuffer::SetDiffiuseColor( const sRGBColor c )
{
	__S_ASSERT( _currentVertex < VertexBufferSize );
	_diffuseColor[_currentVertex] = c;
}
