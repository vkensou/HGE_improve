/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hgeFont helper class implementation
*/


#include "..\..\include\hgefont.h"
#include <stdlib.h>
#include <stdio.h>


HGE *hgeFont::hge=0;
wchar_t hgeFont::buffer[1024];


hgeFont::hgeFont(const wchar_t *szFont, bool bMipmap)
{
	hge = hgeCreate(HGE_VERSION);

	fHeight=0.0f;
	fScale=1.0f;
	fProportion=1.0f;
	fRot=0.0f;
	fTracking=0.0f;
	fSpacing=1.0f;

	fZ=0.5f;
	nBlend=BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE;
	dwCol=0xFFFFFFFF;

	texcnt = 0;
	tex = 0;
	letcnt = 0;
	let = 0;
	letid = 0;
	//pre = 0;
	//post = 0;
	xoff = 0;
	yoff = 0;
	xadv = 0;
	//iN = (int)'\n';
	//iR = (int)'\r';

	int i;
	int num;
	char buf[MAX_PATH]; wchar_t buf2[MAX_PATH];
	wchar_t dir[MAX_PATH], file[MAX_PATH];
	wchar_t *pbuf;
	int id, x, y, width, height, page;

	wcscpy(file, hge->Resource_MakePath(szFont));
	FILE *f = _wfopen(file , L"rb");
	if(!f) {
		hge->System_Log(L"Font '%s' not found.", szFont);
		return;
	}

	memset(padding, 0, sizeof(int) * 4);

	WORD ver;
	fread(&ver, 2, 1, f);
	if(ver == 110) {
		for(i = 0; i < 4; i++) {
			fread(&num, 4, 1, f);
			//padding[i] = (float)num;
		}
	} else {
		fseek(f, 0, SEEK_SET);
	}

	wcscpy(dir, file);
	pbuf = wcsrchr(dir, L'\\');
	if(!pbuf) pbuf = wcsrchr(dir, L'/');
	if(!pbuf) pbuf=dir;
	else pbuf++;
	*pbuf = L'\0';

	fread(&num, 4, 1, f);
	fHeight = (float)num;
	fread(&num, 4, 1, f);
	texcnt = num;
	tex = new HTEXTURE[texcnt];
	for(i = 0; i < texcnt; i++) {

		fread(&num, 4, 1, f);
		fread(&buf, num, 1, f);
		buf[num] = '\0';
		C2W(buf, buf2, MAX_PATH-1);

		swprintf(file, L"%s%s", dir, buf2);
		tex[i] = hge->Texture_Load(file, 0, bMipmap);
	}
	fread(&num, 4, 1, f);
	letcnt = num;
	let = new hgeSprite*[letcnt];
	letid = new int[99000];
	memset(letid, 0, sizeof(int) * 99000);
	//pre = new float[letcnt];
	//post = new float[letcnt];
	xoff = new float[letcnt]; memset(xoff, 0, sizeof(float)*letcnt);
	yoff = new float[letcnt]; memset(yoff, 0, sizeof(float)*letcnt);
	xadv = new float[letcnt]; memset(xadv, 0, sizeof(float)*letcnt);
	for(i = 0; i < letcnt; i++) {
		fread(&id, 4, 1, f);
		fread(&x, 4, 1, f);
		fread(&y, 4, 1, f);
		fread(&width, 4, 1, f);
		fread(&height, 4, 1, f);
		fread(&num, 4, 1, f); xoff[i] = (float)num;
		fread(&num, 4, 1, f); yoff[i] = (float)num;
		fread(&num, 4, 1, f); xadv[i] = (float)num;
		fread(&page, 4, 1, f);
		fread(&num, 4, 1, f);

		letid[id] = i;
		//if(letid[i] == '\n') iN = i;
		//if(letid[i] == '\r') iR = i;

		let[i] = new hgeSprite(tex[page], (float)x, (float)y, (float)width, (float)height);
		//let[i]->SetHotSpot(0, height);
	}

	fclose(f);


	/*void	*data;
	DWORD	size;
	char	*desc, *pdesc;
	char	linebuf[256];
	char	buf[MAX_PATH], *pbuf;
	char	chr;
	int		i, x, y, w, h, a, c;

	// Setup variables
	
	hge=hgeCreate(HGE_VERSION);

	fHeight=0.0f;
	fScale=1.0f;
	fProportion=1.0f;
	fRot=0.0f;
	fTracking=0.0f;
	fSpacing=1.0f;
	hTexture=0;

	fZ=0.5f;
	nBlend=BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE;
	dwCol=0xFFFFFFFF;

	ZeroMemory( &letters, sizeof(letters) );
	ZeroMemory( &pre, sizeof(letters) );
	ZeroMemory( &post, sizeof(letters) );
	
	// Load font description

	data=hge->Resource_Load(szFont, &size);
	if(!data) return;

	desc = new char[size+1];
	memcpy(desc,data,size);
	desc[size]=0;
	hge->Resource_Free(data);

	pdesc=_get_line(desc,linebuf);
	if(strcmp(linebuf, FNTHEADERTAG))
	{
		hge->System_Log("Font %s has incorrect format.", szFont);
		delete[] desc;	
		return;
	}

	// Parse font description

	while(pdesc = _get_line(pdesc,linebuf))
	{
		if(!strncmp(linebuf, FNTBITMAPTAG, sizeof(FNTBITMAPTAG)-1 ))
		{
			strcpy(buf,szFont);
			pbuf=strrchr(buf,'\\');
			if(!pbuf) pbuf=strrchr(buf,'/');
			if(!pbuf) pbuf=buf;
			else pbuf++;
			if(!sscanf(linebuf, "Bitmap = %s", pbuf)) continue;

			hTexture=hge->Texture_Load(buf, 0, bMipmap);
			if(!hTexture)
			{
				delete[] desc;	
				return;
			}
		}

		else if(!strncmp(linebuf, FNTCHARTAG, sizeof(FNTCHARTAG)-1 ))
		{
			pbuf=strchr(linebuf,'=');
			if(!pbuf) continue;
			pbuf++;
			while(*pbuf==' ') pbuf++;
			if(*pbuf=='\"')
			{
				pbuf++;
				i=(unsigned char)*pbuf++;
				pbuf++; // skip "
			}
			else
			{
				i=0;
				while((*pbuf>='0' && *pbuf<='9') || (*pbuf>='A' && *pbuf<='F') || (*pbuf>='a' && *pbuf<='f'))
				{
					chr=*pbuf;
					if(chr >= 'a') chr-='a'-':';
					if(chr >= 'A') chr-='A'-':';
					chr-='0';
					if(chr>0xF) chr=0xF;
					i=(i << 4) | chr;
					pbuf++;
				}
				if(i<0 || i>255) continue;
			}
			sscanf(pbuf, " , %d , %d , %d , %d , %d , %d", &x, &y, &w, &h, &a, &c);

			letters[i] = new hgeSprite(hTexture, (float)x, (float)y, (float)w, (float)h);
			pre[i]=(float)a;
			post[i]=(float)c;
			if(h>fHeight) fHeight=(float)h;
		}
	}

	delete[] desc;	*/
}


hgeFont::~hgeFont()
{
	int i;
	for(i=0; i<letcnt; i++)
		if(let[i]) delete let[i];
	delete[] let;
	for(i=0; i<texcnt; i++)
		if(tex[i]) hge->Texture_Free(tex[i]);
	delete[] tex;
	delete[] letid;
	//delete pre;
	//delete post;
	delete[] xoff;
	delete[] yoff;
	delete[] xadv;
	hge->Release();
}

void hgeFont::Render(float x, float y, int align, const wchar_t *string)
{
	if(!string || !letid) return;
	int i;
	float	fx=x;

	align &= HGETEXT_HORZMASK;
	if(align==HGETEXT_RIGHT) fx-=GetStringWidth(string, false);
	if(align==HGETEXT_CENTER) fx-=int(GetStringWidth(string, false) * 0.5f);

	/*int max, cnt = 0;
	hgeVertex *ver = hge->Gfx_StartBatch(HGEPRIM_QUADS, hTexture, BLEND_DEFAULT, &max);

	if(!ver || max > strlen(string)) max = strlen(string);*/

	while(*string)
	{
		/*if(ver && cnt >= max) {
			hge->Gfx_FinishBatch(max);
			ver = hge->Gfx_StartBatch(HGEPRIM_QUADS, hTexture, BLEND_DEFAULT, &max);
			cnt = 0;
		}*/
		if(*string == L'\n')
		{
			y += int(fHeight*fScale*fSpacing);
			fx = x;
			if(align == HGETEXT_RIGHT)  fx -= GetStringWidth(string+1, false);
			if(align == HGETEXT_CENTER) fx -= int(GetStringWidth(string+1, false) * 0.5f);
		}
		else
		{
			i=letid[*string];
			if(let[i])
			{
				fx += xoff[i]*fScale*fProportion;
				let[i]->RenderEx((float)(int)fx, (float)(int)(y+yoff[i]*fScale), fRot, fScale*fProportion, fScale);
				/*if(*string == TXT(' '))
					fx += (/ * let[i]->GetWidth()* /xadv[i]+fTracking)*fScale*fProportion*2;
				else*/
					fx += (/*let[i]->GetWidth()*/xadv[i]-xoff[i]+fTracking)*fScale*fProportion;
			}
		}
		string++;
		//cnt++;
	}

	//if(ver) hge->Gfx_FinishBatch(max);
}

void hgeFont::printf(float x, float y, int align, const wchar_t *format, ...)
{
	char	*pArg=(char *) &format+sizeof(format);

	memset(buffer, 0, 2048);
	_vsnwprintf(buffer, sizeof(buffer)/sizeof(wchar_t)-1, format, pArg);
	//buffer[sizeof(buffer)-1]=0;
	//vsprintf(buffer, format, pArg);

	Render(x,y,align,buffer);
}

void hgeFont::printfb(float x, float y, float w, float h, int align, const wchar_t *format, ...)
{
	wchar_t	chr, *pbuf, *prevword, *linestart;
	int		i,lines=0;
	float	tx, ty, hh, ww;
	char	*pArg=(char *) &format+sizeof(format);

	memset(buffer, 0, 2048);
	_vsnwprintf(buffer, sizeof(buffer)/sizeof(wchar_t)-1, format, pArg);
	//buffer[sizeof(buffer)-1]=(unsigned short)L'\0';
	//vsprintf(buffer, format, pArg);

	linestart=buffer;
	pbuf=buffer;
	prevword=0;

	for(;;)
	{
		i=0;
		while(pbuf[i] && pbuf[i]!=L' ' && pbuf[i]!=L'\n') i++;

		chr=pbuf[i];
		pbuf[i]=0;
		ww=GetStringWidth(linestart);
		pbuf[i]=chr;

		if(ww > w)
		{
			if(pbuf==linestart)
			{
				pbuf[i]=L'\n';
				linestart=&pbuf[i+1];
			}
			else
			{
				*prevword=L'\n';
				linestart=prevword+1;
			}

			lines++;
		}

		if(pbuf[i]==L'\n')
		{
			prevword=&pbuf[i];
			linestart=&pbuf[i+1];
			pbuf=&pbuf[i+1];
			lines++;
			continue;
		}

		if(!pbuf[i]) {lines++;break;}

		prevword=&pbuf[i];
		pbuf=&pbuf[i+1];
	}
	
	tx=x;
	ty=y;
	hh=fHeight*fSpacing*fScale*lines;

	switch(align & HGETEXT_HORZMASK)
	{
		case HGETEXT_LEFT: break;
		case HGETEXT_RIGHT: tx+=w; break;
		case HGETEXT_CENTER: tx+=int(w/2); break;
	}

	switch(align & HGETEXT_VERTMASK)
	{
		case HGETEXT_TOP: break;
		case HGETEXT_BOTTOM: ty+=h-hh; break;
		case HGETEXT_MIDDLE: ty+=int((h-hh)/2); break;
	}

	Render(tx,ty,align,buffer);
}

float hgeFont::GetStringWidth(const wchar_t *string, bool bMultiline) const
{
	if(!string || !letid) return 0.f;
	int i;
	float linew, w = 0;

	while(*string)
	{
		linew = 0;

		while(*string && *string != L'\n')
		{
			i=letid[*string];
			if(let[i])
				linew += /*let[i]->GetWidth()*/xadv[i]+fTracking;

			string++;
		}

		if(!bMultiline) return linew*fScale*fProportion;

		if(linew > w) w = linew;

		while (*string == L'\n' || *string == L'\r') string++;
	}

	return w*fScale*fProportion;
}

float hgeFont::GetStringHeight(const wchar_t *string, bool bMultiline) const {
	if(!string || !letid) return 0.f;
	if(!bMultiline) return fHeight*fSpacing*fScale;
	
	int h = 1;

	while(*string) {
		if(*string == L'\n') {
			h++;
		}
		string++;
	}

	return (float)h*fHeight*fSpacing*fScale;
}

float hgeFont::GetStringHeightFromWidth(wchar_t *string, float width) const {
	wchar_t	chr, *pbuf, *prevword, *linestart;
	int		i,lines=0;
	float	ww;

	linestart=string;
	pbuf=string;
	prevword=0;

	for(;;)
	{
		i=0;
		while(pbuf[i] && pbuf[i]!=L' ' && pbuf[i]!=L'\n') i++;

		chr=pbuf[i];
		pbuf[i]=0;
		ww=GetStringWidth(linestart);
		pbuf[i]=chr;

		if(ww > width)
		{
			if(pbuf==linestart)
			{
				//pbuf[i]=TXT('\n');
				linestart=&pbuf[i+1];
			}
			else
			{
				//*prevword=TXT('\n');
				linestart=prevword+1;
			}

			lines++;
		}

		if(pbuf[i]==L'\n')
		{
			prevword=&pbuf[i];
			linestart=&pbuf[i+1];
			pbuf=&pbuf[i+1];
			lines++;
			continue;
		}

		if(!pbuf[i]) {lines++;break;}

		prevword=&pbuf[i];
		pbuf=&pbuf[i+1];
	}
	
	return fHeight*fSpacing*fScale*lines;
}

void hgeFont::SetColor(DWORD col)
{
	dwCol = col;

	for(int i=0; i<letcnt; i++)
		if(let[i])
			let[i]->SetColor(col);
}

void hgeFont::SetZ(float z)
{
	fZ = z;

	for(int i=0; i<letcnt; i++)
		if(let[i])
			let[i]->SetZ(z);
}

void hgeFont::SetBlendMode(int blend)
{
	nBlend = blend;

	for(int i=0; i<letcnt; i++)
		if(let[i])
			let[i]->SetBlendMode(blend);
}

float hgeFont::RenderLetter(float x, float y, wchar_t ch) {
	int i=letid[ch];
	if(let[i]) {
		x += xoff[i]*fScale*fProportion;
		let[i]->RenderEx(x, y+yoff[i]*fScale, fRot, fScale*fProportion, fScale);
		return (/*let[i]->GetWidth()*/xadv[i]-xoff[i]+fTracking)*fScale*fProportion;
	}
	return 0.f;

}

float hgeFont::GetLetterWidth(wchar_t ch) {
	int i=letid[ch];
	if(let[i]) {
		return (/*let[i]->GetWidth()*/xadv[i]+fTracking)*fScale*fProportion;
	}
	return 0.f;
}


/*char *hgeFont::_get_line(char *file, char *line)
{
	int i=0;

	if(!file[i]) return 0;

	while(file[i] && file[i]!='\n' && file[i]!='\r')
	{
		line[i]=file[i];
		i++;
	}
	line[i]=0;

	while(file[i] && (file[i]=='\n' || file[i]=='\r')) i++;

	return file + i;
}*/

/*void hgeFont::Convert(wchar_t *str) {
	unsigned short c;
	int i = 0, j;
	while(i < wcslen(str)) {
	  c = (unsigned short)str[i];
		for(j = 0; j < letcnt; j++) {
			if(letid[j] == c) {
				str[i] = (wchar_t)j;
			}
		}
		i++;
	}
}*/