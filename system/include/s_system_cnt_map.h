/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_cnt_map.h
//	Created                 : 28 6 2007   20:43
//	File path               : SLibF\system\Include
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

// _use_sMap_

#include "internal/int_btree.h"
/**
 *	SLib map
 */
template<
	typename _Key,
	typename _Type,
	typename _Compare = System::DefaultCmp<_Key>
>
class sMap
{
private:
	typename typedef Internal::BTree<_Key, _Type, _Compare>		_Tree;
public:
	typename typedef _Tree::Iterator Iterator;
	typename typedef _Tree::ConstIterator ConstIterator;

	typename typedef _Type ElementType;
	typename typedef T::Traits<_Type>::AsInput InputType;
	typename typedef T::Traits<_Key>::AsInput InputKey;
public:
	/**
	 * creates an empty map
	 * RATING( +-+ )
	 */
	sMap() :
		_content( System::Types::sFalse )
	{
	}

	/**
	 *	Copy constructor
	 */
	sMap( const sMap<_Key, _Type, _Compare>& v ) :
		_content( v._content )
	{
	}

	/**
	 *	Destructor
	 */
	~sMap()
	{
	}

	/**
	 *	Copy operator
	 */
	void operator = ( const sMap<_Key, _Type, _Compare>& v )
	{
		_content = v._content;
	}

#ifdef _SLIB_CPP11
	/**
	 * Move copy constructor
	 */
	sMap( sMap<_Key, _Type, _Compare>&& v ) :
		_content( T::Move( v._content ) )
	{
	}

	/**
	 * Assign move operator
	 */
	void operator = ( sMap<_Key, _Type, _Compare>&& v )
	{
		_content = T::Move( v._content );
	}
#endif

	/**
	 *	Add value to map
	 */
	sBool Add( InputKey key, InputType val )
	{
		return _content.AddR( key, val );
	}

	/**
	 * Look up the value by the key
	 */
	sBool Lookup( InputKey key, _Type& val ) const
	{
		const _Type* c = _content.Find( key );
		if( c != NULL )
			val = *c;

		return c != NULL;
	}

	/**
	 *	
	 */
	_Type& operator[] ( InputKey key )
	{
		return _content.AddR( key );
	}

	/**
	 *	
	 */
	const _Type& operator[] ( InputKey key ) const
	{
		return _content.AddR( key );
	}

	/**
	 * returns map size	
	 */
	sInt Size()  const
	{
		return _content.Size();
	}

	/**
	 * remove element from the map by key
	 */
	sBool Remove( InputKey key )
	{
		return _content.Erase( key );
	}

	/**
	 * removes element from the map by key
	 */
	sBool Remove( InputKey key, _Type& val )
	{
		return _content.Erase( key, val );
	}

	/**
	 *	Remove All 
	 */
	void RemoveAll()
	{
		_content.Clear();
	}

	// iterators
	Iterator Begin()
	{
		return _content.Begin();
	}

	ConstIterator ConstBegin() const
	{
		return _content.ConstBegin();
	}

	Iterator End()
	{
		return _content.End();
	}

	ConstIterator ConstEnd() const
	{
		return _content.ConstEnd();
	}

private:
	_Tree		_content;
};
