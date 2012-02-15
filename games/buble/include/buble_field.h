/////////////////////////////////////////////////////////////////////
//  File Name               : buble_field.h
//	Created                 : 30 1 2012   0:05
//	File path               : games/buble/include
//	Author                  : Alexandru Motriuc
//  Platform Independent    : 0%
//	Library                 : 
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

#ifndef _BUBLE_FIELD_INC_
#define _BUBLE_FIELD_INC_

#include "ed3_object.h"
#include "rd3_resobj.h"

/**
 * BubleField
 */
class BubleField : public Ed3::d3Object
{
private:
	typedef Ed3::d3Object _BaseClass;
public:
	/**
	 *
	 */
	BubleField();
protected:
	/**
	 *
	 */
	virtual void LoadFromXML( const Xml::BaseDomNode& element, Ed3::LoadDataParams& loadParams ) throws_error;
	
	/**
	 *
	 */
	virtual void Initialize( Rd3::Render& render ) throws_error;
	
	/**
	 *
	 */
	virtual void Render( const Ed3::d3RenderData& renderData );
	
private:
	Rd3::use_resource<Rd3::Texture>			_tileTexture;
	Rd3::use_resource<Rd3::VertexBuffer>	_vb;
	Rd3::use_resource<Rd3::Effect>			_effect;
	
	sInt							_tileWidth;
	sInt							_tileHeight;
	sInt							_tileCountW;
	sInt							_tileCountH;
	
	sInt							_fieldWidth;
	sInt							_fieldHeight;
	sVector<sInt>					_fieldTiles;
	
	
	void LoadFieldFromFile( const sString& path, Ed3::LoadDataParams& loadParams ) throws_error;
};


#endif // _BUBLE_FIELD_INC_