/**
 * Shared Ptr test
 */
BEGIN_TEST( type_traits, "Type Traits : s_system_t_typetraits.h" )

	// utils
	class TestType
	{

	};

	//-------------------------------------------------------------------
	CHECK( "default type" )
	{
		CONDITION( T::Traits<TestType>::IsBasicType == false )
		CONDITION( T::Traits<TestType>::IsConst == false )
		CONDITION( T::Traits<TestType>::IsDefault == true )
		CONDITION( T::Traits<TestType>::IsReference == false )
		CONDITION( T::Traits<TestType>::IsNumber == false )

	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "reference type" )
		CONDITION( T::Traits<TestType&>::IsBasicType == true )
		CONDITION( T::Traits<TestType&>::IsConst == false )
		CONDITION(T::Traits<TestType&>::IsDefault == true )
		CONDITION( T::Traits<TestType&>::IsReference == true )
		CONDITION( T::Traits<TestType&>::IsNumber == false )

		typedef sInt& refInt;

		CONDITION( T::Traits<refInt>::IsBasicType == true )
		CONDITION( T::Traits<refInt>::IsConst == false )
		CONDITION(T::Traits<refInt>::IsDefault == true )
		CONDITION( T::Traits<refInt>::IsReference == true )
		CONDITION( T::Traits<TestType>::IsNumber == false )
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "const type" )
		CONDITION( T::Traits<const TestType>::IsBasicType == false )
		CONDITION( T::Traits<const TestType>::IsConst == true )
		CONDITION(T::Traits<const TestType>::IsDefault == true )
		CONDITION( T::Traits<const TestType>::IsReference == false )
		CONDITION( T::Traits<const TestType>::IsNumber == false )		
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "const type ref" )
		CONDITION( T::Traits<const TestType&>::IsBasicType == false )
		CONDITION( T::Traits<const TestType&>::IsConst == true )
		CONDITION(T::Traits<const TestType&>::IsDefault == true )
		CONDITION( T::Traits<const TestType&>::IsReference == true )
		CONDITION( T::Traits<const TestType&>::IsNumber == false )		
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "int type" )
		CONDITION( T::Traits<sInt>::IsBasicType == true )
		CONDITION( T::Traits<sInt>::IsConst == false )
		CONDITION(T::Traits<sInt>::IsDefault == false )
		CONDITION( T::Traits<sInt>::IsReference == false )
		CONDITION( T::Traits<sInt>::IsNumber == true )
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "uint type" )
		CONDITION( T::Traits<sUInt>::IsBasicType == true )
		CONDITION( T::Traits<sUInt>::IsConst == false )
		CONDITION(T::Traits<sUInt>::IsDefault == false )
		CONDITION( T::Traits<sUInt>::IsReference == false )
		CONDITION( T::Traits<sUInt>::IsNumber == true )
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "float type" )
		CONDITION( T::Traits<sFloat>::IsBasicType == true )
		CONDITION( T::Traits<sFloat>::IsConst == false )
		CONDITION(T::Traits<sFloat>::IsDefault == false )
		CONDITION( T::Traits<sFloat>::IsReference == false )
		CONDITION( T::Traits<sFloat>::IsNumber == true )
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "double type" )
		CONDITION( T::Traits<sDouble>::IsBasicType == true )
		CONDITION( T::Traits<sDouble>::IsConst == false )
		CONDITION(T::Traits<sDouble>::IsDefault == false )
		CONDITION( T::Traits<sDouble>::IsReference == false )
		CONDITION( T::Traits<sDouble>::IsNumber == true )
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "char type" )
		CONDITION( T::Traits<sChar>::IsBasicType == true )
		CONDITION( T::Traits<sChar>::IsConst == false )
		CONDITION(T::Traits<sChar>::IsDefault == false )
		CONDITION( T::Traits<sChar>::IsReference == false )
		CONDITION( T::Traits<sChar>::IsNumber == false )
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "RemoveReference" )	
		CONDITION( T::Traits<TestType>::IsReference == false )
		CONDITION( T::Traits< T::Traits<TestType>::RemoveReference >::IsReference == false )

		CONDITION( T::Traits<const TestType>::IsReference == false )
		CONDITION( T::Traits< T::Traits<const TestType>::RemoveReference >::IsReference == false )

		CONDITION( T::Traits<TestType&>::IsReference == true )
		CONDITION( T::Traits< T::Traits<TestType>::RemoveReference >::IsReference == false )

		CONDITION( T::Traits<const TestType&>::IsReference == true )
		CONDITION( T::Traits< T::Traits<const TestType>::RemoveReference >::IsReference == false )

	END
	//-------------------------------------------------------------------


END_TEST
