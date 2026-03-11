// Implementation of the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


INT LcMath_CollisionLineToPlane(const D3DXPLANE* pPlane, const D3DXVECTOR3* pLine)
{
	FLOAT D1 = D3DXPlaneDotCoord(pPlane, &pLine[0]);
	FLOAT D2 = D3DXPlaneDotCoord(pPlane, &pLine[1]);

	// Collision
	if(D1 * D2<= 0)
		return 0;

	return -1;
}



INT LcMath_CollisionLineToPlane(const D3DXVECTOR3* pTri, const D3DXVECTOR3* pLine)
{
	D3DXVECTOR3 N;
	FLOAT		D;

	D3DXVECTOR3 vcA = pTri[1] - pTri[0];
	D3DXVECTOR3 vcB = pTri[2] - pTri[0];

	D3DXVec3Cross(&N, &vcA, &vcB);
	D = - D3DXVec3Dot(&N, &pTri[0]);

	FLOAT D1 = D3DXVec3Dot(&N, &pLine[0]) + D;
	FLOAT D2 = D3DXVec3Dot(&N, &pLine[1]) + D;

	// Collision
	if(D1 * D2<= 0)
		return 0;

	return -1;
}


CMcCollision::CMcCollision()
{
	m_pDev	= NULL;

	m_bColl = FALSE;
}

CMcCollision::~CMcCollision()
{
	Destroy();
}


INT CMcCollision::Create(LPDIRECT3DDEVICE9 pDev)
{
	m_pDev	= pDev;

	m_pTri[0]	= VtxD( 10, -100,  200, 0xFFFF7777);
	m_pTri[1]	= VtxD(500,  200,  300, 0xFF77FF77);
	m_pTri[2]	= VtxD(400,  50,    20, 0xFF7777FF);

	m_pLine[0].p = D3DXVECTOR3(  100, 300,  300);
	m_pLine[1].p = D3DXVECTOR3(  200, 100,  200);

	return 0;
}


void CMcCollision::Destroy()
{
}


INT	CMcCollision::FrameMove()
{
	CMcInput*	pInput = g_pApp->m_pInput;

	if(pInput->KeyState(VK_UP))
	{
		m_pLine[0].p.y += 1;
		m_pLine[1].p.y += 1;
	}

	if(pInput->KeyState(VK_DOWN))
	{
		m_pLine[0].p.y -= 1;
		m_pLine[1].p.y -= 1;
	}

	if(pInput->KeyState(VK_LEFT))
	{
		m_pLine[0].p.x -= 1;
		m_pLine[1].p.x -= 1;
	}

	if(pInput->KeyState(VK_RIGHT))
	{
		m_pLine[0].p.x += 1;
		m_pLine[1].p.x += 1;
	}

	D3DXVECTOR3 pTri[3];
	pTri[0] = m_pTri[0].p;
	pTri[1] = m_pTri[1].p;
	pTri[2] = m_pTri[2].p;

	D3DXVECTOR3 pLine[2];

	pLine[0] = m_pLine[0].p;
	pLine[1] = m_pLine[1].p;

	m_bColl = LcMath_CollisionLineToPlane(pTri, pLine);
	
	return 0;
}

void CMcCollision::Render()
{
	m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pDev->SetRenderState( D3DRS_LIGHTING,  FALSE);
	m_pDev->SetRenderState( D3DRS_ALPHABLENDENABLE,  FALSE);
	m_pDev->SetRenderState( D3DRS_ALPHATESTENABLE,  FALSE);
	
	m_pDev->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);

	if( SUCCEEDED(m_bColl) )
		m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	m_pDev->SetTexture(0, 0);
	m_pDev->SetFVF(VtxD::FVF);

	m_pDev->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, m_pTri, sizeof(VtxD));


	m_pDev->DrawPrimitiveUP(D3DPT_LINELIST, 1, m_pLine, sizeof(VtxD));
}

