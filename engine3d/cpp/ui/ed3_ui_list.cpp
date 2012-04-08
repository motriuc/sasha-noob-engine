/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_ui_list.cpp
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

#include "ed3afx.h"
#include "ed3_ui_list.h"
#include "ed3_edata.h"

#include "rd3_render.h"

namespace Ed3
{

//------------------------------------------------------------------
uiList::uiList( const sString& name ) :
	_BaseClass( name )
{
}

//------------------------------------------------------------------
uiList::~uiList()
{
}

//------------------------------------------------------------------
void uiList::LoadFromXML_Items( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	for( sInt i = 0; i < element.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& childElement = element[i];

		if( !Rd3::XmlCheckDef( childElement, loadParams.def ) )
			continue;
		
		if( childElement.GetName() == ELEMENT_ITEM )
		{
			Item item;
			item.LoadFromXml( childElement, loadParams );

			_items.Add( item );
		}
	}
}

//------------------------------------------------------------------
sBool uiList::LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	if( _BaseClass::LoadFromXMLSubnode( element, loadParams ) )
		return sTrue;

	if( element.GetName() == _S("itemlist") )
	{
		LoadFromXML_Items( element, loadParams );
		return sTrue;
	}

	return sFalse;
}

//------------------------------------------------------------------
void uiList::Render2D( const d3RenderData& renderData )
{
}

//------------------------------------------------------------------
void uiList::AI( d3EngineData& edata )
{
	for( sInt i = 0; i < _items.Size(); ++i )
	{
		Item& item = _items[i];
		item._animation().Animate( edata.GetTime() ,item._animationState, item._animationResult );
	}
}

//------------------------------------------------------------------
// Item
//------------------------------------------------------------------
void uiList::Item::LoadFromXml( const Xml::BaseDomNode& element, LoadDataParams& loadParams )
{
	_id = element.GetAttributeValue( ATTR_ID, 0 );
	_animation = loadParams.render.UseAnimation( element.GetAttributes()[ATTR_ANIMATION] );
}

}
