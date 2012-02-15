/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_xml.h
//	Created                 : 29 6 2007   21:55
//	File path               : SLibF\system\Include
//	Author                  : Alexandru Motriuc
//  Platform Independentsy  : 0%
//	Library                 : 
//
/////////////////////////////////////////////////////////////////////
//	Purpose:
//      
//
/////////////////////////////////////////////////////////////////////
//
//  Modification History:
//      
/////////////////////////////////////////////////////////////////////

/**
 *	Xml
 */
namespace Xml
{
using namespace System;
using namespace System::Types;

/**
 *	NodeType
 */
namespace NodeType
{
/**
 *	Node type
 */
enum NodeType
{
	eDocument  = 0,
	eElement   = 1
};
}

/**
 * Attribute list
 */
class AttributeList
{
public:
	/**
	 * Set the attribute value
	 */
	void SetValue( const sString& name, const sString& value );

	/**
	 * Get attribute value
	 */
	const sString operator[] ( const sString& name ) const;

	/**
	 * get attribute count
	 */
	sInt GetCount() const;

	/**
	 * Return attribute name by id 
	 */
	const sString& GetName( sInt i ) const;
private:
	Cnt::sVector<sString>		_names;
	Cnt::sMap<sString,sString>	_values;
};


/**
 * Base Domnode
 */
class BaseDomNode
{
public:
	/**
	 * Return node name
	 */
	const sString& GetName() const;

	/**
	 * Set Node name
	 */
	void SetName( const sString& name );

	/**
	 * Return node type
	 */
	NodeType::NodeType GetType() const;

	/**
	 * Return Node value
	 */
	const sString& GetValue() const;

	/**
	 * Set Node Value
	 */
	void SetValue( const sString& value );

	/**
	 * Retunrn TRUE if has children
	 */
	sBool HasChildren() const;

	/**
	 * Get child cont
	 */
	sInt GetChildCount() const;

	/**
	 * Get Child
	 */
	const BaseDomNode& GetChild( sInt i ) const;

	/**
	 * Get Child
	 */
	const BaseDomNode& operator [] ( sInt i ) const;

	/**
	 * Get Child
	 */
	BaseDomNode& GetChild( sInt i );

	/**
	 * Get Child
	 */
	BaseDomNode& operator [] ( sInt i );

	/**
	 * Add Child
	 */
	sInt AddChild( BaseDomNode* pChild );

	/**
	 * Remove child
	 */
	BaseDomNode* RemoveChild( sInt i );

	/**
	 * Get Attributes
	 */
	AttributeList& GetAttributes();
	const AttributeList& GetAttributes() const;

	/**
	 * Returnns the node parent
	 */
	BaseDomNode* GetParent();

	/**
	 *	
	 */
	virtual ~BaseDomNode();

protected:
	BaseDomNode( NodeType::NodeType type, const sString& name = _S("") );

	enum domProperty
	{
		E_NAME    = 1,
		E_VALUE   = 2,
		E_CHILD   = 4
	};

	sBool ReadOnlyProperty( domProperty p ) { return sFalse; }
private:
	NodeType::NodeType				_nodeType;
	BaseDomNode*					_pParent;
	Cnt::sVector<BaseDomNode*>		_children;
	AttributeList					_attributes;

	sString							_nodeName;
	sString							_nodeValue;
};


/**
 * Domelement
 */
class DomElement : public BaseDomNode
{
private:
	typedef BaseDomNode _BaseClass;
public:
	DomElement( const sString& name = _S("") );
};

/**
 * Document
 */
class DomDocument : public BaseDomNode
{
private:
	typedef BaseDomNode _BaseClass;
public:
	DomDocument();

	/**
	 * Get document root
	 */
	BaseDomNode& GetRoot();

	/**
	 * Get document root
	 */
	const BaseDomNode& GetRoot() const;

	/**
	 * Set document root
	 */
	void SetRoot( BaseDomNode* pRoot );

	/**
	 *	
	 */
	virtual ~DomDocument();

	/**
	 *	
	 */
	static DomDocument* Read( const Streams::IInputStream* pStream ) throws_error;
	
	/**
	 *
	 */
	static DomDocument* Read( const sString& string ) throws_error;

private:
	BaseDomNode*  _pRoot;
};

/**
 *	XMLParseError
 */
class XMLParseError : public Errors::Error
{
	_SLIB_RUNTIME( System::Xml, XMLParseError, System::Errors::Error )
public:
	XMLParseError( Error* pPrevError = NULL, const sString& msg = _S("") , sInt txtline = -1 );

#ifdef _DEBUG
	XMLParseError( const sChar* file, sInt line, Error* pPrevError = NULL, const sString& msg = _S(""), sInt txtline = -1 );
#endif
	virtual sString Description() const;
private:
	sInt		_line;
	sString		_message;
};

#include "s_system_xml.inl"

}
