
#ifndef HGEPIXELSHADER_H
#define HGEPIXELSHADER_H

#include "hge.h"

class hgePixelShader
{
public:
	hgePixelShader( const wchar_t* pixFileName, const char* mainFunc, const char* virsion );
	~hgePixelShader();
	bool StartShaderEffect();
	void EndShaderEffect();

	void SetParamentValue( const char* name, float val );
	void SetParamentValue( const char* name, int val  );
	void SetParamentValue( const char* name, bool val );
protected:
	hgePixelShader();
	static HGE	*hge;

	HPIXSHADER hPixShader;
	HCONSTTABLE hConstTable;
};

#endif