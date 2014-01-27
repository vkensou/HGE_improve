/*
** Haaf's Game Engine 1.7
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Resource script parser implementation
*/

#include "parser.h"


HGE *RScriptParser::hge=0;


struct keyword
{
	wchar_t*	word;
	int		code;
};

keyword keytable[]=
{
	{ L"=",			TTEQUALS		},
	{ L":",			TTBASED			},
	{ L",",			TTSEPARATOR		},
	{ L"{",			TTOPENBLOCK		},
	{ L"}",			TTCLOSEBLOCK	},
	{ L"true",		TTBOOL			},
	{ L"false",		TTBOOL			},

	{ L"Include",	TTRES_INCLUDE	},
	{ L"Resource",	TTRES_RESOURCE	},
	{ L"Texture",	TTRES_TEXTURE	},
	{ L"Sound",		TTRES_SOUND		},
	{ L"Music",		TTRES_MUSIC		},
	{ L"Stream",		TTRES_STREAM	},
	{ L"Target",		TTRES_TARGET	},
	{ L"Sprite",		TTRES_SPRITE	},
	{ L"Animation",	TTRES_ANIMATION	},
	{ L"Font",		TTRES_FONT		},
	{ L"Particle",	TTRES_PARTICLE	},
	{ L"Distortion",	TTRES_DISTORT	},
	{ L"StringTable",TTRES_STRTABLE	},

	{ L"filename",	TTPAR_FILENAME	},
	{ L"resgroup",	TTPAR_RESGROUP	},
	{ L"mipmap",		TTPAR_MIPMAP	},
	{ L"amplify",	TTPAR_AMPLIFY	},
	{ L"size",		TTPAR_SIZE		},
	{ L"zbuffer",	TTPAR_ZBUFFER	},
	{ L"texture",	TTPAR_TEXTURE	},
	{ L"rect",		TTPAR_RECT		},
	{ L"hotspot",	TTPAR_HOTSPOT	},
	{ L"blendmode",	TTPAR_BLENDMODE	},
	{ L"color",		TTPAR_COLOR		},
	{ L"zorder",		TTPAR_ZORDER	},
	{ L"flip",		TTPAR_FLIP		},
	{ L"scale",		TTPAR_SCALE		},
	{ L"proportion",	TTPAR_PROPORTION},
	{ L"rotation",	TTPAR_ROTATION	},
	{ L"frames",		TTPAR_FRAMES	},
	{ L"fps",		TTPAR_FPS		},
	{ L"mode",		TTPAR_MODE		},
	{ L"tracking",	TTPAR_TRACKING	},
	{ L"spacing",	TTPAR_SPACING	},
	{ L"sprite",		TTPAR_SPRITE	},
	{ L"mesh",		TTPAR_MESH		},

	{ L"COLORMUL",	TTCON_COLORMUL	},
	{ L"COLORADD",	TTCON_COLORADD	},
	{ L"ALPHABLEND",	TTCON_ALPHABLND	},
	{ L"ALPHAADD",	TTCON_ALPHAADD	},
	{ L"ZWRITE",		TTCON_ZWRITE	},
	{ L"NOZWRITE",	TTCON_NOZWRITE	},
	{ L"FORWARD",	TTCON_FORWARD	},
	{ L"REVERSE",	TTCON_REVERSE	},
	{ L"PINGPONG",	TTCON_PINGPONG	},
	{ L"NOPINGPONG",	TTCON_NOPINGPONG},
	{ L"LOOP",		TTCON_LOOP		},
	{ L"NOLOOP",		TTCON_NOLOOP	},
	{ L"CIRCLE",		TTCON_CIRCLE	},
	{ L"RECT",		TTCON_RECT		},
	{ L"ALPHA",		TTCON_ALPHA		},

	{ NULL,			TTNONE			}
};

RScriptParser::RScriptParser(wchar_t *name, wchar_t *scr)
{
	hge=hgeCreate(HGE_VERSION);

	scriptname=name;
	script=scr;
	tokenvalue[0]=0;
	tokentype=TTNONE;
	line=1;
}

int RScriptParser::get_token()
{
	int i;

	// Skip whitespaces and comments

	for(;;)
	{
		while(*script==' ' || *script=='\t' || *script=='\n' || *script=='\r')
		{
			if(*script=='\n') line++;
			script++;
		}
		if(*script==';') while(*script && *script!='\n' && *script!='\r') script++;
		else break;
	}

	// End of script

	if(!*script) { tokentype=TTEND; tokenvalue[0]=0; return tokentype; }

	// Number

	if((*script>='0' && *script<='9') || *script=='.' || *script=='-')
	{
		tokentype=TTNUMBER;
		for(i=0;(*script>='0' && *script<='9') || *script=='.' || *script=='-';i++)
			 tokenvalue[i]=*script++;

		// Hexadecimal number starting with decimal digit

		if((*script>='A' && *script<='F') || (*script>='a' && *script<='f'))
		{
			tokentype=TTSTRING;
			for(; (*script>='A' && *script<='F') || (*script>='a' && *script<='f') ; i++)
				 tokenvalue[i]=*script++;
		}

		tokenvalue[i]=0;
		return tokentype;
	}

	// Quoted string

	if(*script=='"')
	{
		tokentype=TTSTRING;
		script++;
		for(i=0;*script && *script!='"' && *script!='\n' && *script!='\r';i++)
			 tokenvalue[i]=*script++;
		tokenvalue[i]=0;
		if(*script) script++;
		return tokentype;
	}

	// Keyword

	for(i=0;keytable[i].word;i++)
		if(!strtkcmp(keytable[i].word, script))
		{
			tokentype = keytable[i].code;
			wcscpy(tokenvalue,keytable[i].word);
			script+=wcslen(keytable[i].word);
			return tokentype;
		}

	// Unquoted string or hexadecimal number

	tokentype=TTSTRING;
	for(i=0;
		*script && *script!=' ' && *script!='\t' && *script!='\n' && *script!='\r'
		&& *script!=',' && *script!='=' && *script!='{' && *script!='}' && *script!=':';
		i++)
		tokenvalue[i]=*script++;
	tokenvalue[i]=0;
	return tokentype;
}

bool RScriptParser::strtkcmp(wchar_t *str, wchar_t *mem)
{
	int i,len=wcslen(str);
	for(i=0;i<len;i++)
	{
		if(!mem[i]) return true;
		if(mem[i] != str[i]) return true;
	}
	return false;
}

DWORD RScriptParser::tkn_hex()
{
	int i;
	DWORD dw=0;
	wchar_t chr;
	for(i=0; tokenvalue[i]; i++)
	{
		chr=tokenvalue[i];
		if(chr >= 'a') chr-='a'-':';
		if(chr >= 'A') chr-='A'-':';
		chr-='0';
		if(chr>0xF) chr=0xF;
		dw=(dw << 4) | chr;
	}
	return dw;
}

void RScriptParser::ScriptPostError(wchar_t *msg1, wchar_t *msg2)
{
	hge->System_Log(L"%s, line %d: %s'%s'%s",
		get_name(), get_line(), msg1, tokenvalue[0] ? tkn_string():L"<EOF>", msg2);
}
