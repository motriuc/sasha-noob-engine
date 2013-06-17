
BEGIN_TEST( map, "map test : s_system_cnt_maps.h" )

	CHECK( "sMap()" )
	{
		sMap<sInt,sInt> v;
		CONDITION( v.Size() == 0 )
		CONDITION( v.Begin() == v.End() )
		CONDITION( v.ConstBegin() == v.ConstEnd() )
	}
	END

	CHECK( "Add( key, val ), sBool Lookup( key, &val )" )
	{
		// simple test
		sMap<sInt,sInt> v;

		CONDITION( v.Add( 100, 100 ) == sTrue )
		CONDITION( v.Add( 100, 101 ) == sFalse )

		CONDITION( v.Add( 200, 200 ) == sTrue )
		CONDITION( v.Add( 200, 201 ) == sFalse )

		CONDITION( v.Add( 10, 10 ) == sTrue )
		CONDITION( v.Add( 10, 11 ) == sFalse )

		CONDITION( v.Add( 50, 50 ) == sTrue )
		CONDITION( v.Add( 50, 51 ) == sFalse )

		CONDITION( v.Add( 500, 500 ) == sTrue )
		CONDITION( v.Add( 500, 501 ) == sFalse )

		CONDITION( v.Add( 300, 300 ) == sTrue )
		CONDITION( v.Add( 300, 301 ) == sFalse )


		sInt ret;
		CONDITION( v.Lookup( 100, ret ) == sTrue && ret == 100 )
		CONDITION( v.Lookup( 200, ret ) == sTrue && ret == 200 )
		CONDITION( v.Lookup( 300, ret ) == sTrue && ret == 300 )
		CONDITION( v.Lookup( 500, ret ) == sTrue && ret == 500 )
		CONDITION( v.Lookup( 10, ret ) == sTrue && ret == 10 )
		CONDITION( v.Lookup( 50, ret ) == sTrue && ret == 50 )

		CONDITION( v.Lookup( 101, ret ) == sFalse )
		CONDITION( v.Lookup( 501, ret ) == sFalse )
		CONDITION( v.Lookup( 201, ret ) == sFalse )
		CONDITION( v.Lookup( 11, ret ) == sFalse )
		CONDITION( v.Lookup( 51, ret ) == sFalse )

	}
	END

END_TEST
