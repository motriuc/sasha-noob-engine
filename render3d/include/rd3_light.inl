////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_light.inl
//	Created            : 5 2 2012   17:25
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\render3d\include
//  System independent : 0%
//  Library            : 
//
//	Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////

inline Light::Light() :
	_type( LightType::E_NULL )
{
}

inline Light::Light( const Light& src ) :
	_type( LightType::E_NULL )
{
	Assign( src );
}

inline Light::Light( const LightPoint& src ) :
	_type( LightType::E_NULL )
{
	Assign( src );
}

inline void Light::operator = ( const Light& src )
{
	Free();
	Assign( src );
}

inline void Light::operator = ( const LightPoint& src )
{
	Free();
	Assign( src );
}

inline LightPoint& Light::lightPoint()
{
	__S_ASSERT( _type == LightType::E_POINT );
	
	return *reinterpret_cast<LightPoint*>( _lightBuffer );
}

inline const LightPoint& Light::lightPoint() const
{
	__S_ASSERT( _type == LightType::E_POINT );
	
	return *reinterpret_cast<const LightPoint*>( _lightBuffer );
}


inline void Light::Assign( const Light& src )
{
	switch( src._type )
	{
		case LightType::E_NULL:
		break;
		
		case LightType::E_POINT:
			Assign( src.lightPoint() );
		break;
		
		default:
			__S_ASSERT( sFalse );	
	}
}

inline void Light::Free()
{
	switch( _type )
	{
		case LightType::E_NULL:
		break;
		
		case LightType::E_POINT:
			lightPoint().~LightPoint();
		break;
		
		
		default:
			__S_ASSERT( sFalse );
	}
	
	_type = LightType::E_NULL;
}

inline void Light::Assign( const LightPoint& src )
{
	__S_ASSERT( sizeof( LightPoint ) <= MAX_LIGHT_BUFFER );
	__S_ASSERT( _type == LightType::E_NULL );

	LightPoint* pLight = new ((LightPoint*)_lightBuffer) LightPoint();
	*pLight = src;
	
	_type = LightType::E_POINT;
}

inline LightType::LightType Light::GetType() const
{
	return _type;
}


inline sInt LightList::Size() const
{
	return _lightList.Size();
}

inline const Light& LightList::operator [] ( sInt i ) const
{
	return _lightList[i];
}

