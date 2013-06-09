
/**
 * Shared Ptr test
 */
BEGIN_TEST( ptr_shared, "Shared Pointer test : s_system_ptr_shared.h" )

	//-------------------------------------------------------------------
	CHECK( "ptr_shared()" )
	{
		ptr_shared<sInt> sh_ptr;
		
		CONDITION( sh_ptr.RefCount() == 1 )
		CONDITION( sh_ptr.WeakRefCount() == 0 )
		CONDITION( sh_ptr.IsNull() )
	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "ptr_shared( Type* )" )
	{	
		sInt* ptr = new sInt( 1977 );
		ptr_shared<sInt> sh_ptr( ptr );

		CONDITION( sh_ptr.RefCount() == 1 )
		CONDITION( sh_ptr.WeakRefCount() == 0 )
		CONDITION( *ptr == *sh_ptr )
	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "~ptr_shared" )
	{
		{
			ptr_shared<TestAllocateObject> sh_ptr( new TestAllocateObject() );

			CONDITION( sh_ptr.RefCount() == 1 )
			CONDITION( sh_ptr.WeakRefCount() == 0 )
			CONDITION( TestAllocateObject::step == TestAllocateObject::New )
		}
		CONDITION( TestAllocateObject::step == TestAllocateObject::Free )
	}
	END
	//-------------------------------------------------------------------


	//-------------------------------------------------------------------
	CHECK( "ptr_shared( ptr_shared& )" )
	{
		{
			ptr_shared<TestAllocateObject> sh_ptrA( new TestAllocateObject() );

			CONDITION( sh_ptrA.RefCount() == 1 )
			CONDITION( sh_ptrA.WeakRefCount() == 0 )
			CONDITION( TestAllocateObject::step == TestAllocateObject::New )

			{
				ptr_shared<TestAllocateObject> sh_ptrB( sh_ptrA );

				CONDITION( sh_ptrA.RefCount() == 2 )
				CONDITION( sh_ptrA.WeakRefCount() == 0 )
				CONDITION( sh_ptrB.RefCount() == 2 )
				CONDITION( sh_ptrB.WeakRefCount() == 0 )
				CONDITION( TestAllocateObject::step == TestAllocateObject::New )

				{
					ptr_shared<TestAllocateObject> sh_ptrC( sh_ptrB );

					CONDITION( sh_ptrC.RefCount() == 3)
					CONDITION( sh_ptrC.WeakRefCount() == 0 )
					CONDITION( TestAllocateObject::step == TestAllocateObject::New )
				}
				CONDITION( sh_ptrA.RefCount() == 2 )
				CONDITION( sh_ptrA.WeakRefCount() == 0 )
				CONDITION( TestAllocateObject::step == TestAllocateObject::New )
			}

			CONDITION( sh_ptrA.RefCount() == 1 )
			CONDITION( sh_ptrA.WeakRefCount() == 0 )
			CONDITION( TestAllocateObject::step == TestAllocateObject::New )
		}
		CONDITION( TestAllocateObject::step == TestAllocateObject::Free )
	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "ptr_shared( ptr_weak& )" )
	{
		ptr_weak<TestAllocateObject> pw1;
		ptr_shared<TestAllocateObject> p0( pw1 );
		
		CONDITION( p0.RefCount() == 1 )
		CONDITION( p0.WeakRefCount() == 0 )
		CONDITION( p0.IsNull() )

		{
			ptr_shared<TestAllocateObject> p1( new TestAllocateObject() );
			pw1 = p1;

			ptr_weak<TestAllocateObject> pw2( p1 );

			CONDITION( p1.RefCount() == 1 )
			CONDITION( p1.WeakRefCount() == 2 )
			CONDITION( TestAllocateObject::step == TestAllocateObject::New )

			ptr_shared<TestAllocateObject> p2 = pw2;

			CONDITION( p1.RefCount() == 2 )
			CONDITION( p1.WeakRefCount() == 2 )
			CONDITION( TestAllocateObject::step == TestAllocateObject::New )
		}

		CONDITION( pw1.RefCount() == 0 )
		CONDITION( pw1.WeakRefCount() == 1 )
		
		ptr_shared<TestAllocateObject> p2 = pw1;

		CONDITION( p2.RefCount() == 1 )
		CONDITION( p2.WeakRefCount() == 0 )
		CONDITION( p2.IsNull() )

	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "operator == ( const ptr_shared& )" )
	{
		ptr_shared<sInt> p1;
		ptr_shared<sInt> p2;
		ptr_shared<sInt> p3( new sInt() );
		ptr_shared<sInt> p4( new sInt() );
		ptr_shared<sInt> p5( p1 );
		ptr_shared<sInt> p6( p3 );
		ptr_shared<sInt> p7( p6 );

		CONDITION( p1 == p1 )
		CONDITION( p1 == p2 )
		CONDITION( !(p1 == p3) )
		CONDITION( !(p3 == p4) )
		CONDITION( p1 == p5 )
		CONDITION( p2 == p5 )
		CONDITION( p3 == p6 )
		CONDITION( p7 == p6 )
		CONDITION( p7 == p3 )
	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "operator == ( const ptr_weak& )" )
		ptr_shared<sInt> p1;
		ptr_weak<sInt> p2( p1 );
		ptr_shared<sInt> p3( new sInt() );
		ptr_weak<sInt> p4( p3 );

		ptr_shared<sInt> p5( new sInt() );
		ptr_weak<sInt> p6( p5 );

		CONDITION( p1 == p2 )
		CONDITION( !(p3 == p2) )
		CONDITION( !(p3 == p2) )
		CONDITION( p3 == p4 )
		CONDITION( !(p3 == p6) )

		ptr_weak<sInt> p7;
		{
			ptr_shared<sInt> p8( new sInt() );
			p7 = p8;
		}

		CONDITION( p1 == p7 )
		CONDITION( !(p3 == p7) )
	END
	//-------------------------------------------------------------------



END_TEST