#include "../../include/hgepixelshader.h"

HGE * hgePixelShader::hge = NULL;

hgePixelShader::hgePixelShader( const wchar_t *pixFileName, const char *mainFunc, const char *virsion )
{
	hPixShader = 0;
	hConstTable = 0;
	hge = hgeCreate(HGE_VERSION);

	hge->Shader_CreatePixelShader( pixFileName, mainFunc, virsion, &hPixShader, &hConstTable );
}

hgePixelShader::~hgePixelShader()
{
	hge->Shader_FreePixelShader( hPixShader );
	hge->Shader_FreeConstTable( hConstTable );
	hge->Release();
}

bool hgePixelShader::StartShaderEffect()
{
	if ( hPixShader == 0 )
	{
		return false;
	}

	return hge->Shader_SetPixelShader( hPixShader );
}

void hgePixelShader::EndShaderEffect()
{
	hge->Shader_SetPixelShader( 0 );
}

void hgePixelShader::SetParamentValue( const char* name, float val )
{
	hge->Shader_SetParaValue( hConstTable, name, val );
}

void hgePixelShader::SetParamentValue( const char* name, int val  )
{
	hge->Shader_SetParaValue( hConstTable, name, val );
}

void hgePixelShader::SetParamentValue( const char* name, bool val )
{
	hge->Shader_SetParaValue( hConstTable, name, val );
}