#ifndef GDIFONT_H
#define GDIFONT_H

#include "hgesprite.h"

class hgeFont2
{
public:
	hgeFont2(const wchar_t* lpsFontName, int nFaceSize, BOOL bBold = FALSE, BOOL bItalic = FALSE, BOOL bAntialias = TRUE);
	~hgeFont2(void);

public:
	// 渲染文本
	virtual void	Render(float x, float y, int align , const wchar_t* text ,int strsize = -1);
	virtual void	Print( float x, float y, int align , const wchar_t *format, ... );
	virtual void	Printb( float x, float y, float w, float h, int align , const wchar_t *format, ... );

	// 设置与获取颜色
	virtual void	SetColor( DWORD dwColor, int i = -1 );
	virtual DWORD	GetColor( int i = 0 );

	// 获取文本宽高
	float		GetHeight() const { return m_nFontSize; }
	virtual SIZE	GetTextSize( const wchar_t* text );

	// 根据坐标获取字符
	virtual wchar_t	GetCharacterFromPos( const wchar_t* text, float pixel_x, float pixel_y );

	// 设置字间距
	virtual void	SetKerningWidth( float kerning );
	virtual void	SetKerningHeight( float kerning );

	// 获取字间距
	virtual float	GetKerningWidth();
	virtual float	GetKerningHeight();

	// 字体大小
	virtual float	GetFontSize();

private:
	// 根据字符获取轮廓
	unsigned int	GetGlyphByCharacter( wchar_t c );
	inline float	GetWidthFromCharacter( wchar_t c, bool original = false );
	inline void		CacheCharacter(unsigned int idx, wchar_t c);

	typedef struct tagEngineFontGlyph
	{
		HTEXTURE	t;
		float		w;
		float		h;
		float		x;
		float		y;
		float		c;
	}TENGINEFONTGLYPH;

	static const unsigned int font_count = 0xFFFF;// = sizeof(wchar_t);
	TENGINEFONTGLYPH	m_Glyphs[font_count];
	UINT				m_nAntialias;//反锯齿
	LONG				m_nAscent;//基线
	DWORD				m_dwFontColor;
	float				m_nFontSize;
	float				m_nKerningWidth;
	float				m_nKerningHeight;

	HGE*				m_pHGE;
	hgeSprite*			m_pSprite;

	// GDI设备
	HDC					m_hMemDC;
	HFONT				m_hFont;
};
#endif//GDIFONT_H
