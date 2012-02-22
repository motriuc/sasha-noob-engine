////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_types.h
//	Created            : 30 1 2012   19:09
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\engine3d\include
//  System independent : 0%
//  Library            : 
//
//	Purpose:	
//    
//
/////////////////////////////////////////////////////////////////////////
//  Modification History :
// 
/////////////////////////////////////////////////////////////////////////

#ifndef _ED3_TYPES_H_
#define _ED3_TYPES_H_

#ifndef _ED3_CONF_H_
	#error ed3_conf.h must be included
#endif

namespace Ed3 
{

class d3ObjectClassNames;
class d3PhysicsWorld;
	
/**
 * LoadParams
 */
class LoadDataParams
{
public:
	/**
	 *
	 */
	LoadDataParams( 
			   const Rd3::Def& idef,
			   const System::Streams::StreamArchive& iarchive,
			   Rd3::Render& irender
			   ) :
		def( idef ),
		archive( iarchive ),
		render( irender ),
		pClassNames( NULL ),
		pPhysicsWorld( NULL )
	{
	}
			   
	const Rd3::Def& def;
	const System::Streams::StreamArchive& archive;
	Rd3::Render& render;
	d3ObjectClassNames* pClassNames;
	d3PhysicsWorld*	pPhysicsWorld;
};
	
}
#endif // _ED3_TYPES_H_