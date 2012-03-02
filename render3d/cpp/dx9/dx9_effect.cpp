/////////////////////////////////////////////////////////////////////
//  File Name               : dx9_effect.cpp
//  Created                 : 23 1 2011   22:43
//  File path               : SLibF\render3d\dx9\cpp
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

#include "rd3afx.h"

#include "dx9/dx9_conf.h"
#include "dx9/dx9_effect.h"
#include "dx9/dx9_texture.h"
#include "dx9/dx9_render.h"

using namespace Rd3;
using namespace System::Cnt;

/////////////////////////////////////////////////////////////////////////////////////////////
// Utils
/////////////////////////////////////////////////////////////////////////////////////////////

typedef sVector<char> CharV;
typedef sVector<CharV> CharVVector;

//------------------------------------------------------------------------------------------
void ToCharV( CharV& v, const sString& s )
{
	sInt count = s.Length();
	v.SetSize( count + 1 );

#ifdef _SLIB_WCHAR
	count = Chars::Convert( v.GetBuffer(), count, s.c_str(), count );  
#else
	Memory::Copy( v.GetBuffer(), s.c_str(), count );
#endif
	v[count] = 0;
}

//------------------------------------------------------------------------------------------
void GetFxMacrosFromDef( CharVVector& values, sVector<D3DXMACRO>& macro, const Rd3::Def& def )
{
	sStrings defStrings;

	def.GetAllDefined( defStrings );

	sInt count = defStrings.Size();

	macro.SetSize( count + 1 );
	values.SetSize( 2*count );

	for( sInt i = 0; i < defStrings.Size(); i++ )
	{
		ToCharV( values[2*i], defStrings[i] );
		ToCharV( values[2*i + 1], def[defStrings[i]] );

		D3DXMACRO&m = macro[i];

		m.Name = values[2*i].GetBuffer();
		m.Definition = values[2*i+1].GetBuffer();
	}

	D3DXMACRO&m = macro[count];
	m.Name = NULL;
	m.Definition = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Dx9Effect::Dx9Effect
/////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------
Dx9Effect::Dx9Effect(
		Rd3::Render* owner,  
		const sString& objectName
		) :
	_BaseClass(owner, objectName),
	_pEffect( NULL )
{
}

//-------------------------------------------------------------------------------------------
void Dx9Effect::LoadFromFile( const sString& filePath, const Rd3::Def& def, const Streams::StreamArchive& archive ) throws_error
{
	ptr_unique<const Streams::IInputStream> pStream( archive.Open( filePath ) ); 
	
	sUInt length = pStream().GetSize();
	
	ptr_array_unique<char> charBuffer ( new char[length] );
	pStream().Read( charBuffer, length );
	
	LoadFromString( sString( charBuffer, length ), def );
}

//-------------------------------------------------------------------------------------------
void Dx9Effect::LoadFromChars( const SBCHAR* effect, sInt size, const Rd3::Def& def ) throws_error
{
	__S_ASSERT( _pEffect == NULL );

	CharVVector values;
	sVector<D3DXMACRO> macro;

	// convert data to char*
	GetFxMacrosFromDef( values, macro, def );

	SDWORD dwFlags = 0;
#ifdef _DEBUG
	dwFlags |= D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION; 
#else
#endif

	LPD3DXBUFFER pBuffer;

	HRESULT hr = D3DXCreateEffect( 
		Dx9Render::GetDX9Device( GetOwner() ), 
		effect,
		size,
		macro.GetBuffer(),
		NULL,
		dwFlags,
		NULL,
		&_pEffect,
		&pBuffer
	);

	if( FAILED( hr ) )
	{
		if( pBuffer )
		{
			sString error( (const char*)pBuffer->GetBufferPointer(), pBuffer->GetBufferSize() );
			pBuffer->Release();
			error_throw_arg( System::Errors::StringError ) 
				error
			);
		}
		else
			_DX9_ERROR( hr );
	}

	InitParamsLinks();
}

//-------------------------------------------------------------------------------------------
void Dx9Effect::LoadFromString( const sString& effect, const Rd3::Def& def ) throws_error
{
	// convert data to char*
	CharV effectCharV;
	ToCharV( effectCharV, effect );
	LoadFromChars( effectCharV.GetBuffer(), effectCharV.Size(), def ); 
}

//-------------------------------------------------------------------------------------------
void Dx9Effect::InitParamsLinks() throws_error
{
	__S_ASSERT( _pEffect != NULL );

	D3DXEFFECT_DESC     effectDesc;
	D3DXPARAMETER_DESC  paramDesc;

	HRESULT hr = _pEffect->GetDesc( &effectDesc );

	if( FAILED(hr) )
		_DX9_ERROR( hr );

	sString unknownParams;

	for( sInt i = 0; i < (sInt)effectDesc.Parameters; i++ )
	{
		D3DXHANDLE hParam = _pEffect->GetParameter ( NULL, i );
		hr = _pEffect->GetParameterDesc( hParam, &paramDesc );
		
		if( FAILED(hr) )
			_DX9_ERROR( hr );

		if( paramDesc.Name == NULL )
			continue;

		/**
		 * texture params
		 */
		sString paramName( paramDesc.Name );

		if( paramDesc.Class == D3DXPC_OBJECT && 
			( 
				paramDesc.Type == D3DXPT_TEXTURE ||
				paramDesc.Type == D3DXPT_TEXTURE1D ||
				paramDesc.Type == D3DXPT_TEXTURE2D ||
				paramDesc.Type == D3DXPT_TEXTURE3D
			)
		)
		{
			TextureParameter::TextureParameter p = TextureParameter::GetType( paramName );
			if( p != TextureParameter::UNKNOWN )
			{
				SetIndex( p, (sUInt)hParam );
			}
			else
				unknownParams += paramName + _S(";");
		}

		if(  paramDesc.Class == D3DXPC_MATRIX_ROWS || paramDesc.Class == D3DXPC_MATRIX_COLUMNS )
		{
			MatrixParameter::MatrixParameter p = MatrixParameter::GetType( paramName );
			
			if( p != MatrixParameter::UNKNOWN )
			{
				SetIndex( p, (sUInt)hParam );
			}
			else
				unknownParams += paramName + _S(";");
		}
    
		if( paramDesc.Class == D3DXPC_VECTOR )
		{
			VectorParameter::VectorParameter p = VectorParameter::GetType( paramName );
			if( p != VectorParameter::UNKNOWN )
			{
				SetIndex( p, (sUInt)hParam );
			}
			else
				unknownParams += paramName + _S(";");
		}

		if( paramDesc.Class == D3DXPC_SCALAR )
		{
			if( paramDesc.Type == D3DXPT_FLOAT )
			{
				FloatParameter::FloatParameter p = FloatParameter::GetType( paramName );
				if( p != FloatParameter::UNKNOWN )
				{
					SetIndex( p, (sUInt)hParam );
				}
				else
					_floatDynamicParams.Add( paramName, (sUInt)hParam );

			}
			else if( paramDesc.Type == D3DXPT_BOOL )
			{
				BoolParameter::BoolParameter p = BoolParameter::GetType( paramName );
				if( p != BoolParameter::UNKNOWN )
				{
					SetIndex( p, (sUInt)hParam );
				}
				else
					unknownParams += paramName + _S(";");
			}
		}
	}

	if( unknownParams.Length() > 0 )
	{
		System::Platform::ShowWarning( _S("Warning the folowing paramas <") + unknownParams + 
			_S("> from fx: ") + GetObjectName() + _S(" are not supported by engine") ); 
	}
}

//-------------------------------------------------------------------------------------------
Dx9Effect::~Dx9Effect()
{
	if( _pEffect != NULL )
		_pEffect->Release();
}

//-------------------------------------------------------------------------------------------
void Dx9Effect::Set( sUInt h, const d3Matrix& m ) const
{
	__S_ASSERT( _pEffect != NULL );
	HRESULT hr = _pEffect->SetMatrix( (D3DXHANDLE)h, (const D3DXMATRIX*)&m );
	__S_ASSERT( SUCCEEDED(hr) );
}

//-------------------------------------------------------------------------------------------
void Dx9Effect::Set( sUInt h, const d3Vector& v ) const
{
	__S_ASSERT( _pEffect != NULL );
	HRESULT hr = _pEffect->SetVector( (D3DXHANDLE)h, (const D3DXVECTOR4*)&v ); 
	__S_ASSERT( SUCCEEDED(hr) );
}

//-------------------------------------------------------------------------------------------
void Dx9Effect::Set( sUInt h, const d3Float f ) const
{
	__S_ASSERT( _pEffect != NULL );
	HRESULT hr = _pEffect->SetFloat( (D3DXHANDLE)h, f );
	__S_ASSERT( SUCCEEDED(hr) );
}

//-------------------------------------------------------------------------------------------
void Dx9Effect::Set( sUInt h, const sBool b ) const
{
	__S_ASSERT( _pEffect != NULL );
	HRESULT hr = _pEffect->SetBool( (D3DXHANDLE)h, b );
	__S_ASSERT( SUCCEEDED(hr) );
}

//-------------------------------------------------------------------------------------------
void Dx9Effect::Set( sUInt i, sUInt h, const Texture* t ) const
{
	__S_ASSERT( _pEffect != NULL );

	if( t == NULL )
		return;

	HRESULT hr = _pEffect->SetTexture( (D3DXHANDLE)h, ((Dx9Texture*)t)->GetHandle() );
	__S_ASSERT( SUCCEEDED(hr) );
}
