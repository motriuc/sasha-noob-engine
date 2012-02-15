////////////////////////////////////////////////////////////////////////
//	File Name          : ed3_resloader.cpp
//	Created            : 30 1 2012   19:09
//  Author             : Alexandru Motriuc  
//	File Path          : SLibF\engine3d\cpp
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

#include "ed3afx.h"
#include "ed3_resloader.h"
#include "rd3_xml_def.h"
#include "rd3_resobj.h"
#include "rd3_render.h"
#include "rd3_mesh.h"
#include "rd3_texture.h"
#include "rd3_effect.h"

namespace Ed3 
{

//-----------------------------------------------------------------------
d3ResourceLoader::d3ResourceLoader()
{
	
}

//-----------------------------------------------------------------------
d3ResourceLoader::~d3ResourceLoader()
{
	for( sInt i = 0; i < _loadedResources.Size(); ++i )
	{
		_loadedResources[i]->UnuseResource();
	}
}

//-----------------------------------------------------------------------
void d3ResourceLoader::LoadFromXML( const Xml::BaseDomNode& element, LoadDataParams& loadParams )
{
	for( sInt i = 0; i < element.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& childElement = element[i];
		
		if( !Rd3::XmlCheckDef( childElement, loadParams.def ) )
			continue;
		
		if ( childElement.GetName() == ELEMENT_TEXTURE )
			LoadTexture( childElement, loadParams );
		else if ( childElement.GetName() == ELEMENT_EFFECT )
			LoadEffect( childElement, loadParams );
		else if( childElement.GetName() == ELEMENT_MESH )
			LoadMesh( childElement, loadParams );
		else if( childElement.GetName() == ELEMENT_VBUFFER )
			LoadVBuffer( childElement, loadParams );
		else if( childElement.GetName() == ELEMENT_IBUFFER )
			LoadIBuffer( childElement, loadParams );
	}
}	

//-----------------------------------------------------------------------
void d3ResourceLoader::LoadVBuffer( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	sString vbName = element.GetAttributes()[ATTR_NAME];
	sString path = element.GetAttributes()[ATTR_PATH];
	
	Rd3::VertexBuffer* pVertexBuffer = loadParams.render.CreateVertexBufferFromFile(
		vbName,
		path,
		loadParams.archive
	);
	
	_loadedResources.Add( pVertexBuffer );	
}		

//-----------------------------------------------------------------------
void d3ResourceLoader::LoadIBuffer( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	sString ibName = element.GetAttributes()[ATTR_NAME];
	sString path = element.GetAttributes()[ATTR_PATH];
		
	Rd3::IndexBuffer* pVertexBuffer = loadParams.render.CreateIndexBufferFromFile(
		ibName,
		path,
		loadParams.archive
	);

	_loadedResources.Add( pVertexBuffer );	
}		
	
//-----------------------------------------------------------------------
void d3ResourceLoader::LoadMesh( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	sString meshName = element.GetAttributes()[ATTR_NAME];
	sString path = element.GetAttributes()[ATTR_PATH];
	
	Rd3::Mesh* pMesh = loadParams.render.CreateMeshFromFile( meshName, path, loadParams.def, loadParams.archive );
	
	_loadedResources.Add( pMesh );
}					 
//-----------------------------------------------------------------------
void d3ResourceLoader::LoadTexture( const Xml::BaseDomNode& element, LoadDataParams& loadParams )
{
	sString textureName = element.GetAttributes()[ATTR_NAME];
	sString path = element.GetAttributes()[ATTR_PATH];
	
	Rd3::TextureType::TextureType textureType = Rd3::TextureType::GetType( element.GetAttributes()[ATTR_TYPE] );
	
	if( textureType == Rd3::TextureType::UNKNOWN )
		textureType = Rd3::TextureType::E_IMAGE;
	
	Rd3::TextureParams param;
	
	for( sInt i = 0; i < element.GetChildCount(); ++i )
	{
		const Xml::BaseDomNode& childElement = element[i];
		
		if( !Rd3::XmlCheckDef( childElement, loadParams.def ) )
			continue;
		
		if( childElement.GetName() == ELEMENT_TEXTURE_PARAMS )
			Rd3::XmlLoad_TextureParams( param, childElement, loadParams.def );
		
	}
	
	Rd3::Texture* pTexture = loadParams.render.CreateTextureFromFile( textureName, path, loadParams.archive, textureType, param );
	_loadedResources.Add( pTexture ); 
}

//-----------------------------------------------------------------------
void d3ResourceLoader::LoadEffect( const Xml::BaseDomNode& element, LoadDataParams& loadParams ) throws_error
{
	sString textureName = element.GetAttributes()[ATTR_NAME];
	sString path = element.GetAttributes()[ATTR_PATH];
	
	Rd3::Effect* pEffect = loadParams.render.CreateEffectFromFile( textureName, loadParams.def, path, loadParams.archive );
	_loadedResources.Add( pEffect );
}
	
}

