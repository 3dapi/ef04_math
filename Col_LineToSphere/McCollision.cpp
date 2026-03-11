// Implementation of the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


BOOL LcMath_CollisionLineToSphere(D3DXVECTOR3* pLine, D3DXVECTOR3* pC, FLOAT fR, D3DXVECTOR3* vcOut = NULL)
{
	D3DXVECTOR3 vcL;
	D3DXVECTOR3 vcT;

	vcL = pLine[1]-pLine[0];
	vcT = *pC - pLine[0];

	D3DXVec3Normalize(&vcL, &vcL);

	if(vcOut)
	{
		FLOAT		fT;
		FLOAT		fC;

		fC = D3DXVec3LengthSq(&vcT);
		fT = D3DXVec3Dot(&vcL, &vcT);

		*vcOut = pLine[0] + fT * vcL;
		fC -= fT * fT;

		if(fC < fR*fR)
			return TRUE;
	}
	else
	{
		D3DXVECTOR3 vcN;
		FLOAT		fN;

		D3DXVec3Cross(&vcN, &vcL, &vcT);

		fN = D3DXVec3LengthSq(&vcN);

		if(fN < fR*fR)
			return TRUE;
	}

	return FALSE;
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

	m_pLine[0].p = D3DXVECTOR3(  100,  300,  300);
	m_pLine[1].p = D3DXVECTOR3(  200, -300,  200);

	m_fR = 100;

	m_vcSphere = D3DXVECTOR3(50, 100, 150);

	D3DXCreateSphere(m_pDev, m_fR, 20, 20, &m_pMsh, 0);

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
		m_pLine[0].p.z += 1;
		m_pLine[1].p.z += 1;
	}

	if(pInput->KeyState(VK_DOWN))
	{
		m_pLine[0].p.z -= 1;
		m_pLine[1].p.z -= 1;
	}

	if(pInput->KeyState(VK_HOME))
	{
		m_pLine[0].p.y += 1;
		m_pLine[1].p.y += 1;
	}

	if(pInput->KeyState(VK_END))
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

	D3DXVECTOR3 pLine[2];

	pLine[0] = m_pLine[0].p;
	pLine[1] = m_pLine[1].p;

//	for(int i=0; i<20000; ++i)
	{
	m_bColl = LcMath_CollisionLineToSphere(pLine, &m_vcSphere, m_fR, &m_vcPick);
	}

	return 0;
}

void CMcCollision::Render()
{
	m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pDev->SetRenderState( D3DRS_LIGHTING,  FALSE);
	m_pDev->SetRenderState( D3DRS_ALPHABLENDENABLE,  FALSE);
	m_pDev->SetRenderState( D3DRS_ALPHATESTENABLE,  FALSE);

	m_pDev->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);

	if(m_bColl)
		m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pDev->SetTexture(0, 0);
	m_pDev->SetFVF(VtxD::FVF);

	m_pDev->DrawPrimitiveUP(D3DPT_LINELIST, 1, m_pLine, sizeof(VtxD));

	D3DLIGHT9 Lgt;
	D3DMATERIAL9	mtl;
	D3DUtil_InitLight( Lgt, D3DLIGHT_DIRECTIONAL, -1.0f, -1.0f, 2.0f );
	D3DUtil_InitMaterial(mtl,1.0f, 0.0f,0.0f);

	m_pDev->SetLight( 0, &Lgt );
	m_pDev->LightEnable( 0, TRUE );
	m_pDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pDev->SetRenderState( D3DRS_AMBIENT, 0x000F0F0F );

	m_pDev->SetMaterial( &mtl );

	D3DXMATRIX mtW;
	D3DXMatrixIdentity(&mtW);

	mtW._41 = m_vcSphere.x;
	mtW._42 = m_vcSphere.y;
	mtW._43 = m_vcSphere.z;

	m_pDev->SetTransform(D3DTS_WORLD,&mtW);
	m_pMsh->DrawSubset(0);

	D3DXMatrixIdentity(&mtW);
	m_pDev->SetTransform(D3DTS_WORLD,&mtW);

	m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
}

