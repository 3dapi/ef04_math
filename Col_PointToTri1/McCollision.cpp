// Implementation of the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


FLOAT LcMath_DotAngle(const D3DXVECTOR3* p0, const D3DXVECTOR3* p1, const D3DXVECTOR3* p2)
{
	D3DXVECTOR3 vcA = *p1 - *p0;
	D3DXVECTOR3 vcB = *p2 - *p0;

	D3DXVec3Normalize(&vcA,&vcA);
	D3DXVec3Normalize(&vcB,&vcB);

	FLOAT fDot = D3DXVec3Dot(&vcA, &vcB);

	if(fDot>0.9999f)
		return 0.f;
	else if(fDot<-0.9999f)
		return D3DX_PI;

	fDot = acosf(fDot);

	return fDot;
}

BOOL LcMath_CollisionPointToTriangle(D3DXVECTOR3* vcOut
									, const D3DXVECTOR3* pTri
									, const D3DXVECTOR3* pPoint)
{
	FLOAT	fA;
	FLOAT	fB;
	FLOAT	fC;

	fA = LcMath_DotAngle(pPoint, &pTri[0], &pTri[1]);
	fB = LcMath_DotAngle(pPoint, &pTri[1], &pTri[2]);
	fC = LcMath_DotAngle(pPoint, &pTri[2], &pTri[0]);

	if(vcOut)
		*vcOut = *pPoint;

	if(fA+fB+fC>=(D3DX_PI*2-0.001f))
		return 0;

	return -1;
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

	m_pTri[0]	= VtxD( 10,   0,   10, 0xFFFF7777);
	m_pTri[1]	= VtxD(200,   0,  300, 0xFF77FF77);
	m_pTri[2]	= VtxD(400,   0,   20, 0xFF7777FF);

	m_Pos = D3DXVECTOR3(  100, 0,  300);

	D3DXCreateSphere(m_pDev, 3, 8, 8, &m_pMsh, 0);

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
		m_Pos.z += 1;
	}

	if(pInput->KeyState(VK_DOWN))
	{
		m_Pos.z -= 1;
	}

	if(pInput->KeyState(VK_LEFT))
	{
		m_Pos.x -= 1;
	}

	if(pInput->KeyState(VK_RIGHT))
	{
		m_Pos.x += 1;
	}

	D3DXVECTOR3 pTri[3];
	pTri[0] = m_pTri[0].p;
	pTri[1] = m_pTri[1].p;
	pTri[2] = m_pTri[2].p;

//	for(int i=0; i<20000; ++i)
		m_bColl = LcMath_CollisionPointToTriangle(NULL, pTri, &m_Pos);

	return 0;
}

void CMcCollision::Render()
{
	m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pDev->SetRenderState( D3DRS_LIGHTING,  FALSE);
	m_pDev->SetRenderState( D3DRS_ALPHABLENDENABLE,  FALSE);
	m_pDev->SetRenderState( D3DRS_ALPHATESTENABLE,  FALSE);

	m_pDev->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);

	if(SUCCEEDED(m_bColl))
		m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pDev->SetTexture(0, 0);
	m_pDev->SetFVF(VtxD::FVF);

	m_pDev->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, m_pTri, sizeof(VtxD));


	D3DLIGHT9 Lgt;
	D3DMATERIAL9	mtl;
	D3DUtil_InitLight( Lgt, D3DLIGHT_DIRECTIONAL, -1.0f, -1.0f, 2.0f );
	D3DUtil_InitMaterial(mtl,1.0f, 0.0f,0.0f);

	m_pDev->SetLight( 0, &Lgt );
	m_pDev->LightEnable( 0, TRUE );
	m_pDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pDev->SetRenderState( D3DRS_AMBIENT, 0x000F0F0F );

	m_pDev->SetMaterial( &mtl );

	m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	D3DXMATRIX mtW;
	D3DXMatrixIdentity(&mtW);

	mtW._41 = m_Pos.x;
	mtW._42 = m_Pos.y;
	mtW._43 = m_Pos.z;

	m_pDev->SetTransform(D3DTS_WORLD,&mtW);
	m_pMsh->DrawSubset(0);

	D3DXMatrixIdentity(&mtW);
	m_pDev->SetTransform(D3DTS_WORLD,&mtW);

	m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
}

