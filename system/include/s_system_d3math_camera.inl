/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_d3math_camera.inl
//  Created                 : 22 1 2011   22:28
//  File path               : SLibF\system\Include
//  Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//  Library                 : 
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

inline void d3Camera::GetProjection( d3Matrix& prj ) const
{
	prj.SetPerspectiveFovLH( _fFov, _fAspect, _fNearPlane, _fFarPlane );
}

inline void d3Camera::GetView( d3Matrix& view ) const
{
	view.SetLookAtLH( _pPosition, _vLookAt, _vWorldUp );
}

inline void d3Camera::Move( const d3Vector& v )
{
	_pPosition += v;

	_bChanged = sTrue;
}

inline void d3Camera::MoveForward( d3Float f )
{
	d3Vector v( _vLookAt );
	v *= f;
	_pPosition += v;

	_bChanged = sTrue;
}

inline void d3Camera::MoveUp( d3Float f )
{
	d3Vector v( _vWorldUp );
	v *= f;
	_pPosition += v;

	_bChanged = sTrue;
}

inline void d3Camera::MoveLeft( d3Float f )
{
	d3Vector v;
	d3Vector::CrossProduct( v, _vLookAt, _vWorldUp );
	v = v.UnitVector();

	v *= f;
	_pPosition += v;

	_bChanged = sTrue;
}

inline void d3Camera::RotateLeft( d3Float f )
{
	d3Matrix tr;
	tr.SetRotate( _vWorldUp, -f );
	d3Vector::Mul( _vLookAt, _vLookAt, tr );

	_bChanged = sTrue;
}

inline void d3Camera::RotateUp( d3Float f )
{
	d3Vector v;
	d3Vector::CrossProduct( v, _vLookAt, _vWorldUp );
	v = v.UnitVector();

	d3Matrix tr;
	tr.SetRotate( v, f );

	d3Vector::Mul( _vLookAt, _vLookAt, tr );
	d3Vector::Mul( _vWorldUp, _vWorldUp, tr );

	_bChanged = sTrue;
}
  
inline void d3Camera::RotateView( d3Float f )
{
	d3Matrix tr;
	tr.SetRotate( _vLookAt, f );
	d3Vector::Mul( _vWorldUp, _vWorldUp, tr );

	_bChanged = sTrue;
}

inline void d3Camera::SetPosition( const d3Point& p )
{
	_pPosition = p;

	_bChanged = sTrue;
}

inline void d3Camera::SetLookAt( const d3Vector& v )
{
	_vLookAt = v.UnitVector();

	_bChanged = sTrue;
}

inline void d3Camera::SetUp( const d3Vector& v )
{
	_vWorldUp = v.UnitVector();

	_bChanged = sTrue;
}

inline void d3Camera::SetFov( d3Float v )
{
	_fFov = v;
	_bChanged = sTrue;
}

inline void d3Camera::SetAspect( d3Float v )
{
	_fAspect = v;
	_bChanged = sTrue;
}

inline void d3Camera::SetNearPlane( d3Float v )
{
	_fNearPlane = v;
	_bChanged = sTrue;
}
inline void d3Camera::SetFarPlane( d3Float v )
{
	_fFarPlane = v;
	_bChanged = sTrue;
}

inline d3Float d3Camera::GetNearPlane() const
{
	return _fNearPlane;
}

inline d3Float d3Camera::GetFarPlane() const
{
	return _fFarPlane;
}

inline d3Float d3Camera::GetAspect() const
{
	return _fAspect;
}

inline d3Float d3Camera::GetFov() const
{
	return _fFov;
}

inline d3Camera::d3Camera( const d3Camera& src ) :
	_pPosition( src._pPosition ),
	_vLookAt( src._vLookAt ),
	_vWorldUp( src._vWorldUp ),
	_fFov( src._fFov ),
	_fAspect( src._fAspect ),
	_fNearPlane( src._fNearPlane ),
	_fFarPlane( src._fFarPlane ),
	_bChanged( sTrue )
{
}

inline void d3Camera::operator = ( const d3Camera& src )
{
	_pPosition = src._pPosition;
	_vLookAt = src._vLookAt;
	_vWorldUp = src._vWorldUp;
	_fFov = src._fFov;
	_fAspect = src._fAspect;
	_fNearPlane = src._fNearPlane;
	_fFarPlane = src._fFarPlane;
	_bChanged = sTrue;
}

inline const d3Point& d3Camera::GetPosition() const
{
	return _pPosition;
}

inline sBool d3Camera::ChangedFromLastCommit() const
{
	return _bChanged;
}

inline void d3Camera::CommitChanges() const
{
	_bChanged = sFalse;
}

