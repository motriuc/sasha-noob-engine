/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_ui_image.h
//  Created             : 1 4 2012
//  Author              : Motriuc Alexandru
//  File Path           : SLibF\engine3d\include\ui
//  System independent  : 0%
//  Library             : 
//
//  Purpose:
//    
//
/////////////////////////////////////////////////////////////////////
//  Modification History :
//
/////////////////////////////////////////////////////////////////////

#ifndef _ED3_UI_IMAGE_INC_
#define _ED3_UI_IMAGE_INC_

#include "ed3_object_d2.h"

namespace Ed3
{

/**
 * uiImage
 */
class uiImage : public d2Object
{
private:
	typedef d2Object _BaseClass;
public:
	/**
	 * uiImage
	 */
	uiImage( const sString& name = _S("") );
	~uiImage();

protected:
	virtual sBool LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	virtual void Render2D( const d3RenderData& renderData );
private:
	Rd3::use_resource<Rd3::Texture>		_texture;
	d2Vector							_tx1;
	d2Vector							_tx2;
};

}

#endif // _ED3_UI_IMAGE_INC_
