/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_serv_textedit.h
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

#ifndef _RD3_SERV_TEXTEDIT_INC_
#define _RD3_SERV_TEXTEDIT_INC_


#include "rd3_service.h"

namespace Rd3
{

/**
 * ITextEdit
 */
class ITextEdit
{
public:
	virtual void DeleteBack() = 0;
	virtual void AddText( const sString& text ) = 0;
};

/**
 * ITextEditService
 */
class TextEditService : public Service
{
private:
	typedef Service _BaseClass;
public:
	
	TextEditService( Render* owner, const sString& objectName ):
		_BaseClass( owner, objectName )
	{
	}
	
	static sString ServiceType() { return _S("TextEditService:"); }
	
	virtual void BeginEdit( ITextEdit* pEdit ) = 0;
	virtual void EndEdit( ITextEdit* pEdit ) = 0;
};

}

#endif // _RD3_MSG_TEXTEDIT_INC_