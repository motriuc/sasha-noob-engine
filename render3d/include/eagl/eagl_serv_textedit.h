/////////////////////////////////////////////////////////////////////
//  File Name               : eagl_serv_textedit.h
//  Created                 : 1 4 2012   19:58
//  File path               : SLibF\render3d\include
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

#ifndef _EAGL_SERV_TEXTEDIT_INC_
#define _EAGL_SERV_TEXTEDIT_INC_

#ifndef _EAGL_CONF_H_	
	#error eagl_conf.h must be included
#endif

#include "rd3_serv_textedit.h"

namespace Rd3
{
	class EngineData;
}

/**
 * EAGLTextEditService
 */
class EAGLTextEditService : public Rd3::TextEditService
{
private:
	typedef Rd3::TextEditService _BaseClass;
public:
	/**
	 *
	 */
	EAGLTextEditService( Rd3::Render* pRender, const sString& objectName );
	
	virtual void BeginEdit( Rd3::ITextEdit* pEdit );
	virtual void EndEdit( Rd3::ITextEdit* pEdit );
	virtual void Process( Rd3::EngineData& edata );
	
	void AddText( const sString& text );
	void DeleteBack();
	
	
private:
	Rd3::ITextEdit*	_pCurrentTextEdit;
	sString	_text;
	sInt	_backDeleteCount;
};

#endif // _EAGL_SERV_TEXTEDIT_INC_