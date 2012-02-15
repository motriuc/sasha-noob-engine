/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_object.inl
//	Created                 : 27 6 2007   20:28
//	File path               : SLibF\system\include
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

inline sBool IType::Is( const IType* pType ) const
{
	const IType* pClass = this;
	
	while( pClass != NULL && pType != pClass )
		pClass = pClass->GetParent();

	return pClass != NULL;
}

inline sBool IType::IsReal( const IType* pType ) const
{
	return this == pType;
}

inline sBool Object::IsReal( const IType* pType ) const
{
	return ObjectType() == pType;
}

inline sBool Object::Is( const IType* pType ) const
{
	return ObjectType()->Is( pType );
}
