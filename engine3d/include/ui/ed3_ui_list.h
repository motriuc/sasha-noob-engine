/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_ui_list.h
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

#ifndef _ED3_UI_LIST_INC_
#define _ED3_UI_LIST_INC_

#include "rd3_animation.h"
#include "ed3_object_d2.h"
#include "rd3_msg_gesture_detect.h"

namespace Ed3
{

/**
 * uiList
 */
class uiList : public d2Object
{
	_SLIB_RUNTIME( Ed3, uiList, d2Object )
public:
	uiList( const sString& name = _S("") );

	/**
	 *
	 */
	~uiList();

	/**
	 *
	 */
	void SelectItem( sInt id )									{ _tmpSelectedId = id; }

	/**
	 *
	 */
	sInt GetSelectedItem() const								{ return _selectedId; }
protected:
	virtual void LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	virtual sBool LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	virtual void LoadFromXML_Items( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;

	virtual void Initialize( Rd3::Render& render ) throws_error;
	virtual void AI( d3EngineData& edata );

	virtual void Render2D( const d3RenderData& renderData );

	virtual void OnGestureEvent( Rd3::EngineData& edata, const Rd3::GestureEvent& e );
	void OnSwipe( Rd3::EngineData&, const d3Vector& delta );
	void OnTap( Rd3::EngineData&, const d3Point& delta );
	
	void UpdatePositions();
private:
	/**
	 * Item
	 */
	class Item
	{
	public:
		Item() :
		  _id( -1 )
		{
			_rect.SetEmpty();
		}

		void LoadFromXml( const Xml::BaseDomNode& element, LoadDataParams& loadParams );
	protected:
		void SetAnimation( const sString& name )
		{
			_animation().SetAnimationSequence( name, _animationState );
		}
	private:
		d2Rectangle							_rect;
		sInt								_id;
		sString								_name;
		Rd3::use_resource<Rd3::Animation>	_animation;
		Rd3::Animation::State				_animationState;
		Rd3::Animation::Result				_animationResult;

		friend class uiList;
	};

	/**
	 * Select item
	 */
	void SelectItemInternal( sInt id );
	void UpdateSelectItem();

	void AnimateSelection();
	void OnAnimationEnd( const Rd3::Animation& animation, Rd3::Animation::State& state );
private:
	sVector<Item>					_items;
	sInt							_selectedItem;
	sInt							_selectedId;
	sInt							_tmpSelectedId;
	d2Vector						_itemSize;
	d3Float							_deltaView;

	Rd3::use_resource<Rd3::Texture>		_texture;
	
	Rd3::use_resource<Rd3::Animation>	_animation;
	Rd3::Animation::State				_animationState;
	Rd3::Animation::Result				_animationResult;

	Rd3::GestureDetect				_gestureDetect;
};

}

#endif // _ED3_UI_LIST_INC_

