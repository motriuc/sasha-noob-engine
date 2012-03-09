/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_quaternion.inl
//  Created                 : 9 3 2012   14:03
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
//
/////////////////////////////////////////////////////////////////////
//  Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

inline d3Quaternion::d3Quaternion()
{
}

inline d3Quaternion::d3Quaternion( d3Float vx, d3Float vy, d3Float vz, d3Float vw ):
	x( vx ),
	y( vy ),
	z( vz ),
	w( vw )
{
}

inline d3Quaternion::d3Quaternion( d3Float ax, d3Float ay, d3Float az )
{
	ax *= 0.5f;
	ay *= 0.5f;
	az *= 0.5f;

	d3Float sax = FMath::Sin( ax );
	d3Float cax = FMath::Cos( ax );
	d3Float say = FMath::Sin( ay );
	d3Float cay = FMath::Cos( ay );
	d3Float saz = FMath::Sin( az );
	d3Float caz = FMath::Cos( az );

	x = cax * cay * caz + sax * say * saz;
	y = sax * cay * caz - cax * say * saz;
	z = cax * say * caz + sax * cay * saz;
	w = cax * cay * saz - sax * say * caz; 
}

inline d3Float d3Quaternion::Magnitude() const
{
	return FMath::Sqrt( x*x + y*y + z*z );
}

inline void d3Quaternion::Mul( d3Quaternion& r, const d3Quaternion& a, const d3Quaternion& b )
{
	r = d3Quaternion(
		a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
		a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
		a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x,
		a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
	);
}

inline d3Quaternion d3Quaternion::operator * ( const d3Quaternion& b )
{
	d3Quaternion r;
	Mul( r, *this, b );
	return r;
}
