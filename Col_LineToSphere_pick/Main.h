#ifndef _MAIN_H_
#define _MAIN_H_



class CMain : public CD3DApplication
{
public:
	ID3DXFont*	m_pD3DXFont;													// D3DX font
	char		m_sMsg[512];

	CMcInput*	m_pInput;
	CMcCam*		m_pCam;
	CMcGrid*	m_pGrid;

	CMcPicking*	m_pColl;
	

public:
	virtual HRESULT Init();
	virtual HRESULT Destroy();
	
	virtual HRESULT Restore();
	virtual HRESULT Invalidate();
	
	virtual HRESULT Render();
	virtual HRESULT FrameMove();

protected:
	void	RenderText();
	
	
public:
	LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	CMain();	
};


extern CMain*	g_pApp;


#endif