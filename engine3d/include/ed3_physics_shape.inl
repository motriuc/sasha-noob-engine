////////////////////////////////////////////////////////////////////////
//  File Name          : ed3_physics_shape.inl
//  Created            : 29 02 2012   19:09
//  Author             : Alexandru Motriuc  
//  File Path          : SLibF\engine3d\include
//  System independent : 0%
//  Library            : 
//
//  Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////

inline phShape::phShape( d3Object* owner ) :
	_owner( owner )
{
	__S_ASSERT( _owner != NULL );
}
	
inline phShape::~phShape()
{
}

inline d3Object* phShape::GetOwner()
{
	return _owner;
}
