/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_after_effect.cpp
//  Created                 : 20 2 2012 
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

#include "rd3afx.h"
#include "rd3_after_effect.h"
#include "rd3_xml_def.h"

using namespace System;

namespace Rd3
{
	
//------------------------------------------------------------------
/**
 * FactoryMap
 */
typedef sMap<sString, IAfterEffectElementFactory* > FactoryMap;
	
/**
 * IAfterEffectElementFactory
 */
class AfterEffectElementFactory : public T::ClassFactoryById1< AfterEffectElement, sString, FactoryMap, Render& >
{
public:
};
	
//------------------------------------------------------------------
AfterEffectElementFactory& g_IAfterEffectElementFactory()
{
	static AfterEffectElementFactory factory;
	return factory;
}

//------------------------------------------------------------------
AfterEffect::AfterEffect( Render* owner, const sString& objectName ) :
	_BaseClass( owner, objectName, ResourceType::E_AFTEREFFECT )
{
}

//------------------------------------------------------------------
void AfterEffect::Register( const sString& name, IAfterEffectElementFactory* pFactory )
{
	g_IAfterEffectElementFactory().Register( name, pFactory );
}

//------------------------------------------------------------------
AfterEffectElement* AfterEffect::Create( const sString& name, Render& render )
{
	return g_IAfterEffectElementFactory().Create( name, render );
}

//------------------------------------------------------------------
void AfterEffect::LoadFromFile( const sString& path, const Def& def, const Streams::StreamArchive& archive ) throws_error
{
	ptr_unique<const Streams::IInputStream> pStream( archive.Open( path ) );
	
	ptr_unique<Xml::DomDocument> pDocument( Xml::DomDocument::Read( &pStream() ) );
	
	LoadFromXml( pDocument().GetRoot(), def, archive );		
}
	
//------------------------------------------------------------------
void AfterEffect::LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error
{
	for( sInt i = 0; i < node.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& child = node[i];
		
		if( !XmlCheckDef( child, def ) )
			continue;
		
		if( child.GetName() == ELEMENT_FILTER )
		{
			sString type = child.GetAttributes()[ATTR_TYPE];
			AfterEffectElement* element =  Create( type, *GetOwner() );
			
			if( element == NULL )
				error_throw_arg( Errors::StringError )
					_S("Unknown after effect filter type: ") + type 
				);
			
			try
			{
				element->LoadFromXml( child, def, archive );
				Add( element );
			}
			catch (...) 
			{
				delete element;
				throw;
			}
		}
	}
}	
	
}
