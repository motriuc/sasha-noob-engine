/////////////////////////////////////////////////////////////////////
//  File Name           : ed3_obj_factory.h
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

#ifndef _ED3_OBJ_FACTORY_
#define _ED3_OBJ_FACTORY_

#ifndef _ED3_CONF_H_
#error ed3_conf.h must be included
#endif

#define AUTO_REGISTER_D3OBJECT_FACTORY( _name, _class ) \
		static class Factory_Register_##_class \
		{ \
		public: \
			Factory_Register_##_class( ) \
			{ \
				static System::T::ClassFactory<_class, Ed3::d3Object> obj; \
				Ed3::d3ObjectFactory_Register( _name, &obj ); \
			} \
		} register_##_class;
	

namespace  Ed3 
{
	
/**
 *
 */
class d3Object;

/**
 * Id3ObjectFactory
 */
typedef T::IClassFactory<d3Object> Id3ObjectFactory;

/**
 *
 */
void d3ObjectFactory_Register( const sString& idname, Id3ObjectFactory* pFactory );

/**
 *
 */
d3Object* d3ObjectFactory_Create( const sString& idname );

/**
 *
 */
void d3ObjectFactory_Register_BaseClasses();
	
}

#endif // _ED3_OBJ_FACTORY_