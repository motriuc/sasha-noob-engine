/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_font.h
//	Created                 : 22 1 2012   19:58
//	File path               : SLibF\render3d\include
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

#ifndef _RD3_FONT_H_
#define _RD3_FONT_H_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

#include "rd3_resobj.h"

namespace Rd3
{
	
/**
 * IFontFactory
 */
typedef System::T::IClassFactory2< Font, Render*, const sString& > IFontFactory;

/**
 * Font
 */
class Font : public ResourceObject
{
private:
	typedef ResourceObject _BaseClass;
public:
	
	/**
	 *
	 */
	virtual RenderString* CreateRenderString() = 0;

	/**
	 *
	 */
	virtual void LoadFromXml( const System::Xml::BaseDomNode& node, const Def& def ) throws_error = 0;

public:	
	/**
	 * 
	 */
	static void Register( const sString& name, IFontFactory* pFactory );
	static Font* Create( const sString& name, Render* owner, const sString& objectName );

protected:
	/**
	 *
	 */
	Font( Render* owner, const sString& objectName ); 
private:	
};

}

////////////////////////////////////////////////////////////////////
// Register font factory
////////////////////////////////////////////////////////////////////

#define AUTO_REGISTER_FONT_FACTORY( _name, _class ) \
	static class Factory_Font_Register_##_class : \
		public System::T::ClassFactory2<_class, Rd3::Font, Rd3::Render*, const sString& >\
	{ \
	public: \
		Factory_Font_Register_##_class( ) \
		{ \
			Rd3::Font::Register( _name, this ); \
		} \
	} register_font_##_class;


#endif // _RD3_CONF_H_