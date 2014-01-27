/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hgeResourceManager helper class header
*/


#ifndef HGERESOURCE_H
#define HGERESOURCE_H


#include "hge.h"
#include "hgesprite.h"
#include "hgeanim.h"
#include "hgefont.h"
#include "hgeparticle.h"
#include "hgedistort.h"
#include "hgestrings.h"
#include "hgeanim2.h"

#define RESTYPES 13
#define MAXRESCHARS 128


class hgeResourceManager;

struct ResDesc
{
	wchar_t		name[MAXRESCHARS];
	int			resgroup;
	DWORD		handle;
	ResDesc*	next;

	ResDesc()	{ hge=hgeCreate(HGE_VERSION); }
	~ResDesc()	{ hge->Release(); }

	virtual DWORD Get(hgeResourceManager *rm) = 0;
	virtual void  Free() = 0;

protected:
	static HGE	*hge;
};

/*
** HGE Resource manager class
*/
class hgeResourceManager
{
public:
	hgeResourceManager(const wchar_t *scriptname=0);
	~hgeResourceManager();

	void				ChangeScript(const wchar_t *scriptname=0);
	bool				Precache(int groupid=0);
	void				Purge(int groupid=0);

	void*				GetResource(const wchar_t *name);
	HTEXTURE			GetTexture(const wchar_t *name);
	HEFFECT				GetEffect(const wchar_t *name);
	HMUSIC				GetMusic(const wchar_t *name);
	HSTREAM				GetStream(const wchar_t *name);
	HTARGET				GetTarget(const wchar_t *name);

	hgeSprite*			GetSprite(const wchar_t *name);
	hgeAnimation*		GetAnimation(const wchar_t *name);
	hgeFont*			GetFont(const wchar_t *name);
	hgeParticleSystem*	GetParticleSystem(const wchar_t *name);
	hgeDistortionMesh*	GetDistortionMesh(const wchar_t *name);
	hgeStringTable*		GetStringTable(const wchar_t *name);

	ResDesc*			res[RESTYPES];

private:
	hgeResourceManager(const hgeResourceManager &);
	hgeResourceManager&	operator= (const hgeResourceManager&);
	void				_remove_all();
	void				_parse_script(const wchar_t *scriptname=0);

	static HGE			*hge;
};


#endif
