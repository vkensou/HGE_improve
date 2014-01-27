/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hgeFont helper class header
*/


#ifndef HGEFONT_H
#define HGEFONT_H


#include "hge.h"
#include "hgesprite.h"



enum {
	PAD_TOP = 0,
	PAD_RIGHT,
	PAD_BOTTOM,
	PAD_LEFT
};

/*
** HGE Font class
*/
class hgeFont
{
public:
	hgeFont(const wchar_t *filename, bool bMipmap=false);
	~hgeFont();

	void		Render(float x, float y, int align, const wchar_t *string);
	void		printf(float x, float y, int align, const wchar_t *format, ...);
	void		printfb(float x, float y, float w, float h, int align, const wchar_t *format, ...);

	void		SetColor(DWORD col);
	void		SetZ(float z);
	void		SetBlendMode(int blend);
	void		SetScale(float scale) {fScale=scale;}
	void		SetProportion(float prop) { fProportion=prop; }
	void		SetRotation(float rot) {fRot=rot;}
	void		SetTracking(float tracking) {fTracking=tracking;}
	void		SetSpacing(float spacing) {fSpacing=spacing;}

	DWORD		GetColor() const {return dwCol;}
	float		GetZ() const {return fZ;}
	int			GetBlendMode() const {return nBlend;}
	float		GetScale() const {return fScale;}
	float		GetProportion() const { return fProportion; }
	float		GetRotation() const {return fRot;}
	float		GetTracking() const {return fTracking;}
	float		GetSpacing() const {return fSpacing;}

	//hgeSprite*	GetSprite(char chr) const { return let[(unsigned char)chr]; }
	float		GetHeight() const { return fHeight; }
	float		GetStringWidth(const wchar_t *string, bool bMultiline = true) const;
	float		GetStringHeight(const wchar_t *string, bool bMultiline = true) const;
	float		GetStringHeightFromWidth(wchar_t *string, float width) const;

	float		RenderLetter(float x, float y, wchar_t ch);
	float		GetLetterWidth(wchar_t ch);

	//void Convert(wchar_t *str);

protected:
	hgeFont();
	hgeFont(const hgeFont &fnt);
	hgeFont&	operator= (const hgeFont &fnt);

	//char*		_get_line(char *file, char *line);

	static HGE	*hge;

	static wchar_t	buffer[1024];

	HTEXTURE *tex;
	int texcnt;
	hgeSprite **let;
	int letcnt;
	int *letid;
	//int iN, iR;
	//float *pre;
	//float *post;
	float *xoff, *yoff, *xadv;
	float		fHeight;
	float		fScale;
	float		fProportion;
	float		fRot;
	float		fTracking;
	float		fSpacing;

	float padding[4];

	DWORD		dwCol;
	float		fZ;
	int			nBlend;
};


#endif
