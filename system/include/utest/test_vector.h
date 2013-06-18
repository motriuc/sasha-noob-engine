
BEGIN_TEST( vector, "vector test : s_system_cnt_vector.h" )

	//-------------------------------------------------------------------
	CHECK( "sVector()" )
	{
		sVector<sInt> v;
		CONDITION( v.Size() == 0 ) 
		CONDITION( v.Capacity() >= 0 ) 
	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "sVector( sInt size )" )
	{
		sVector<sInt> v( 10 );

		CONDITION( v.Size() == 0 ) 
		CONDITION( v.Capacity() >= 10 ) 
		CONDITION( v.GetBuffer() != NULL )
	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "sVector( sInt size, InputType val )" )
	{
		sVector<sInt> v( 10, 666 );

		CONDITION( v.Size() == 10 ) 
		CONDITION( v.Capacity() >= 10 ) 
		CONDITION( v.GetBuffer() != NULL )

		for( sInt i = 0; i < 10; i++ )
		{
			CONDITION( v[i] == 666 )
		}
	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "sVector( const sVector< _Type >& v )" )
	{
		{
			sVector<sInt> v1;
			sVector<sInt> v2( v1 );

			CONDITION( v1.Size() == 0 ) 
			CONDITION( v1.Capacity() >= 0 ) 
			CONDITION( v2.Size() == 0 ) 
			CONDITION( v2.Capacity() >= 0 ) 
		}
		{
			sVector<sInt> v1( 10, 666 );
			sVector<sInt> v2( v1 );


			CONDITION( v1.Size() == 10 ) 
			CONDITION( v1.Capacity() >= 10 ) 
			CONDITION( v1.GetBuffer() != NULL )

			CONDITION( v2.Size() == 10 ) 
			CONDITION( v2.Capacity() >= 10 ) 
			CONDITION( v2.GetBuffer() != NULL )

			for( sInt i = 0; i < 10; i++ )
			{
				CONDITION( v1[i] == 666 )
				CONDITION( v2[i] == 666 )
			}
		}
	}
	END
	//-------------------------------------------------------------------
	
#ifdef _SLIB_CPP11
	//-------------------------------------------------------------------
	CHECK( "sVector( sVector< _Type >&& v )" )
	{
		{
			sVector<sInt> v1;
			sVector<sInt> v2( T::Move( v1 ) );
		
			CONDITION( v1.Size() == 0 ) 
			CONDITION( v1.Capacity() >= 0 ) 
			CONDITION( v2.Size() == 0 ) 
			CONDITION( v2.Capacity() >= 0 ) 
		}
		{
			sVector<sInt> v1( 10, 666 );
			sVector<sInt> v2( T::Move( v1 ) );


			CONDITION( v1.Size() == 0 ) 
			CONDITION( v1.Capacity() >= 0 ) 

			CONDITION( v2.Size() == 10 ) 
			CONDITION( v2.Capacity() >= 10 ) 
			CONDITION( v2.GetBuffer() != NULL )

			for( sInt i = 0; i < 10; i++ )
			{
				CONDITION( v2[i] == 666 )
			}
		}
	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "void operator = ( sVector< _Type >&& v )" )
	{
		{
			sVector<sInt> v1;
			sVector<sInt> v2;
			v2 = T::Move( v1 );
		
			CONDITION( v1.Size() == 0 ) 
			CONDITION( v1.Capacity() >= 0 ) 
			CONDITION( v2.Size() == 0 ) 
			CONDITION( v2.Capacity() >= 0 ) 
		}
		{
			sVector<sInt> v1( 10, 666 );
			sVector<sInt> v2;
			v2 = T::Move( v1 );


			CONDITION( v1.Size() == 0 ) 
			CONDITION( v1.Capacity() >= 0 ) 

			CONDITION( v2.Size() == 10 ) 
			CONDITION( v2.Capacity() >= 10 ) 
			CONDITION( v2.GetBuffer() != NULL )

			for( sInt i = 0; i < 10; i++ )
			{
				CONDITION( v2[i] == 666 )
			}
		}
	}
	END
	//-------------------------------------------------------------------

#endif // _SLIB_CPP11

	//-------------------------------------------------------------------
	CHECK( "void operator = ( const sVector< _Type >& v )" )
	{
		{
			sVector<sInt> v1;
			sVector<sInt> v2;
			v2 = v1;
		
			CONDITION( v1.Size() == 0 ) 
			CONDITION( v1.Capacity() >= 0 ) 
			CONDITION( v2.Size() == 0 ) 
			CONDITION( v2.Capacity() >= 0 ) 
		}
		{
			sVector<sInt> v1( 10, 666 );
			sVector<sInt> v2;
			v2 = v1;


			CONDITION( v1.Size() == 10 ) 
			CONDITION( v1.Capacity() >= 10 ) 
			CONDITION( v1.GetBuffer() != NULL )

			CONDITION( v2.Size() == 10 ) 
			CONDITION( v2.Capacity() >= 10 ) 
			CONDITION( v2.GetBuffer() != NULL )

			for( sInt i = 0; i < 10; i++ )
			{
				CONDITION( v1[i] == 666 )
				CONDITION( v2[i] == 666 )
			}
		}
	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "sInt Add( InputType item )" )
	{
		sVector<sInt> v;
		sInt p;

		for( sInt i = 0; i < 100; i++ )
		{
			p = v.Add( 100 + i );

			CONDITION( p == i )
			CONDITION( v.Size() ==  i + 1 );
			CONDITION( v[i] == 100 + i )
		}

		for( sInt i = 0; i < 100; i++ )
		{
			CONDITION( v[i] == 100 + i )
		}
	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "sInt AddAt( sInt index, InputType item )" )
	{
		sVector<sInt> v;
		for( sInt i = 0; i < 100; i++ )
		{
			v.Add( 100 + i );
		}


		sInt p1 = v.AddAt( -1, 666 );
		sInt p2 = v.AddAt( 50, 777 );
		sInt p3 = v.AddAt( 10000, 999 );

		CONDITION( p1 == 0 )
		CONDITION( p2 == 50 )
		CONDITION( p3 == 102 )
		CONDITION( v[0] == 666 );
		CONDITION( v[50] == 777 );
		CONDITION( v[102] == 999 );

		for( sInt i = 1; i < 50; i++ )
		{
			CONDITION( v[i] == 100 + i - 1 )
		}

		for( sInt i = 51; i < 102; i++ )
		{
			CONDITION( v[i] == 100 + i - 2 )
		}
	}
	END
	//-------------------------------------------------------------------

END_TEST
