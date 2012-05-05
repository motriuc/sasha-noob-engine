/////////////////////////////////////////////////////////////////////
//  File Name               : s_system_xml.inl
//  Created                 : 29 6 2007   22:26
//  File path               : SLibF\system\Include
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

inline BaseDomNode::BaseDomNode( NodeType::NodeType type, const sString& name ) :
	_nodeType( type ),
	_nodeName( name ),
	_pParent( NULL )
{
}


inline const sString& BaseDomNode::GetName() const
{
	return _nodeName;
}

inline void BaseDomNode::SetName( const sString& name )
{
	if( !ReadOnlyProperty( E_NAME ) )
		_nodeName = name;
}

inline NodeType::NodeType BaseDomNode::GetType() const
{
	return _nodeType;
}

inline const sString& BaseDomNode::GetValue() const
{
	return _nodeValue;
}

inline void BaseDomNode::SetValue( const sString& value )
{
	if( !ReadOnlyProperty( E_VALUE ) )
		_nodeValue = value;
}

inline sBool BaseDomNode::HasChildren() const
{
	return _children.Size() > 0;
}

inline sInt BaseDomNode::GetChildCount() const
{
	return _children.Size();
}

inline const BaseDomNode& BaseDomNode::GetChild( sInt i ) const
{
	return *_children[i];
}

inline BaseDomNode& BaseDomNode::GetChild( sInt i )
{
	return *_children[i];
}

inline const BaseDomNode& BaseDomNode::operator [] ( sInt i ) const
{
	return *_children[i];
}

inline BaseDomNode& BaseDomNode::operator [] ( sInt i )
{
	return *_children[i];
}

inline sInt BaseDomNode::AddChild( BaseDomNode* pChild )
{
	__S_ASSERT( pChild != NULL );

	if( ReadOnlyProperty( E_CHILD ) || pChild->_pParent != NULL ) 
		return -1;

	pChild->_pParent = this;

	return _children.Add( pChild );
}

inline BaseDomNode* BaseDomNode::RemoveChild( sInt i )
{
	if( ReadOnlyProperty( E_CHILD ) ) 
		return NULL;

	return _children.RemoveAt( i );
}

inline BaseDomNode* BaseDomNode::GetParent()
{
	return _pParent;
}

inline AttributeList& BaseDomNode::GetAttributes()
{
	return _attributes;
}

inline const AttributeList& BaseDomNode::GetAttributes() const
{
	return _attributes;
}

inline sFloat BaseDomNode::GetAttributeValue( const sString& name, sFloat defValue ) const
{
	sString v = _attributes[name];
	if( v.Length() > 0 )
		return v.ToFloat();
		
	return defValue;
} 

inline sInt BaseDomNode::GetAttributeValue( const sString& name, sInt defValue ) const
{
	sString v = _attributes[name];
	if( v.Length() > 0 )
		return v.ToInt();
		
	return defValue;	
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

inline DomElement::DomElement( const sString& name ) :
	BaseDomNode( NodeType::eElement, name )
{
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
inline BaseDomNode& DomDocument::GetRoot()
{
	return *_pRoot;
}

inline const BaseDomNode& DomDocument::GetRoot() const
{
	return *_pRoot;
}

inline void DomDocument::SetRoot( BaseDomNode* pRoot )
{
	if( _pRoot )
		delete _pRoot;

	_pRoot = pRoot;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

inline void AttributeList::SetValue( const sString& name, const sString& value )
{
	if( value.Length() == 0 )
	{
		if( _values.Remove( name ) )
		{
			for( sInt i = 0; i < _names.Size(); i++ )
			{
				if( _names[i] == name )
				{
					_names.RemoveAt( i );
					break;
				}
			}
		}
	}
	else if( _values.Add( name, value ) )
		_names.Add( name );
}


inline const sString AttributeList::operator[] ( const sString& name ) const
{
	sString val;
	_values.Lookup( name, val );
	return val;
}

inline sInt AttributeList::GetCount() const
{
	return _names.Size();
}

inline const sString& AttributeList::GetName( sInt i ) const
{
	return _names[i];
}
