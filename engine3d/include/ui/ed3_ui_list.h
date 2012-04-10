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


namespace Ed3
{

/**
 * uiList
 */
class uiList : public d2Object
{
private:
	typedef d2Object _BaseClass;
public:
	uiList( const sString& name = _S("") );

	/**
	 *
	 */
	~uiList();

	/**
	 * Item
	 */
	class Item
	{
	public:
		Item() :
		  _id( -1 )
		{
		}

		void LoadFromXml( const Xml::BaseDomNode& element, LoadDataParams& loadParams );
	protected:
		void SetAnimation( const sString& name )
		{
			_animation().SetAnimationSequence( name, _animationState );
		}
	private:
		sInt								_id;
		sString								_name;
		Rd3::use_resource<Rd3::Animation>	_animation;
		Rd3::Animation::State				_animationState;
		Rd3::Animation::Result				_animationResult;

		friend class uiList;
	};

protected:
	virtual void LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	virtual sBool LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	virtual void LoadFromXML_Items( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;

	virtual void AI( d3EngineData& edata );

	virtual void Render2D( const d3RenderData& renderData );

private:
	sVector<Item>	_items;
	sInt			_selectedItem;
	d2Vector		_itemSize;

	Rd3::use_resource<Rd3::Texture>	_texture;
};

}

#endif // _ED3_UI_LIST_INC_

