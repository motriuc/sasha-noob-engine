/**
 * Shared Ptr test
 */
BEGIN_TEST( ptr_weak, "Weak Pointer test : s_system_ptr_weak.h" )

	//-------------------------------------------------------------------
	CHECK( "ptr_weak()" )
	{
		ptr_weak<sInt> p;
		
		CONDITION( p.RefCount() == 1 )
		CONDITION( p.WeakRefCount() == 0 )
		CONDITION( p.IsNull() )
	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "ptr_weak( const ptr_shared& )" )
	{
		ptr_shared<sInt> p( new sInt() );
		ptr_weak<sInt> pw( p );
		
		CONDITION( p.RefCount() == 1 )
		CONDITION( p.WeakRefCount() == 1 )
		CONDITION( pw.RefCount() == 1 )
		CONDITION( pw.WeakRefCount() == 1 )
		CONDITION( pw == p );
	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "ptr_weak( const ptr_shared& )" )
	{
		ptr_shared<sInt> p( new sInt() );
		ptr_weak<sInt> pw1( p );
		ptr_weak<sInt> pw2( pw1 );
		
		CONDITION( p.RefCount() == 1 )
		CONDITION( p.WeakRefCount() == 2 )
		CONDITION( pw1.RefCount() == 1 )
		CONDITION( pw1.WeakRefCount() == 2 )
		CONDITION( pw2.RefCount() == 1 )
		CONDITION( pw2.WeakRefCount() == 2 )
		CONDITION( pw2 == pw1 )
	}
	END
	//-------------------------------------------------------------------



	//-------------------------------------------------------------------
	CHECK( "~ptr_weak()" )
	{
		ptr_weak<TestAllocateObject> pw1;
		{
			ptr_shared<TestAllocateObject> p( new TestAllocateObject() );
			
			CONDITION( TestAllocateObject::step == TestAllocateObject::New )
			CONDITION( p.RefCount() == 1 )
			CONDITION( p.WeakRefCount() == 0 )
			
			pw1 = p;

			CONDITION( TestAllocateObject::step == TestAllocateObject::New )
			CONDITION( p.RefCount() == 1 )
			CONDITION( p.WeakRefCount() == 1 )

			{
				ptr_weak<TestAllocateObject> pw2( p );
				CONDITION( TestAllocateObject::step == TestAllocateObject::New )
				CONDITION( p.RefCount() == 1 )
				CONDITION( p.WeakRefCount() == 2 )
			}

			CONDITION( TestAllocateObject::step == TestAllocateObject::New )
			CONDITION( p.RefCount() == 1 )
			CONDITION( p.WeakRefCount() == 1 )
		}
		CONDITION( TestAllocateObject::step == TestAllocateObject::Free )
		CONDITION( pw1.RefCount() == 0 )
		CONDITION( pw1.WeakRefCount() == 1 )
	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "ptr_weak::IsNull" )
	{
		ptr_weak<TestAllocateObject> pw;
		CONDITION( pw.IsNull() );
		{
			ptr_shared<TestAllocateObject> p( new TestAllocateObject() );
			pw = p;
			CONDITION( !pw.IsNull() );
		}
		CONDITION( pw.IsNull() );
	}
	END
	//-------------------------------------------------------------------


END_TEST