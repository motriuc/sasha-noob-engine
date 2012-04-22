/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_ui_label.h
//  Created             : 23 3 2012
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

#ifndef _ED3_UI_LABEL_INC_
#define _ED3_UI_LABEL_INC_

#include "ed3_object_d2.h"

namespace Ed3
{

/**
 * uiLabel
 */
class uiLabel : public d2Object
{
	_SLIB_RUNTIME( Ed3, uiLabel, d2Object )
public:
	/**
	 *
	 */
	uiLabel( const sString& name = _S("") );

	/**
	 *
	 */
	~uiLabel();

protected:
	virtual void Render2D( const d3RenderData& renderData );
	virtual sBool LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;

private:
	sString	_text;
};

}

#endif // _ED3_UI_LABEL_INC_