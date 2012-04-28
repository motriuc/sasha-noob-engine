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
	_BaseClass( name, sTrue ),
	_selectedItem( -1 ),
	_selectedId( -1 ),
	_tmpSelectedId( -1 ),
	_itemSize( 1.0f ),
	_deltaView( 0.0f )
{
	_gestureDetect.Swipe.Enable();
	_gestureDetect.Swipe.SetBBox( GetRectangle() );
	_gestureDetect.Swipe.onSwipe = Events::Event( this, &uiList::OnSwipe );

	_gestureDetect.Tap.Enable();
	_gestureDetect.Tap.SetBBox( GetRectangle() );
	_gestureDetect.Tap.onTap = Events::Event( this, &uiList::OnTap );
}

//------------------------------------------------------------------
uiList::~uiList()
{
}

//------------------------------------------------------------------
void  uiList::OnSwipe( Rd3::EngineData&, const d3Vector& delta )
{
	_deltaView += delta.x;

	_deltaView = FMath::Clamp(
		_deltaView,
		-_items.Size() * _itemSize.x,
		0.0f
	);
}

//------------------------------------------------------------------
void uiList::OnAnimationEnd( const Rd3::Animation& animation, Rd3::Animation::State& state )
{
	animation.SetAnimationSequence( _S(""), 0, 0, state );
}

//------------------------------------------------------------------
void uiList::UpdatePositions()
{
	d3Float height = _itemSize.y * 0.5f;
	d3Float width = _itemSize.x;

	d3Float x1 = _deltaView + _animationResult.GetMove().x;
	d3Float y1 = -height;
	d3Float x2 = x1 + width;
	d3Float y2 = height;

	for( sInt i = 0; i < _items.Size(); ++i )
	{
		Item& item = _items[i];
		item._rect.SetEmpty();
		item._rect.Add( d2Point( x1, y1 ) );
		item._rect.Add( d2Point( x2, y2 ) );

		x1 += width;
		x2 += width;
	}
}

//------------------------------------------------------------------
void uiList::AnimateSelection()
{
	if( _selectedItem != -1 )
	{
		Item& item = _items[_selectedItem];

		d3Float delta = -_itemSize.x * 0.5f - item._rect.Min().x ;
		_deltaView += delta;
		UpdatePositions();

		_animation().RemoveFrames( 1, 30 );
		_animation().Move( 1, d3Point( -delta, 0.0f, 0.0f ) );
		_animation().Move( 30, d3Point( 0.0f, 0.0f, 0.0f ) );
		_animation().SetAnimationSequence( _S(""), 1, 30, _animationState );
		_animationState.onAnimationEnd = Events::Event( this, &uiList::OnAnimationEnd );
	}
}

//------------------------------------------------------------------
void uiList::UpdateSelectItem( )
{
	if( _selectedId == _tmpSelectedId )
		return;

	for( sInt i = 0; i < _items.Size(); ++i )
	{
		if( _items[i]._id == _tmpSelectedId )
		{
			SelectItemInternal( i );
			AnimateSelection();
			break;
		}
	}
}

//------------------------------------------------------------------
void uiList::SelectItemInternal( sInt id )
{
	if( id != _selectedItem && id >= 0 && id < _items.Size() )
	{
		if( _selectedItem >= 0 )
			_items[_selectedItem].SetAnimation( _S("default") );

		_selectedItem = id;
		_selectedId = _items[_selectedItem]._id;
		_tmpSelectedId = _selectedId;

		_items[_selectedItem].SetAnimation( _S("selected") );
	}
}

//------------------------------------------------------------------
void uiList::OnTap( Rd3::EngineData& edata, const d3Point& point )
{
	for( sInt i = 0; i < _items.Size(); ++i )
	{
		const Item& item = _items[i];

		if( item._rect.Intersect( d2Point( point.x, point.y ) ) )
		{
			SelectItemInternal( i );

			if( GetUIQueue() )
			{
				UiMessage msg( UiMessage::eList, UiMessage::eSelectionChanged, this );
				GetUIQueue()->SendMessage( edata, msg );
			}

			break;
		}
	}
}

//------------------------------------------------------------------
void uiList::OnGestureEvent( Rd3::EngineData& edata, const Rd3::GestureEvent& e )
{
	_gestureDetect.Process( edata, e );
}

//------------------------------------------------------------------
void uiList::Initialize( Rd3::Render& render ) throws_error
{
	_BaseClass::Initialize( render );
	_animation.ResourceCreate( render.CreateAnimation( _S("") ) );
	_animation().Move( 0, d3Point( 0.0f, 0.0f, 0.0f ) );
	_animation().SetAnimationSequence( _S(""), 0, 0, _animationState );

	_deltaView = -_items.Size() * _itemSize.x / 2.0f;
	UpdatePositions();
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
		for( sInt i = 0; i < _items.Size(); ++i )
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
	for( sInt i = 0; i < _items.Size(); ++i )
	{
		Item& item = _items[i];
	
		if( GetRectangle().Contains( item._rect ) )
		{
			RenderTexture( 
				item._rect.Min(),
				item._rect.Max(),
				_texture,
				item._animationResult.GetTx1(),
				item._animationResult.GetTx2()
			);
		}
	}
}

//------------------------------------------------------------------
void uiList::AI( d3EngineData& edata )
{
	UpdateSelectItem();

	for( sInt i = 0; i < _items.Size(); ++i )
	{
		Item& item = _items[i];
		item._animation().Animate( edata.GetTime() ,item._animationState, item._animationResult );
	}

	_animation().Animate( edata.GetTime(), _animationState, _animationResult );

	UpdatePositions();
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
