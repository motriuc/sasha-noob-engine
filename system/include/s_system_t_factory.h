/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_t_factory.h
//  Created                 : 19 1 2012   18:12
//  File path               : SLibF\system\include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
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


/**
 * IClassFactory
 */
template< typename _Type >
class IClassFactory
{
public:
	virtual _Type* Create() = 0;
};

/**
 * IClassFactory2
 */
template< typename _Type, typename _P1, typename _P2 >
class IClassFactory2
{
public:
	virtual _Type* Create( _P1 p1, _P2 p2 ) = 0;
};

/**
 * ClassFactory
 */
template< typename _Class, typename _Type >
class ClassFactory : public IClassFactory<_Type>
{
public:
	virtual _Type* Create() { return new _Class(); }	
};

template< typename _Class, typename _Type, typename _P1, typename _P2 >
class ClassFactory2 : public IClassFactory2< _Type, _P1, _P2 >
{
public:
	virtual _Type* Create( _P1 p1, _P2 p2 ) { return new _Class( p1, p2 ); } 
};

/**
 * ClassFactoryById
 */
template< typename _Type, typename _IdType, typename _Continer >
class ClassFactoryById
{
public:
	void Register( const _IdType& name, IClassFactory<_Type>* pFactory )
	{
		__S_ASSERT( pFactory != NULL );
		__S_VERIFY( _factoryMap.Add( name, pFactory ) );
	}
										 
	_Type* Create( const _IdType& name )
	{
		IClassFactory<_Type>* pFactory = NULL;
		
		_factoryMap.Lookup( name, pFactory );
		
		if( pFactory != NULL )
			return pFactory->Create();
		
		return NULL;
	}
private:
	_Continer _factoryMap;
};


/**
 * ClassFactoryById2
 */
template< typename _Type, typename _IdType, typename _Continer, typename _P1, typename _P2 >
class ClassFactoryById2
{
public:
	void Register( const _IdType& name, IClassFactory2<_Type,_P1, _P2>* pFactory )
	{
		__S_ASSERT( pFactory != NULL );
		__S_VERIFY( _factoryMap.Add( name, pFactory ) );
	}
	
	_Type* Create( const _IdType& name, _P1 p1, _P2 p2 )
	{
		IClassFactory2<_Type,_P1, _P2>* pFactory = NULL;
		
		_factoryMap.Lookup( name, pFactory );
		
		if( pFactory != NULL )
			return pFactory->Create( p1, p2 );
		
		return NULL;
	}
private:
	_Continer _factoryMap;
};