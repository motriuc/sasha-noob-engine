/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_ui_edit.h
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

#ifndef _ED3_UI_EDIT_INC_
#define _ED3_UI_EDIT_INC_

#include "ed3_object_d2.h"

#include "rd3_serv_textedit.h"

namespace Ed3
{

/**
 * uiLabel
 */
class uiEdit : public d2Object, private Rd3::ITextEdit
{
	_SLIB_RUNTIME( Ed3, uiEdit, d2Object )
public:
	/**
	 *
	 */
	uiEdit( const sString& name = _S("") );

	/**
	 *
	 */
	~uiEdit();

protected:
	virtual void Initialize( Rd3::Render& render ) throws_error;
	virtual void AI( d3EngineData& edata );
	
	virtual void Render2D( const d3RenderData& renderData );
	virtual sBool LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;

	virtual void OnGestureEvent( Rd3::EngineData& edata, const Rd3::GestureEvent& e );
	
private:
	// from ITextEdit
	virtual void DeleteBack();
	virtual void AddText( const sString& text );
	
private:
	sString	_text;
	sBool	_pressed;
	sBool	_textChanged;
	
	Rd3::use_resource<Rd3::TextEditService>	_editService;
};

}

#endif // _ED3_UI_EDIT_INC_