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
	
	void Add( d3Object* pObj );
	
	virtual ~d3ObjectContiner();
protected:
	virtual void Initialize( Rd3::Render& render ) throws_error;
	virtual void Uninitialize( Rd3::Render& render );
	
	virtual void Render( const d3RenderData& renderData );
	virtual void AI( d3EngineData& edata );
	virtual void ComputeBoundingBox( d3AABBox& b );
	
	virtual sBool LoadFromXMLSubnode( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
  
private:
	sVector<d3Object*>  _objVector;
};

}

#endif // !defined(_ED3_CONT_OBJECT_H_)
