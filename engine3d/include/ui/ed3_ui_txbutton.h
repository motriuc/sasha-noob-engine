/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_ui_txbutton.h
//  Created             : 20 3 2012
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

#ifndef _ED3_UI_TXBUTTON_INC_
#define _ED3_UI_TXBUTTON_INC_

#include "ed3_ui_button.h"

namespace Ed3
{

/**
 * uiTxButton
 */
class uiTxButton : public uiButton
{
private:
	typedef uiButton _BaseClass; 
public:
	/**
	 *
	 */
	uiTxButton( const sString& name = _S("") );

	/**
	 *
	 */
	~uiTxButton();

protected:
	virtual void Render2D( const d3RenderData& renderData );

	virtual sBool LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
private:
	Rd3::use_resource<Rd3::Texture>		_txUp;
	Rd3::use_resource<Rd3::Texture>		_txDown;

	d2Vector							_txUp1;
	d2Vector							_txUp2;

	d2Vector							_txDown1;
	d2Vector							_txDown2;
};

}

#endif // _ED3_UI_TXBUTTON_INC_