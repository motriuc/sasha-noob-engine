
BEGIN_TEST( sort, "sort test : s_system_cnt_sort.h" )

	//-------------------------------------------------------------------
	CHECK( "Sort2Elements" )
	{
		{
			Array<sInt, 2> arr;
			arr[0] = 10;
			arr[1] = 11;

			Sort< Array<sInt, 2> >::Sort2Elements( arr, 0 );
			CONDITION( arr[0] == 10 )
			CONDITION( arr[1] == 11 )
		}
		{
			Array<sInt, 2> arr;
			arr[0] = 11;
			arr[1] = 10;

			Sort< Array<sInt, 2> >::Sort2Elements( arr, 0 );
			CONDITION( arr[0] == 10 )
			CONDITION( arr[1] == 11 )
		}

	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "Sort3Elements" )
	{
		typedef Array<sInt, 3> Array3;

		{
			Array3 arr;
			arr[0] = 0;
			arr[1] = 1;
			arr[2] = 2;

			Sort<Array3>::Sort3Elements( arr, 0 );
			CONDITION( arr[0] == 0 )
			CONDITION( arr[1] == 1 )
			CONDITION( arr[2] == 2 )
		}

		{
			Array3 arr;
			arr[0] = 0;
			arr[1] = 2;
			arr[2] = 1;

			Sort<Array3>::Sort3Elements( arr, 0 );
			CONDITION( arr[0] == 0 )
			CONDITION( arr[1] == 1 )
			CONDITION( arr[2] == 2 )
		}

		{
			Array3 arr;
			arr[0] = 1;
			arr[1] = 0;
			arr[2] = 2;

			Sort<Array3>::Sort3Elements( arr, 0 );
			CONDITION( arr[0] == 0 )
			CONDITION( arr[1] == 1 )
			CONDITION( arr[2] == 2 )
		}

		{
			Array3 arr;
			arr[0] = 1;
			arr[1] = 2;
			arr[2] = 0;

			Sort<Array3>::Sort3Elements( arr, 0 );
			CONDITION( arr[0] == 0 )
			CONDITION( arr[1] == 1 )
			CONDITION( arr[2] == 2 )
		}

		{
			Array3 arr;
			arr[0] = 2;
			arr[1] = 0;
			arr[2] = 1;

			Sort<Array3>::Sort3Elements( arr, 0 );
			CONDITION( arr[0] == 0 )
			CONDITION( arr[1] == 1 )
			CONDITION( arr[2] == 2 )
		}

		{
			Array3 arr;
			arr[0] = 2;
			arr[1] = 1;
			arr[2] = 0;

			Sort<Array3>::Sort3Elements( arr, 0 );
			CONDITION( arr[0] == 0 )
			CONDITION( arr[1] == 1 )
			CONDITION( arr[2] == 2 )
		}

	}
	END
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	CHECK( "QuickSort" )
	{
		typedef Array<sInt, 10000> Array10000;

		Array10000 arr;
		RMath::Random rnd;

		for( sInt i = 0; i < 10000; i++ )
		{
			arr[i] = rnd.Rand( 500 );
		}

		Sort<Array10000>::QuickSort( arr );

		for( sInt i = 0; i < 10000 - 1; i++ )
		{
			CONDITION( arr[i] <= arr[i+1] )
		}
	}
	END
	//-------------------------------------------------------------------

END_TEST
