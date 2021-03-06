/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_primitive.h
//  Created                 : 5 2 2012   0:05
//  File path               : SLibF\render3d\include\primitives
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

#ifndef _RD3_PRIMITIVE_INC_
#define _RD3_PRIMITIVE_INC_

#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif

namespace Rd3
{

using namespace System;

class Primitive3D;
	
/**
 * IPrimitiveFactory
 */
typedef System::T::IClassFactory<Primitive3D> IPrimitive3DFactory;
	
/**
 * Primitive3D
 */
class Primitive3D
{
protected:
	Primitive3D() {}
public:
	/**
	 *
	 */
	virtual void GetMesh( VertexPList& p, IndexList& i, VertexNList& n, VertexTxCoord& t ) const throws_error = 0;
	
	/**
	 *
	 */
	virtual sInt EstimateVertexCount() const = 0;
	
	/**
	 *
	 */
	virtual sInt EstimateIndexCount() const = 0;

	/**
	 *
	 */
	virtual void LoadFromXml( const Xml::BaseDomNode& node, const Def& def, const Streams::StreamArchive& archive ) throws_error = 0;
    
    virtual ~Primitive3D() {}
	
public:	
	/**
	 *
	 */
	static void Register( const sString& idname, IPrimitive3DFactory* pFactory );
	
	/**
	 *
	 */
	static Primitive3D* Create( const sString& idname );
};

	
}
//////////////////////////////////////////////////////////////////////////
// Primitive factory
//////////////////////////////////////////////////////////////////////////

#define AUTO_REGISTER_PRIMITIVE_FACTORY( _name, _class ) \
	static class Factory_Register_primitive_##_class : public System::T::ClassFactory<_class, Rd3::Primitive3D> \
	{ \
	public: \
		Factory_Register_primitive_##_class( ) \
		{ \
			Rd3::Primitive3D::Register( _name, this ); \
		} \
	} register_primitive_##_class;

#endif // _RD3_PRIMITIVE_INC_