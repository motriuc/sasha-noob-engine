/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_xml.cpp
//  Created                 : 29 6 2007   21:59
//  File path               : C:\Sasha\C++\SLibF\base\Cpp
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

#define _use_Xml_
#define _use_Streams_

#include "s_system.h"
#include "expat.h"

namespace System
{

namespace Xml
{
using namespace System;
using namespace System::Types;

/************************************************************************/
/*                                                                      */
/************************************************************************/
XMLParseError::XMLParseError( Error* pPrevError, const sString& msg, sInt txtline ) :
	_BaseClass( pPrevError ),
	_message( msg ),
	_line( txtline )
{
}

#ifdef _DEBUG

//-----------------------------------------------------------------------
XMLParseError::XMLParseError( const sChar* file, sInt line, Error* pPrevError, const sString& msg, sInt txtline ) :
	_BaseClass( file, line, pPrevError ),
	_message( msg ),
	_line( txtline )
{
}

#endif // _DEBUG

//-----------------------------------------------------------------------
sString XMLParseError::Description() const
{
	if( _line < 0 )
		return Format( _S("{1}\n{2}") ) % _message % _BaseClass::Description();

	return Format( _S("Parse error line ({1}) {2}\n{3}") ) % _line % _message % _BaseClass::Description();		
}

/************************************************************************/
/* BaseDomNode                                                          */
/************************************************************************/

BaseDomNode::~BaseDomNode()
{
	for( sInt i = 0; i < _children.Size(); i++ )
		delete _children[i];
}

/************************************************************************/
/* XML parsing                                                          */
/************************************************************************/

typedef struct
{
	DomDocument*    _pDocument;
	BaseDomNode*    _pNode;
} _READ_STRUCT;

//-----------------------------------------------------------------------
static void XMLCALL startElement( void* userData, const XML_Char *name, const XML_Char **atts )
{
	_READ_STRUCT& readStruct = *(_READ_STRUCT*) userData;

	DomElement* pDomElement = new DomElement( name );

	if( readStruct._pDocument == NULL )
	{
		readStruct._pDocument = new DomDocument;
		readStruct._pDocument->SetRoot( pDomElement );
	}
	else
	{
		__S_ASSERT( readStruct._pNode != NULL );
		readStruct._pNode->AddChild( pDomElement );
	}

	AttributeList& attrList = pDomElement->GetAttributes();

	for ( sInt i = 0; atts[i]; i += 2 )
		attrList.SetValue( atts[i], atts[i + 1] );

	readStruct._pNode = pDomElement;
}

//-----------------------------------------------------------------------
static void XMLCALL endElement( void *userData, const XML_Char *name )
{
	_READ_STRUCT& readStruct = *(_READ_STRUCT*) userData;

	__S_ASSERT( readStruct._pNode != NULL );

	readStruct._pNode = readStruct._pNode->GetParent();
}
	
//-----------------------------------------------------------------------
static void dataElement( void *userData, const XML_Char *s, int len )
{
  
}

/************************************************************************/
/* DomDocument                                                          */
/************************************************************************/

DomDocument::DomDocument() :
	_BaseClass( NodeType::eDocument,   _S("document") ),
	_pRoot( NULL )
{
}

//-----------------------------------------------------------------------
DomDocument* DomDocument::Read( const sString& string ) throws_error
{
	_READ_STRUCT readStruct = { NULL, NULL };
	
	XML_Parser parser = XML_ParserCreate( NULL );
	
	if( parser == NULL )
	{
		error_throw_arg( XMLParseError )
		_S("Can't initialize XML parser")
		);
	}
	
	XML_SetUserData( parser, &readStruct );		
	XML_SetElementHandler( parser, startElement, endElement );
	XML_SetCharacterDataHandler( parser, dataElement );
	
	try
	{
		if( XML_Parse( parser, (const char*)string.c_str(), string.Length() * sizeof(sChar), true ) == XML_STATUS_ERROR )
		{
			error_throw_arg( XMLParseError )
				sString( XML_ErrorString( XML_GetErrorCode( parser ) ) ),
				XML_GetCurrentLineNumber( parser )
			);
		}
		
		XML_ParserFree( parser );
	}
	catch(...)
	{
		XML_ParserFree( parser );
		delete readStruct._pDocument;
		throw;
	}
	
	return readStruct._pDocument;	
}

//-----------------------------------------------------------------------	
DomDocument* DomDocument::Read( const Streams::IInputStream* pStream )
{
	__S_ASSERT( pStream != NULL );

	_READ_STRUCT readStruct = { NULL, NULL };

	XML_Parser parser = XML_ParserCreate( NULL );

	if( parser == NULL )
	{
		error_throw_arg( XMLParseError )
			_S("Can't initialize XML parser")
		);
	}

	XML_SetUserData( parser, &readStruct );

	const sInt readBufferSize = 1024;
	XML_Char readBuffer[readBufferSize];

	XML_SetElementHandler( parser, startElement, endElement );
	XML_SetCharacterDataHandler( parser, dataElement );

	try
	{
		sInt readSize = readBufferSize;
		
		for(;;)
		{
			readSize = pStream->Read( readBuffer, readBufferSize );
			
			if( XML_Parse( parser, readBuffer, readSize, readSize < readBufferSize ) == XML_STATUS_ERROR )
			{
				error_throw_arg( XMLParseError )
					sString( XML_ErrorString( XML_GetErrorCode( parser ) ) ),
					XML_GetCurrentLineNumber( parser )
				);
			}
			if( readSize < readBufferSize )
				break;
		}

		XML_ParserFree( parser );
	}
	catch(...)
	{
		XML_ParserFree( parser );
		delete readStruct._pDocument;
		throw;
	}

	return readStruct._pDocument;
}

//-----------------------------------------------------------------------	
DomDocument::~DomDocument()
{
	delete _pRoot;
}


}
}