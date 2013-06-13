/////////////////////////////////////////////////////////////////////
//	File Name               : int_btree.h
//	Created                 : 28 6 2007   21:07
//	File path               : SLibF\system\include
//	Author                  : Alexandru Motriuc
//	Platform Independentsy  : 0%
//	Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      BTree implementation, this code is taken from an version of STL
//		with some modifications
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

namespace Internal
{

template< typename _KEY, typename _TYPE, typename _COMPARE >
class BTree
{
private:
	typedef struct
	{
		_KEY		_Key;
		_TYPE		_Value;
	} Content;
private:
	/**
	 *	Color
	 */
	enum _Redbl { _Red, _Black };
	struct _Node;

	typedef struct _Node*	_Nodeptr;
	typedef struct _Node*&	_Nodepref;
	typedef _Redbl&			_Rbref;
	typedef _TYPE&			_Vref;
	typedef _KEY&			_Keyref;
	typedef struct _Node	_NodeV;

	typedef struct 
	{
		_Nodeptr	_Left, _Parent, _Right;
		_Redbl		_Color;
	} _BNode;

	struct _Node : public _BNode
	{
		Content		_content;
	};

	inline static _Rbref _Color ( _Nodeptr _P )
	{
		return ((_Rbref)(*_P)._Color);
	}

	inline static _Keyref _Key( _Nodeptr _P )
	{
		return ((_Keyref)(*_P)._content._Key);
	}

	inline static _Nodepref _Left( _Nodeptr _P )
	{
		return ((_Nodepref)(*_P)._Left);
	}
	
	inline static _Nodepref _Parent( _Nodeptr _P )
	{
		return ((_Nodepref)(*_P)._Parent);
	}

	inline static _Nodepref _Right( _Nodeptr _P )
	{
		return ((_Nodepref)(*_P)._Right);
	}
	inline static _Vref _Value( _Nodeptr _P )
	{
		return ((_Vref)(*_P)._content._Value);
	}

	/**
	 *	Alloc new node
	 */
	inline static _Nodeptr _Buynode( _Nodeptr _Parg, _Redbl _Carg )
    {
		_Nodeptr p = new struct _Node;
		_Parent(p) = _Parg;
		_Color(p) = _Carg;
		return (p);
	}
	
	inline static void _Freenode( _Nodeptr p )
	{
		delete p;
	}

	inline _Nodeptr& _Lmost()
	{
		return (_Left(_Head));
	}
	
	inline const _Nodeptr& _Lmost() const
	{
		return (_Left(_Head));
	}

	inline _Nodeptr& _Rmost()
	{
		return (_Right(_Head));
	}
	
	inline const _Nodeptr& _Rmost() const
	{
		return (_Right(_Head));
	}
	
	inline _Nodeptr& _Root()
	{
		return (_Parent(_Head));
	}
	
	inline const _Nodeptr& _Root() const
	{
		return (_Parent(_Head));
	}

	_Nodeptr _Lbound( const _KEY& _Kv ) const
	{
		_Nodeptr _X = _Root();
		_Nodeptr _Y = _Head;
		while (_X != _Nil)
		{
			if( _key_compare( _X, _Kv) )
				_X = _Right(_X);
			else
				_Y = _X, _X = _Left(_X);
		}
		return _Y; 
	}

	_Nodeptr _Ubound( const _KEY& _Kv ) const
	{
		_Nodeptr _X = _Root();
		_Nodeptr _Y = _Head;
		
		while (_X != _Nil)
		{
			if( _key_compare(_Kv, _X ) )
				_Y = _X, _X = _Left(_X);
			else
				_X = _Right(_X);
		}
		
		return (_Y);
	}

	void _Init()
	{
		_Head = _Buynode( _Nil, _Red );
		_Size = 0;
		_Lmost() = _Head;
		_Rmost() = _Head;
	}

	void _Rrotate( _Nodeptr _X )
	{
		_Nodeptr _Y = _Left(_X);
		_Left(_X) = _Right(_Y);

		if( _Right(_Y) != _Nil )
			_Parent(_Right(_Y)) = _X;
                
		_Parent(_Y) = _Parent(_X);
		
		if ( _X == _Root() )
			_Root() = _Y;
		else if( _X == _Right(_Parent(_X)) )
			_Right(_Parent(_X)) = _Y;
		else
			_Left(_Parent(_X)) = _Y;
		
		_Right(_Y) = _X;
		_Parent(_X) = _Y;
	}

	void _Lrotate( _Nodeptr _X )
	{
		_Nodeptr _Y = _Right(_X);
		_Right(_X) = _Left(_Y);
		
		if( _Left(_Y) != _Nil )
			_Parent(_Left(_Y)) = _X;
		
		_Parent(_Y) = _Parent(_X);
		
		if( _X == _Root() )
			_Root() = _Y;
		else if( _X == _Left(_Parent(_X)) )
			_Left(_Parent(_X)) = _Y;
		else
			_Right(_Parent(_X)) = _Y;
		
		_Left(_Y) = _X;
		_Parent(_X) = _Y;
	}

	inline static _Nodeptr _Max(_Nodeptr _P)
	{
		while (_Right(_P) != _Nil)
			_P = _Right(_P);
		
		return (_P); 
	}
	
	inline static _Nodeptr _Min(_Nodeptr _P)
	{
		while (_Left(_P) != _Nil)
			_P = _Left(_P);
		return (_P);
	}

	inline static System::Types::sBool _key_compare( _Nodeptr _X, _Nodeptr _Y )
	{
		return _COMPARE::Small( _Key( _X ), _Key( _Y ) );
	}

	inline static System::Types::sBool _key_compare( const _KEY& _X, _Nodeptr _Y )
	{
		return _COMPARE::Small( _X, _Key( _Y ) );
	}

	inline static System::Types::sBool _key_compare( _Nodeptr _X, const _KEY& _Y )
	{
		return _COMPARE::Small( _Key( _X ), _Y );
	}

	inline _Nodeptr _begin() const
	{
		return _Lmost();
	}

	inline _Nodeptr _end() const
	{
		return _Head;
	}

	static void _Dec( _Nodeptr& _Ptr )
	{
		if (_Color(_Ptr) == _Red && _Parent(_Parent(_Ptr)) == _Ptr)
			_Ptr = _Right(_Ptr);
		else if (_Left(_Ptr) != _Nil)
			_Ptr = _Max(_Left(_Ptr));
		else
		{
			_Nodeptr _P;
			while (_Ptr == _Left(_P = _Parent(_Ptr)))
				_Ptr = _P;
			_Ptr = _P;
		}
	}

	static void _Inc( _Nodeptr& _Ptr )
	{
		if (_Right(_Ptr) != _Nil)
			_Ptr = _Min(_Right(_Ptr));
		else
		{
			_Nodeptr _P;
			while (_Ptr == _Right(_P = _Parent(_Ptr)))
				_Ptr = _P;
			if (_Right(_Ptr) != _P)
				_Ptr = _P;
		}
	}

	_Nodeptr _Insert( _Nodeptr _X, _Nodeptr _Y, const _KEY& _K )
	{
		_Nodeptr _Z = _Buynode( _Y, _Red );
		_Left(_Z) = _Nil; 
		_Right(_Z) = _Nil;
		_Key(_Z) = _K;
		++_Size;

		if (_Y == _Head || _X != _Nil || _key_compare( _Z, _Y ) )
		{
			_Left(_Y) = _Z;
			if( _Y == _Head )
			{
				_Root() = _Z;
				_Rmost() = _Z;
			}
			else if( _Y == _Lmost() )
				_Lmost() = _Z;
		}
		else
		{
			_Right(_Y) = _Z;
			if( _Y == _Rmost() )
				_Rmost() = _Z;
		}
		
		for (_X = _Z; _X != _Root() && _Color(_Parent(_X)) == _Red; )
		{
			if (_Parent(_X) == _Left(_Parent(_Parent(_X))))
			{
				_Y = _Right(_Parent(_Parent(_X)));
				if (_Color(_Y) == _Red)
				{
					_Color(_Parent(_X)) = _Black;
					_Color(_Y) = _Black;
					_Color(_Parent(_Parent(_X))) = _Red;
					_X = _Parent(_Parent(_X));
				}
				else
				{
					if (_X == _Right(_Parent(_X)))
					{
						_X = _Parent(_X);
						_Lrotate(_X);
					}
					
					_Color(_Parent(_X)) = _Black;
					_Color(_Parent(_Parent(_X))) = _Red;
					_Rrotate(_Parent(_Parent(_X)));
				}
			}
			else
			{
				_Y = _Left(_Parent(_Parent(_X)));
				if (_Color(_Y) == _Red)
				{
					_Color(_Parent(_X)) = _Black;
					_Color(_Y) = _Black;
					_Color(_Parent(_Parent(_X))) = _Red;
					_X = _Parent(_Parent(_X));
				}
				else
				{
					if (_X == _Left(_Parent(_X)))
					{
						_X = _Parent(_X);
						_Rrotate(_X);
					}
					
					_Color(_Parent(_X)) = _Black;
					_Color(_Parent(_Parent(_X))) = _Red;
					_Lrotate(_Parent(_Parent(_X)));
				}
			}
		}
                
		_Color(_Root()) = _Black;
                
		return _Z;
	}

	_Nodeptr _Insert( const _KEY& _K, System::Types::sBool& bInserted )
	{
		bInserted = System::Types::sTrue;

		_Nodeptr _X = _Root();
		_Nodeptr _Y = _Head;
		System::Types::sBool _Ans = System::Types::sTrue;

		while( _X != _Nil )
		{
			_Y = _X;
			_Ans = _key_compare( _K, _X );
			_X = _Ans ? _Left(_X) : _Right(_X);
		}

		if( _Multi )
			return _Insert( _X, _Y, _K );
		
		_Nodeptr _P = _Y;
		if (!_Ans)
			;
		else if ( _P == _Lmost() )
			return _Insert(_X, _Y, _K );
		else
			_Dec( _P );
		if( _key_compare( _P, _K ) )
			return _Insert(_X, _Y, _K);

		bInserted = System::Types::sFalse;

		return _P;
	}

	void _Erase( _Nodeptr _X )
	{
		for ( _Nodeptr _Y = _X; _Y != _Nil; _X = _Y )
		{
			_Erase(_Right(_Y));
			_Y = _Left(_Y);
			_Freenode(_X);
		}
	}

	_Nodeptr erase( _Nodeptr _P )
	{
		_Nodeptr _X;
		_Nodeptr _Y = _P;
		_Nodeptr _Z = _Y;
		_Inc( _P );

		if (_Left(_Y) == _Nil)
			_X = _Right(_Y);
		else if (_Right(_Y) == _Nil)
			_X = _Left(_Y);
		else
			_Y = _Min(_Right(_Y)), _X = _Right(_Y);
		
		if (_Y != _Z)
		{
			_Parent(_Left(_Z)) = _Y;
			_Left(_Y) = _Left(_Z);
			
			if (_Y == _Right(_Z))
				_Parent(_X) = _Y;
			else
			{
				_Parent(_X) = _Parent(_Y);
				_Left(_Parent(_Y)) = _X;
				_Right(_Y) = _Right(_Z);
				_Parent(_Right(_Z)) = _Y;
			}

			if (_Root() == _Z)
				_Root() = _Y;
			else if (_Left(_Parent(_Z)) == _Z)
				_Left(_Parent(_Z)) = _Y;
			else
				_Right(_Parent(_Z)) = _Y;
			
			_Parent(_Y) = _Parent(_Z);

			_Redbl tmp = _Color(_Y);
			_Color(_Y) = _Color(_Z);
			_Color(_Z) = tmp;

			_Y = _Z; 
		}
		else
		{
			_Parent(_X) = _Parent(_Y);
			
			if (_Root() == _Z)
				_Root() = _X;
			else if (_Left(_Parent(_Z)) == _Z)
				_Left(_Parent(_Z)) = _X;
			else
				_Right(_Parent(_Z)) = _X;
			
			if (_Lmost() != _Z)
				;
			else if (_Right(_Z) == _Nil)
				_Lmost() = _Parent(_Z);
			else
				_Lmost() = _Min(_X);
			
			if (_Rmost() != _Z)
				;
			else if (_Left(_Z) == _Nil)
				_Rmost() = _Parent(_Z);
			else
				_Rmost() = _Max(_X);
		}
                
		if (_Color(_Y) == _Black)
		{
			while (_X != _Root() && _Color(_X) == _Black)
				if (_X == _Left(_Parent(_X)))
				{
					_Nodeptr _W = _Right(_Parent(_X));
					if (_Color(_W) == _Red)
					{
						_Color(_W) = _Black;
						_Color(_Parent(_X)) = _Red;
						_Lrotate(_Parent(_X));
						_W = _Right(_Parent(_X));
					}

					if (_Color(_Left(_W)) == _Black && _Color(_Right(_W)) == _Black)
					{
						_Color(_W) = _Red;
						_X = _Parent(_X);
					}
					else
					{
						if (_Color(_Right(_W)) == _Black)
						{
							_Color(_Left(_W)) = _Black;
							_Color(_W) = _Red;
							_Rrotate(_W);
							_W = _Right(_Parent(_X));
						}
						_Color(_W) = _Color(_Parent(_X));
						_Color(_Parent(_X)) = _Black;
						_Color(_Right(_W)) = _Black;
						_Lrotate(_Parent(_X));
						break;
					}
				}
				else
				{
					_Nodeptr _W = _Left(_Parent(_X));
					if (_Color(_W) == _Red)
					{
						_Color(_W) = _Black;
						_Color(_Parent(_X)) = _Red;
						_Rrotate(_Parent(_X));
						_W = _Left(_Parent(_X));
					}
					if (_Color(_Right(_W)) == _Black && _Color(_Left(_W)) == _Black)
					{
						_Color(_W) = _Red;
						_X = _Parent(_X);
					}
					else
					{
						if (_Color(_Left(_W)) == _Black)
						{
							_Color(_Right(_W)) = _Black;
							_Color(_W) = _Red;
							_Lrotate(_W);
							_W = _Left(_Parent(_X));
						}
						
						_Color(_W) = _Color(_Parent(_X));
						_Color(_Parent(_X)) = _Black;
						_Color(_Left(_W)) = _Black;
						_Rrotate(_Parent(_X));
						break;
					}
				}
				
			_Color(_X) = _Black;
		}

		_Freenode(_Y);
		--_Size;
		return (_P);
	}

	_Nodeptr erase( _Nodeptr _F, _Nodeptr _L )
	{
		if( Size() == 0 || _F != _begin() || _L != _end() )
		{
			while (_F != _L)
			{
				_Nodeptr tmp = _F;
				_Inc( _F );
				erase(tmp);
			}
			return (_F);
		}
		else
		{
			_Erase(_Root());
			_Root() = _Nil, _Size = 0;
			_Lmost() = _Head, _Rmost() = _Head;
			
			return (_begin());
		}
	}

	_Nodeptr _Copy(_Nodeptr _X, _Nodeptr _P)
	{
		_Nodeptr _R = _X;
		for (; _X != _Nil; _X = _Left(_X))
		{
			_Nodeptr _Y = _Buynode(_P, _Color(_X));
			if (_R == _X)
				_R = _Y;
			
			_Right(_Y) = _Copy(_Right(_X), _Y);
			_Key(_Y) = _Key(_X);
			_Value(_Y) = _Value(_X);
			_Left(_P) = _Y;
			_P = _Y;
		}
		
		_Left(_P) = _Nil;
		return (_R);
	}

	void _Copy( const BTree<_KEY, _TYPE, _COMPARE >& _X )
	{
		_Root() = _Copy(_X._Root(), _Head);
		_Size = _X.Size();
		
		if (_Root() != _Nil)
		{
			_Lmost() = _Min(_Root());
			_Rmost() = _Max(_Root());
		}
		else
			_Lmost() = _Head, _Rmost() = _Head;
	}

public:

	BTree( System::Types::sBool bMulti = false ) :
		_Multi( bMulti )
	{
		_Init();
	}

	BTree( const BTree<_KEY, _TYPE, _COMPARE >& v ) :
		_Multi( v._Multi )
	{
		_Init();
		_Copy( v );
	}

#ifdef _SLIB_CPP11
	BTree( BTree<_KEY, _TYPE, _COMPARE >&& v )
	{
		_Head = v._Head;
		_Size = v._Size;
		_Multi = v._Multi;

		v.Init();
	}

	void operator = ( BTree<_KEY, _TYPE, _COMPARE >&& v )
	{
		Clear();
		_Freenode(_Head);

		_Head = v._Head;
		_Size = v._Size;
		_Multi = v._Multi;

		v.Init();
	}
#endif

	~BTree()
	{
		Clear();
		_Freenode(_Head);
		_Head = 0, _Size = 0;
	}

	void operator = ( const BTree<_KEY, _TYPE, _COMPARE >& v )
	{
		if( this != &v )
		{
			erase( _begin(), _end());
			_Copy(v);
		}
	}

	/**
	 *	Return collection size
	 */
	inline System::Types::sUInt Size() const
	{
		return _Size;
	}

	/**
	 *	Add item to tree
	 */
	inline System::Types::sBool AddI( const _KEY k, const _TYPE v )
	{
		return AddR( k, v );
	}

	/**
	 *	Add item to tree
	 */
	inline System::Types::sBool AddR( const _KEY& k, const _TYPE& v )
	{
		System::Types::sBool ins;

		_Nodeptr p = _Insert( k, ins );
		if( ins )
			p->_content._Value = v;

		return ins;
	}

	/**
	 * Add element to tree	
	 */
	inline _TYPE& AddR( const _KEY& k )
	{
		System::Types::sBool ins;
		_Nodeptr p = _Insert( k, ins );

		return p->_content._Value;
	}

	/**
	 *	Find item
	 */
	inline _TYPE* Find( const _KEY& key )
	{
		_Nodeptr p = _Lbound( key );
		if( p == _Head || _key_compare( key, p ) )
			return NULL;
		
		return &p->_content._Value;
	}

	/**
	 *	Find item
	 */
	const _TYPE* Find( const _KEY& key ) const
	{
		_Nodeptr p = _Lbound( key );
		if( p == _Head || _key_compare( key, p ) )
			return NULL;
		
		return &p->_content._Value;
	}

	/**
	 *	Erase element with key
	 */
	inline System::Types::sBool Erase( const _KEY& _X )
	{
		_Nodeptr first = _Lbound( _X );
		_Nodeptr second = _Ubound( _X );

		if( first == second )
			return System::Types::sFalse;

		erase( first, second );

		return System::Types::sTrue;
	}

	inline System::Types::sBool Erase( const _KEY& _X, _TYPE& val )
	{
		_Nodeptr first = _Lbound( _X );
		_Nodeptr second = _Ubound( _X );

		if( first == second )
			return System::Types::sFalse;

		val = first->_content._Value;
		erase( first, second );

		return System::Types::sTrue;
	}


	inline void Clear()
	{
		erase(_begin(), _end());
	}

	/**
	 *
	 */
	class ConstIterator
	{
	public:
		inline ConstIterator( const ConstIterator& src ) :
			_p( src._p )
		{
		}

		inline void operator = ( const ConstIterator& src )
		{
			_p = src._p;
		}

		inline void operator ++() const
		{
			__S_ASSERT( _p != NULL );
			BTree<_KEY, _TYPE, _COMPARE >::_Inc( _p );
		}

		inline void operator --() const
		{
			__S_ASSERT( _p != NULL );
			BTree<_KEY, _TYPE, _COMPARE >::_Dec( _p );
		}

		inline System::Types::sBool operator == ( const ConstIterator& src ) const
		{
			return _p == src._p;
		}

		inline System::Types::sBool operator != ( const ConstIterator& src ) const
		{
			return _p != src._p;
		}

		inline const _TYPE& Value() const
		{
			__S_ASSERT( _p != NULL );
			return BTree<_KEY, _TYPE, _COMPARE >::_Value( _p );
		}

		inline const _KEY& Key() const
		{
			__S_ASSERT( _p != NULL );
			return BTree<_KEY, _TYPE, _COMPARE >::_Key( _p );
		}
	protected:
		inline ConstIterator( _Nodeptr p ) :
			_p( p )
		{
		}

	protected:
		mutable _Nodeptr	_p;
		friend class BTree<_KEY, _TYPE, _COMPARE >;
	};

	/**
	 *
	 */
	class Iterator : public ConstIterator
	{
	public:
		inline _TYPE& Value()
		{
			__S_ASSERT( ConstIterator::_p != NULL );
			return BTree<_KEY, _TYPE, _COMPARE >::_Value( ConstIterator::_p );
		}

	private:
		inline Iterator( _Nodeptr p ) :
			ConstIterator( p )
		{
		}
		friend class BTree<_KEY, _TYPE, _COMPARE >;
	};

	/**
	 * Begin
	 */
	inline Iterator Begin()
	{
		return Iterator( _begin() );
	}

	/**
	 * Begin
	 */
	inline ConstIterator ConstBegin() const
	{
		return ConstIterator( _begin() );
	}

	/**
	 *	End
	 */
	inline Iterator End()
	{
		return Iterator( _end() );
	}

	/**
	 *	End
	 */
	inline ConstIterator ConstEnd() const
	{
		return ConstIterator( _end() );
	}

private:
	_Nodeptr					_Head;
	System::Types::sInt			_Size;
	System::Types::sBool		_Multi;

private:
	static _Nodeptr				_Nil;
	static _BNode				_NullNode;

	friend class ConstIterator;
	friend class Iterator;
};

template< typename _KEY, typename _TYPE, typename _COMPARE >
typename BTree<_KEY, _TYPE, _COMPARE>::_BNode BTree<_KEY, _TYPE, _COMPARE>::_NullNode = 
{ 0, 0, 0, _Black }; 

template< typename _KEY, typename _TYPE, typename _COMPARE >
typename BTree<_KEY, _TYPE, _COMPARE>::_Nodeptr BTree<_KEY, _TYPE, _COMPARE>::_Nil = 
	(typename BTree<_KEY, _TYPE, _COMPARE>::_Nodeptr)&_NullNode; 

}
