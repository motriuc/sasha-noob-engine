/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_after_effect.h
//  Created                 : 20 2 2012 
//  File path               : SLibF\render3d\include
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

#ifndef _RD3_AFTER_EFEECT_INC_
#define _RD3_AFTER_EFEECT_INC_

/**
 * Check configuration file include
 */
#ifndef _RD3_CONF_H_
	#error rd3_conf.h must be included
#endif


namespace  Rd3
{
	
/**
 * AfterEffect
 */
class AfterEffectElement
{
public:	
	/**
	 *
	 */
	virtual void Apply( RenderState& render ) const = 0;
};

/**
 *
 */
class AfterEffect 
{
public:
	/**
	 *
	 */
	void Add( AfterEffectElement* element ) { _elements.Add( element ); }

	/**
	 *
	 */
	sInt ElementCount() const { return _elements.Size(); }
		
	/**
	 *
	 */
	const AfterEffectElement& GetElement( sInt i ) const { return *_elements[i]; }
private:
	sVector<AfterEffectElement*>	_elements;
};
	
}

#endif // _RD3_AFTER_EFEECT_INC_
