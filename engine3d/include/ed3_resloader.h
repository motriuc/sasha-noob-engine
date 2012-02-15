////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_resloader.h
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

#ifndef _ED3_RESLOADER_H_
#define _ED3_RESLOADER_H_

#ifndef _ED3_CONF_H_
	#error ed3_conf.h must be included
#endif

#include "ed3_types.h"

namespace Ed3 
{

//////////////////////////////////////////////////////
// d3ResourceLoader schema 
//////////////////////////////////////////////////////
// <>
//		<texture name="..." path="..."/>
//
// </>


/**
 * d3ResourceLoader
 */
class d3ResourceLoader
{
public:
	d3ResourceLoader();
	
	~d3ResourceLoader();
	
	/**
	 *
	 */
	void LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
private:
	sVector<Rd3::ResourceObject*>	_loadedResources;
	
private:
	void LoadTexture( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	void LoadEffect( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	void LoadMesh( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	void LoadVBuffer( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
	void LoadIBuffer( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error;
};

}
#endif // _ED3_RESLOADER_H_
