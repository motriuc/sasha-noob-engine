////////////////////////////////////////////////////////////////////////
//	File Name          : rd3_resloader.cpp
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

#include "rd3afx.h"
#include "rd3_resloader.h"
#include "rd3_xml_def.h"
#include "rd3_resobj.h"
#include "rd3_render.h"
#include "rd3_mesh.h"
#include "rd3_texture.h"
#include "rd3_effect.h"
#include "rd3_after_effect.h"
#include "rd3_resloadparams.h"
#include "rd3_font.h"

namespace Rd3 
{

//-----------------------------------------------------------------------
ResourceLoader::ResourceLoader()
{
	
}

//-----------------------------------------------------------------------
ResourceLoader::~ResourceLoader()
{
	for( sInt i = 0; i < _loadedResources.Size(); ++i )
	{
		_loadedResources[i]->UnuseResource();
	}
}

//-----------------------------------------------------------------------
void ResourceLoader::LoadFromFile( const sString& path, ResLoadParams& loadParams ) throws_error
{
	ptr_unique<const Streams::IInputStream> pStream( loadParams.archive.Open( path ) ); 

	ptr_unique<Xml::DomDocument> pDocument( Xml::DomDocument::Read( &pStream() ) );
	LoadFromXML( pDocument().GetRoot(), loadParams );
}

//-----------------------------------------------------------------------
void ResourceLoader::LoadFromXML( const Xml::BaseDomNode& element, ResLoadParams& loadParams )
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
		else if( childElement.GetName() == ELEMENT_AFTER_EFFECT )
			LoadAfterEffect( childElement, loadParams );
		else if( childElement.GetName() == ELEMENT_FONT )
			LoadFont( childElement, loadParams );
			
	}
}	

//-----------------------------------------------------------------------
void ResourceLoader::LoadFont( const Xml::BaseDomNode& element, ResLoadParams& loadParams ) throws_error
{
	sString fName = element.GetAttributes()[ATTR_NAME];
	sString path = element.GetAttributes()[ATTR_PATH];
	
	Font* font = loadParams.render.CreateFontFromFile(
		fName, path,
		loadParams.def,
		loadParams.archive
	);
	_loadedResources.Add( font );	
}
	
//-----------------------------------------------------------------------
void ResourceLoader::LoadAfterEffect( const Xml::BaseDomNode& element, ResLoadParams& loadParams ) throws_error
{
	sString efName = element.GetAttributes()[ATTR_NAME];
	sString path = element.GetAttributes()[ATTR_PATH];
	
	AfterEffect* pAff = loadParams.render.CreateAfterEffectFromFile(
		efName,
		path,
		loadParams.def,
		loadParams.archive
	);
	
	_loadedResources.Add( pAff );	
}
	
//-----------------------------------------------------------------------
void ResourceLoader::LoadVBuffer( const Xml::BaseDomNode& element, ResLoadParams& loadParams ) throws_error
{
	sString vbName = element.GetAttributes()[ATTR_NAME];
	sString path = element.GetAttributes()[ATTR_PATH];
	
	VertexBuffer* pVertexBuffer = loadParams.render.CreateVertexBufferFromFile(
		vbName,
		path,
		loadParams.archive
	);
	
	_loadedResources.Add( pVertexBuffer );	
}		

//-----------------------------------------------------------------------
void ResourceLoader::LoadIBuffer( const Xml::BaseDomNode& element, ResLoadParams& loadParams ) throws_error
{
	sString ibName = element.GetAttributes()[ATTR_NAME];
	sString path = element.GetAttributes()[ATTR_PATH];
		
	IndexBuffer* pVertexBuffer = loadParams.render.CreateIndexBufferFromFile(
		ibName,
		path,
		loadParams.archive
	);

	_loadedResources.Add( pVertexBuffer );	
}		
	
//-----------------------------------------------------------------------
void ResourceLoader::LoadMesh( const Xml::BaseDomNode& element, ResLoadParams& loadParams ) throws_error
{
	sString meshName = element.GetAttributes()[ATTR_NAME];
	sString path = element.GetAttributes()[ATTR_PATH];
	
	Mesh* pMesh = loadParams.render.CreateMeshFromFile( meshName, path, loadParams.def, loadParams.archive );
	
	_loadedResources.Add( pMesh );
}					 
//-----------------------------------------------------------------------
void ResourceLoader::LoadTexture( const Xml::BaseDomNode& element, ResLoadParams& loadParams )
{
	sString textureName = element.GetAttributes()[ATTR_NAME];
	sString path = element.GetAttributes()[ATTR_PATH];
	
	TextureType::TextureType textureType = TextureType::GetType( element.GetAttributes()[ATTR_TYPE] );
	
	if( textureType == Rd3::TextureType::UNKNOWN )
		textureType = Rd3::TextureType::E_IMAGE;
	
	TextureParams param;
	
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
void ResourceLoader::LoadEffect( const Xml::BaseDomNode& element, ResLoadParams& loadParams ) throws_error
{
	sString textureName = element.GetAttributes()[ATTR_NAME];
	sString path = element.GetAttributes()[ATTR_PATH];
	
	Effect* pEffect = loadParams.render.CreateEffectFromFile( textureName, loadParams.def, path, loadParams.archive );
	_loadedResources.Add( pEffect );
}
	
}

