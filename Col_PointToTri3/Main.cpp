

#include "_StdAfx.h"


CMain::CMain()
{
	m_pD3DXFont	= NULL;
	m_pInput	= NULL;
	m_pCam		= NULL;
	m_pGrid		= NULL;

	m_pColl		= NULL;
}


HRESULT CMain::Init()
{
	SAFE_NEWCREATE1(m_pInput, CMcInput		, m_hWnd);
	SAFE_NEWCREATE1(m_pCam	, CMcCam		, m_pd3dDevice);
	SAFE_NEWCREATE1(m_pGrid	, CMcGrid		, m_pd3dDevice);

	SAFE_NEWCREATE1(m_pColl	, CMcCollision	, m_pd3dDevice);


	D3DXFONT_DESC hFont =
	{
		16, 0
		, FW_NORMAL
		, 1
		, FALSE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS
		, ANTIALIASED_QUALITY
		, FF_DONTCARE
		, "Arial"
	};

	if( FAILED( D3DXCreateFontIndirect(m_pd3dDevice, &hFont, &m_pD3DXFont ) ) )
		return -1;

	return S_OK;
}


HRESULT CMain::Destroy()
{
	SAFE_RELEASE( m_pD3DXFont );

	SAFE_DELETE(	m_pInput	);
	SAFE_DELETE(	m_pCam		);
	SAFE_DELETE(	m_pGrid		);

	SAFE_DELETE(	m_pColl		);

	return S_OK;
}



HRESULT CMain::Restore()
{
	if(m_pD3DXFont)
		m_pD3DXFont->OnResetDevice();

	return S_OK;
}


HRESULT CMain::Invalidate()
{
	if(m_pD3DXFont)
		m_pD3DXFont->OnLostDevice();

	return S_OK;
}




HRESULT CMain::FrameMove()
{
	SAFE_FRMOV(	m_pInput	);
	float camSpeed = m_fElapsedTime* 500.0F;

	// Wheel mouse...
	D3DXVECTOR3 vcD = m_pInput->GetMouseEps();

	if(vcD.z !=0.f)
		m_pCam->MoveForward(-vcD.z* .1f, 1.f);

	if(m_pInput->KeyState('W'))					// W
		m_pCam->MoveForward( camSpeed, 1.f);

	if(m_pInput->KeyState('S'))					// S
		m_pCam->MoveForward(-camSpeed, 1.f);

	if(m_pInput->KeyState('A'))					// A
		m_pCam->MoveSide(-camSpeed);

	if(m_pInput->KeyState('D'))					// D
		m_pCam->MoveSide(camSpeed);


	if(m_pInput->BtnPress(1))
	{
		D3DXVECTOR3 vcDelta = m_pInput->GetMouseEps();
		m_pCam->Rotation(vcDelta);
	}

	SAFE_FRMOV(	m_pCam	);
	m_pCam->SetTransform();

	SAFE_FRMOV(	m_pColl	);


	sprintf( m_sMsg, "%s %s", m_strDeviceStats, m_strFrameStats	);

	return S_OK;
}


HRESULT CMain::Render()
{
	HRESULT hr=0;

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;


	m_pd3dDevice->Clear( 0L
						, NULL
						, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL
						, 0x00006699
						, 1.0f
						, 0L
						);

	m_pCam->SetTransform();


	SAFE_RENDER(	m_pGrid		);

	SAFE_RENDER(	m_pColl		);

	RenderText();

	m_pd3dDevice->EndScene();

	return S_OK;
}



void CMain::RenderText()
{
	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE);
	m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE , FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pd3dDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	RECT	rc;
	SetRect(&rc, 2, 10, m_d3dsdBackBuffer.Width - 20, 30);
	m_pD3DXFont->DrawText(NULL, m_sMsg, -1, &rc, 0, D3DCOLOR_ARGB(255,255,255,0));
}


LRESULT CMain::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if(m_pInput)
		m_pInput->MsgProc(hWnd, msg, wParam, lParam);

	switch( msg )
	{
		case WM_PAINT:
		{
			if( m_bLoadingApp )
			{
				HDC m_hDC = GetDC( hWnd );
				RECT rc;
				GetClientRect( hWnd, &rc );
				ReleaseDC( hWnd, m_hDC );
			}
			break;
		}

	}

	return CD3DApplication::MsgProc( hWnd, msg, wParam, lParam );
}