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
	_BaseClass( name ),
	_selectedItem( -1 ),
	_itemSize( 1.0f )
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

	if( _items.Size() > 0 )
	{
		_selectedItem = 0;
		_items[0].SetAnimation( _S("selected") );

		for( sInt i = 1; i < _items.Size(); ++i )
			_items[i].SetAnimation( _S("default") );
	}
}

//------------------------------------------------------------------
void uiList::LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	_texture = loadParams.render.UseTexture( element.GetAttributes()[ATTR_TEXTURE] );
	_itemSize.x = element.GetAttributeValue( _S("item.width"), 1.0f );
	_itemSize.y = element.GetAttributeValue( _S("item.height"), 1.0f );

	_BaseClass::LoadFromXML( element, loadParams );
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
	d3Float height = _itemSize.y;
	d3Float width = _itemSize.x;

	Item& item = _items[_selectedItem];

	RenderTexture( 
		d2Point( -width, -height ),
		d2Point( width, height ),
		_texture,
		item._animationResult.GetTx1(),
		item._animationResult.GetTx2()
	);

	d3Float x1 = width;
	d3Float y1 = -height;
	d3Float x2 = 3.0f * width;
	d3Float y2 = height;

	for( sInt i = _selectedItem + 1; i < _items.Size(); ++i )
	{
		if( x1 > 1.0f )
			break;

		Item& item = _items[i];

		RenderTexture( 
			d2Point( x1, y1 ),
			d2Point( x2, y2 ),
			_texture,
			item._animationResult.GetTx1(),
			item._animationResult.GetTx2()
		);

		x1 += 2.0f * width;
		x2 += 2.0f * width;
	}

	x1 = -3.0f * width;
	y1 = -height;
	x2 = -width;
	y2 = height;

	for( sInt i = _selectedItem - 1; i >= 0; --i )
	{

	}
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
