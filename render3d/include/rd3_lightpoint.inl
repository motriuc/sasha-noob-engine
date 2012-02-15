////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_lightpoint.inl
//	Created            : 29.1.2011   17:25
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\render3d\include
//  System independent : 0%
//  Library            : 
//
//	Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////

inline LightPoint::LightPoint()
{
}

inline LightPoint::LightPoint( const sRGBColor color, const d3Vector& position ):
	_diffuseColor( color ),
	_specularColor( color ),
	_ambientColor( color ),
	_position( position ),
	_attenuation( 1.0f ),
	_maxLigtiningDistance( 0.0f )
{
}

inline sRGBColor LightPoint::GetDiffuzeColor() const 
{ 
	return _diffuseColor;
}

inline sRGBColor LightPoint::GetSpecularColor() const
{
	return _specularColor;
}

inline sRGBColor LightPoint::GetAmbientColor() const 
{
	return _ambientColor;
}

inline const d3Vector& LightPoint::GetPosition() const 
{ 
	return _position;
}

inline d3Float LightPoint::GetAttenuation() const
{
	return _attenuation; 
}
