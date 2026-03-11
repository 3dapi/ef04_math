// Implementation of the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


FLOAT	LcMath_LineToLineDistance(D3DXVECTOR3* pOut		// Normal vector
								  , const LcLine* pV1	// Input Line1
								  , const LcLine* pV2	// Input Line1
								  )
{
	D3DXVECTOR3 vcN;
	D3DXVECTOR3 L1 = pV1->t;
	D3DXVECTOR3 L2 = pV2->t;
	D3DXVECTOR3	vcTemp=pV1->p - pV2->p;

	FLOAT	fD =0.f;

	D3DXVec3Cross(&vcN, &L1, &L2);
	D3DXVec3Normalize(&vcN, &vcN);

	fD = D3DXVec3Dot(&vcN, &vcTemp);

	*pOut = vcN;

	return fD;
}

INT LcMath_LineToLineIntersection(D3DXVECTOR3* pOut		// Intersection point
								  , const LcLine* pV1	// Input Line1
								  , const LcLine* pV2	// Input Line1
								  )
{
	D3DXVECTOR3 vcN;
	D3DXVECTOR3 L1 = pV1->t;
	D3DXVECTOR3 L2 = pV2->t;
	D3DXVECTOR3 P1 = pV1->p;
	D3DXVECTOR3 P3 = pV2->p;
	D3DXVECTOR3 L3 = P3 - P1;

	FLOAT	fD = LcMath_LineToLineDistance(&vcN, pV1, pV2);

	FLOAT	DotL12 = D3DXVec3Dot(&L1, &L2);
	FLOAT	DotL13 = D3DXVec3Dot(&L1, &L3);
	FLOAT	DotL23 = D3DXVec3Dot(&L2, &L3);

	FLOAT	fDet1 = -1 + DotL12 * DotL12;
	FLOAT	fDet2 = DotL23 - DotL12 * DotL13;
	FLOAT	fBeta = 0.f;


	// 충돌
	if(fabsf(fD)<0.0001f)
	{
		// 부정(정할 수 없다.)
		if(fabsf(fDet2)<0.0001f)
			return -1;

		fBeta = fDet2/ fDet1;
		pOut[0] = P3 + fBeta * L2;
		pOut[1] = pOut[0];


		// 충돌한 점의 개수를 돌려준다.
		return 1;
	}


	// 충돌이 아닌데 평행인 경우
	// 불능(구할 수 없다.)
	if( fabsf(DotL12)>0.9999f)
		return -2;


	P1 = P1 - fD * vcN;
	L3 = P3 - P1;

	DotL13 = D3DXVec3Dot(&L1, &L3);
	DotL23 = D3DXVec3Dot(&L2, &L3);

	fDet2 = DotL23 - DotL12 * DotL13;

	fBeta = fDet2/ fDet1;
	pOut[0] = P3 + fBeta * L2;
	pOut[1] = pOut[0] + fD * vcN;

	// 충돌한 점의 개수를 돌려준다.
	return 2;
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

	m_pLine1[0].p = D3DXVECTOR3(  100,  300,  300);
	m_pLine1[1].p = D3DXVECTOR3(  200, -300,  200);

	m_pLine2[0].p = D3DXVECTOR3(  -1000,  -100,  -3000);
	m_pLine2[1].p = D3DXVECTOR3(   1000,   400,   3000);
	m_pLine2[0].d = 0xFFFFFF00;
	m_pLine2[1].d = 0xFFFFFF00;

	m_fR = 5;

	m_vcSphere[0] = D3DXVECTOR3(50, 100, 150);
	m_vcSphere[1] = D3DXVECTOR3(50, 100, 150);

	D3DXCreateSphere(m_pDev, m_fR, 10, 10, &m_pMsh, 0);

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
		m_pLine1[0].p.z += 1;
		m_pLine1[1].p.z += 1;
	}

	if(pInput->KeyState(VK_DOWN))
	{
		m_pLine1[0].p.z -= 1;
		m_pLine1[1].p.z -= 1;
	}

	if(pInput->KeyState(VK_HOME))
	{
		m_pLine1[0].p.y += 1;
		m_pLine1[1].p.y += 1;
	}

	if(pInput->KeyState(VK_END))
	{
		m_pLine1[0].p.y -= 1;
		m_pLine1[1].p.y -= 1;
	}

	if(pInput->KeyState(VK_LEFT))
	{
		m_pLine1[0].p.x -= 1;
		m_pLine1[1].p.x -= 1;
	}

	if(pInput->KeyState(VK_RIGHT))
	{
		m_pLine1[0].p.x += 1;
		m_pLine1[1].p.x += 1;
	}


	D3DXVECTOR3	vcT[2];

	vcT[0] = m_pLine1[0].p - m_pLine1[1].p;
	vcT[1] = m_pLine2[1].p - m_pLine2[0].p;

	LcLine	Line1(m_pLine1[0].p, vcT[0]);
	LcLine	Line2(m_pLine2[0].p, vcT[1]);

//	for(int i=0; i<5000; ++i)
	{
		D3DXVec3Normalize(&Line1.t, &Line1.t);
		D3DXVec3Normalize(&Line2.t, &Line2.t);
		m_bColl = LcMath_LineToLineIntersection(m_vcSphere, &Line1, &Line2);
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


	m_pDev->SetTexture(0, 0);
	m_pDev->SetFVF(VtxD::FVF);

	m_pDev->DrawPrimitiveUP(D3DPT_LINELIST, 1, m_pLine1, sizeof(VtxD));
	m_pDev->DrawPrimitiveUP(D3DPT_LINELIST, 1, m_pLine2, sizeof(VtxD));

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

	mtW._41 = m_vcSphere[0].x;
	mtW._42 = m_vcSphere[0].y;
	mtW._43 = m_vcSphere[0].z;

	m_pDev->SetTransform(D3DTS_WORLD,&mtW);
	m_pMsh->DrawSubset(0);



	D3DUtil_InitMaterial(mtl,1.0f, 0.0f,1.0f);
	m_pDev->SetMaterial( &mtl );

	mtW._41 = m_vcSphere[1].x;
	mtW._42 = m_vcSphere[1].y;
	mtW._43 = m_vcSphere[1].z;

	m_pDev->SetTransform(D3DTS_WORLD,&mtW);
	m_pMsh->DrawSubset(0);


	D3DXMatrixIdentity(&mtW);
	m_pDev->SetTransform(D3DTS_WORLD,&mtW);

	m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
}

