// Implementation of the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


INT LcMath_CollisionLineToPlane(D3DXVECTOR3* pOut			// Output Collision
								, const D3DXPLANE* pPlane	// Input Plane
								, const LcLine* pLine		// Input Line
							)
{
	D3DXVECTOR3 N = D3DXVECTOR3(pPlane->a, pPlane->b, pPlane->c);
	FLOAT		D = -pPlane->d;

	D3DXVECTOR3 P = pLine->p;
	D3DXVECTOR3 T = pLine->t;

	if(pOut)
	{
		float NT = D3DXVec3Dot(&N, &T);
		float NP = D3DXVec3Dot(&N, &P);

		*pOut = P + (D-NP)/(NT) * T;
	}

	return 0;
}


INT LcMath_CollisionLineToPlane(D3DXVECTOR3* pOut			// Output Collision
								, const D3DXVECTOR3* pTri	// Input Triangle
								, const LcLine* pLine		// Input Line
								)
{
	D3DXVECTOR3 N;
	FLOAT       D;
	
	D3DXVECTOR3 P = pLine->p;
	D3DXVECTOR3 T = pLine->t;

	D3DXVECTOR3 vcA = pTri[1] - pTri[0];
	D3DXVECTOR3 vcB = pTri[2] - pTri[0];

	D3DXVec3Cross(&N, &vcA, &vcB);
	D = D3DXVec3Dot(&N, &pTri[0]);

	if(pOut)
	{
		float NT = D3DXVec3Dot(&N, &T);
		float NP = D3DXVec3Dot(&N, &P);

		*pOut = P + (D-NP)/(NT) * T;
	}

	return 0;
}



CMcCollision::CMcCollision()
{
	m_pDev	= NULL;

	m_bColl = FALSE;
	m_pMsh	= NULL;
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


	FLOAT fR = 5;

	D3DXCreateSphere(m_pDev, fR, 10, 10, &m_pMsh, 0);


	m_vcPick = D3DXVECTOR3(0,0,0);

	return 0;
}


void CMcCollision::Destroy()
{
	SAFE_RELEASE(	m_pMsh	);
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

	LcLine pLine;

	pLine.p = m_pLine[0].p;
	pLine.t = m_pLine[1].p - m_pLine[0].p;

	m_bColl = LcMath_CollisionLineToPlane(&m_vcPick, pTri, &pLine);
	
	return 0;
}

void CMcCollision::Render()
{
	D3DLIGHT9		Lgt;
	D3DMATERIAL9	mtl;
	D3DXMATRIX		mtW;

	m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pDev->SetRenderState( D3DRS_LIGHTING,  FALSE);
	m_pDev->SetRenderState( D3DRS_ALPHABLENDENABLE,  FALSE);
	m_pDev->SetRenderState( D3DRS_ALPHATESTENABLE,  FALSE);

	m_pDev->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);


	D3DUtil_InitLight( Lgt, D3DLIGHT_DIRECTIONAL, -1.0f, -1.0f, 2.0f );
	m_pDev->SetLight( 0, &Lgt );
	m_pDev->LightEnable( 0, TRUE );
	m_pDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pDev->SetRenderState( D3DRS_AMBIENT, 0x000F0F0F );


	D3DUtil_InitMaterial(mtl,1.0f, 0.0f,0.0f);
	m_pDev->SetMaterial( &mtl );

	D3DXMatrixIdentity(&mtW);

	mtW._41 = m_vcPick.x;
	mtW._42 = m_vcPick.y;
	mtW._43 = m_vcPick.z;

	m_pDev->SetTransform(D3DTS_WORLD,&mtW);
	m_pMsh->DrawSubset(0);
	
	D3DXMatrixIdentity(&mtW);
	m_pDev->SetTransform(D3DTS_WORLD,&mtW);
	m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	m_pDev->SetTexture(0, 0);
	m_pDev->SetFVF(VtxD::FVF);
	
	m_pDev->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, m_pTri, sizeof(VtxD));
	m_pDev->DrawPrimitiveUP(D3DPT_LINELIST, 1, m_pLine, sizeof(VtxD));
}

