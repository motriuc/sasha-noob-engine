/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_cont_object.h
//  Created             : 19 1 2012
//  Author              : Motriuc Alexandru
//  File Path           : SLibF\engine3d\include
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
#if !defined(_ED3_CONT_OBJECT_H_)
#define _ED3_CONT_OBJECT_H_


#include "ed3_object.h"

namespace Ed3 
{

class d3RenderData;
class d3EngineData;

//////////////////////////////////////////////////////
// d3ObjectContiner schema
//////////////////////////////////////////////////////
// <object> : d3Object
//	<children>
//		...
//	</children>
// </object>

/**
 * Objects continer
 */
class d3ObjectContiner : public d3Object
{
private:
	typedef d3Object _BaseClass;
public:
	d3ObjectContiner( ObjectType::ObjectType type = ObjectType::E_CONTINER );
	
	/**
	 * Add object
	 */
	void Add( d3Object* pObj );

	/**
	 *
	 */
	d3Object* FindByName( const sString& name );

	template< typename _Type >
	_Type* FindByName( const sString& name )
	{
		d3Object* pObject = FindByName( name );
		if( pObject == NULL )
			return NULL;

		if( !pObject->Is( TYPE( _Type ) ) )
			return NULL;

		return static_cast<_Type*>( pObject );
	}

	virtual ~d3ObjectContiner();
protected:
	virtual void Initialize( Rd3::Render& render ) throws_error;
	virtual void Uninitialize( Rd3::Render& render );
	
	virtual void Render( const d3RenderData& renderData );
	virtual void AI( d3EngineData& edata );
	virtual void ComputeBoundingBox( d3AABBox& b );
	
	virtual sBool LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
  
private:
	sVector<d3Object*>			_objVector;
	sMap<sString,d3Object*>		_objMap;
};

//-------------------------------------------------------------------
inline d3Object* d3ObjectContiner::FindByName( const sString& name )
{
	d3Object* obj = NULL;
	_objMap.Lookup( name, obj );
	return obj;
}

}

#endif // !defined(_ED3_CONT_OBJECT_H_)
