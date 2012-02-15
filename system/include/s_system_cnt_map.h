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
	typename _KEY,
	typename _TYPE,
	typename _COMPARE = System::T::Traits<_KEY>
>
class sMap
{
private:
	typedef Internal::BTree<_KEY, _TYPE, _COMPARE>		_Tree;
public:
	typedef typename _Tree::Iterator Iterator;
	typedef typename _Tree::ConstIterator ConstIterator;

	/**
	 *	constructor
	 */
	inline sMap() :
		_content( System::Types::sFalse )
	{
	}

	/**
	 *	Copy constructor
	 */
	inline sMap( const sMap<_KEY, _TYPE, _COMPARE>& v ) :
		_content( v._content )
	{
	}

	/**
	 *	Destructor
	 */
	inline ~sMap()
	{
	}

	/**
	 *	Copy operator
	 */
	inline void operator = ( const sMap<_KEY, _TYPE, _COMPARE>& v )
	{
		_content = v._content;
	}

	/**
	 *	Add value to map
	 */
	inline System::Types::sBool Add( const _KEY& key, const _TYPE& val )
	{
		return _content.AddR( key, val );
	}

	/**
	 *	Add value to map
	 */
	inline System::Types::sBool AddC( const _KEY key, const _TYPE val )
	{
		return Add( key, val );
	}

	/**
	 *	
	 */
	inline System::Types::sBool Lookup( const _KEY& key, _TYPE& val ) const
	{
		const _TYPE* c = _content.Find( key );
		if( c != NULL )
			val = *c;

		return c != NULL;
	}

	/**
	 *	
	 */
	inline System::Types::sBool LookupC( const _KEY key, _TYPE& val ) const
	{
		return LookupR( key, val );
	}

	/**
	 *	
	 */
	inline _TYPE& operator[] ( const _KEY& key )
	{
		return _content.AddR( key );
	}
	
	/**
	 *	
	 */
	inline System::Types::sInt Size()  const
	{
		return _content.Size();
	}

	/**
	 *	
	 */
	inline System::Types::sBool Remove( const _KEY& key )
	{
		return _content.Erase( key );
	}

	/**
	 *
	 */
	inline System::Types::sBool Remove( const _KEY& key, _TYPE& val )
	{
		return _content.Erase( key, val );
	}

	/**
	 *	
	 */
	inline System::Types::sBool RemoveC( const _KEY key )
	{
		return _content.Erase( key );
	}

	/**
	 *	Remove All 
	 */
	inline void RemoveAll()
	{
		_content.Clear();
	}

	// iterators
	inline Iterator Begin()
	{
		return _content.Begin();
	}

	inline ConstIterator ConstBegin() const
	{
		return _content.ConstBegin();
	}

	inline Iterator End()
	{
		return _content.End();
	}

	inline ConstIterator ConstEnd() const
	{
		return _content.ConstEnd();
	}

private:
	_Tree		_content;
};

