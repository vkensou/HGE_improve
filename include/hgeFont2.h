#ifndef GDIFONT_H
#define GDIFONT_H

#include "hgesprite.h"

class hgeFont2
{
public:
	hgeFont2(const wchar_t* lpsFontName, int nFaceSize, BOOL bBold = FALSE, BOOL bItalic = FALSE, BOOL bAntialias = TRUE);
	~hgeFont2(void);

public:
	// ��Ⱦ�ı�
	virtual void	Render(float x, float y, int align , const wchar_t* text ,int strsize = -1);
	virtual void	Print( float x, float y, int align , const wchar_t *format, ... );
	virtual void	Printb( float x, float y, float w, float h, int align , const wchar_t *format, ... );

	// �������ȡ��ɫ
	virtual void	SetColor( DWORD dwColor, int i = -1 );
	virtual DWORD	GetColor( int i = 0 );

	// ��ȡ�ı����
	float		GetHeight() const { return m_nFontSize; }
	virtual SIZE	GetTextSize( const wchar_t* text );

	// ���������ȡ�ַ�
	virtual wchar_t	GetCharacterFromPos( const wchar_t* text, float pixel_x, float pixel_y );

	// �����ּ��
	virtual void	SetKerningWidth( float kerning );
	virtual void	SetKerningHeight( float kerning );

	// ��ȡ�ּ��
	virtual float	GetKerningWidth();
	virtual float	GetKerningHeight();

	// �����С
	virtual float	GetFontSize();

private:
	// �����ַ���ȡ����
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
	UINT				m_nAntialias;//�����
	LONG				m_nAscent;//����
	DWORD				m_dwFontColor;
	float				m_nFontSize;
	float				m_nKerningWidth;
	float				m_nKerningHeight;

	HGE*				m_pHGE;
	hgeSprite*			m_pSprite;

	// GDI�豸
	HDC					m_hMemDC;
	HFONT				m_hFont;
};
#endif//GDIFONT_H
