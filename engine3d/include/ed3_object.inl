
inline void d3Object::SetState( sUInt uState )
{
	_objectState = uState;
}

inline sBool d3Object::HasState( ObjectState uState ) const
{
	return (_objectState & uState ) > 0;
}

inline void d3Object::AddState( ObjectState uState )
{
	_objectState |= uState;
}

inline void d3Object::RemoveState( ObjectState uState )
{
	_objectState &= ~uState;
}

inline sBool d3Object::IsVisible() const
{
	return _objectState & OBS_VISIBLE;
}

inline sBool d3Object::IsSuspended() const
{
	return _objectState & OBS_SUSPEND;
}

inline sBool d3Object::HasTransformationMatrix() const
{
	return _objectState & OBS_TRANSFORMATION_MATRIX;
}

inline sBool d3Object::HasBoundingBox() const
{
	return _objectState & OBS_BOUNDINGBOX;
}

inline const sString& d3Object::GetName() const
{
	return _name;
}

inline d3ObjectContiner* d3Object::GetParent()
{
	return _parent;
}

inline const d3ObjectContiner* d3Object::GetParent() const
{
	return _parent;
}

inline void d3Object::SetActionState( ObjectActionState s )
{
	__S_ASSERT( s != _objectActionState );
	_objectActionState = s;
}

inline void d3Object::DoAI( d3EngineData& edata )
{
	__S_ASSERT( _objectActionState == OBAS_IDLE );
	SetActionState( OBAS_AI );
	
	AI( edata );

#ifdef ED3_ENGINE_USE_LUA	
	LuaCallAI( edata );
#endif

	__S_ASSERT( _objectActionState == OBAS_AI );
	SetActionState( OBAS_IDLE );
}

inline void d3Object::DoInitialize( Rd3::Render& render ) throws_error
{
	__S_ASSERT( _objectActionState == OBAS_IDLE );
	SetActionState( OBAS_INIT );
	
	Initialize( render );
	
#ifdef ED3_ENGINE_USE_LUA	
	LuaCallInit( render );
#endif
	
	__S_ASSERT( _objectActionState == OBAS_INIT );
	SetActionState( OBAS_IDLE );
}

inline void d3Object::DoUninitalize( Rd3::Render& render )
{
	__S_ASSERT( _objectActionState == OBAS_IDLE );
	SetActionState( OBAS_FREE );
	
	Uninitialize( render );
	
	__S_ASSERT( _objectActionState == OBAS_INIT );
	SetActionState( OBAS_IDLE );
}

inline const d3Matrix& d3Object::GetTransformationMatrix() const
{
	return _transformationMatrix;
}

inline void d3Object::DoLoadFromXML(
    const Xml::BaseDomNode& element,
    LoadDataParams& loadParams
  )
{
	__S_ASSERT( _objectActionState == OBAS_IDLE );
	SetActionState( OBAS_LOADING );
	
	LoadFromXML( element, loadParams );

	__S_ASSERT( _objectActionState == OBAS_LOADING );
	SetActionState( OBAS_IDLE );
}

inline const d3AABBox& d3Object::GetBoundingBox() const
{
	return _boundingBox;
}

inline void d3Object::ApplyTranformation( const d3Matrix& m )
{
	d3Matrix tmp;
	d3Matrix::Mul( tmp, m, _transformationMatrix );
	
	_transformationMatrix = tmp;
	
	_objectState |= OBS_TRANSFORMATION_MATRIX;
}

inline ObjectType::ObjectType d3Object::GetType() const
{
	return _type;
}

