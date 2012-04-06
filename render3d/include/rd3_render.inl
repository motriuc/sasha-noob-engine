/////////////////////////////////////////////////////////////////////
//  File Name               : rd3_render.inl
//  Created                 : 6 04 2012
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

//-------------------------------------------------------------------
inline Service* Render::GetService( const sString& name )
{
	return reinterpret_cast<Service*> ( _serviceResPool[name] );
}
