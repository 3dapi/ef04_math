// Implementation of the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


FLOAT LcMath_LineToLineDistance(FLOAT* pSinTheta		// Sin(θ)
								, D3DXVECTOR3* pOut		// Normal vector
								, const LcLine* pV1		// Input Line1
								, const LcLine* pV2		// Input Line2
								)
{
	D3DXVECTOR3	vcN;
	D3DXVECTOR3	L1 = pV1->t;
	D3DXVECTOR3	L2 = pV2->t;
	D3DXVECTOR3	L3 = pV1->p - pV2->p;

	FLOAT	fD = 0.f;
	FLOAT	fL = 0.f;

	D3DXVec3Cross(&vcN, &L1, &L2);

	fL = D3DXVec3Length(&vcN);

	if(pSinTheta)
		*pSinTheta = fL;

	fL = 1.f/fL;

	vcN.x *= fL;
	vcN.y *= fL;
	vcN.z *= fL;

	fD = D3DXVec3Dot(&vcN, &L3);

	*pOut = vcN;

	return fD;
}


INT LcMath_LineToLineIntersection(FLOAT* pSinTheta			// Sin(θ)
								, FLOAT* pDst				// Distance
								, D3DXVECTOR3* pOut			// Intersection point
								, const LcLine* pV1			// Input Line1
								, const LcLine* pV2			// Input Line2
								  )
{
	D3DXVECTOR3	vcN;
	D3DXVECTOR3	L1 = pV1->t;
	D3DXVECTOR3	L2 = pV2->t;
	D3DXVECTOR3	P1 = pV1->p;
	D3DXVECTOR3	P3 = pV2->p;
	D3DXVECTOR3	L3 = P3 - P1;

	FLOAT	fD		= 0.f;
	FLOAT	DotL12 = D3DXVec3Dot(&L1, &L2);
	FLOAT	DotL13 = D3DXVec3Dot(&L1, &L3);
	FLOAT	DotL23 = D3DXVec3Dot(&L2, &L3);

	FLOAT	fDet1 = -1 + DotL12 * DotL12;
	FLOAT	fDet2 = DotL23 - DotL12 * DotL13;
	FLOAT	fBeta = 0.f;

	// 평행이다.
	if( fabsf(DotL12)>0.9999f)
	{
		D3DXVECTOR3 vcT;

		D3DXVec3Cross(&vcT, &L1, &L3);
		fD = D3DXVec3LengthSq(&vcT);

		// 겹쳐 있다면
		// 부정( 정할 수 없다.)
		if(fD<0.0001f)
			return -1;

		// 겹쳐 있지 않다면
		// 불능(구할 수 없다.)
		return -2;
	}


	fD = LcMath_LineToLineDistance(pSinTheta, &vcN, pV1, pV2);

	if(pDst)
		*pDst = fD;


	// 충돌
	if(fabsf(fD)<0.0001f)
	{
		fBeta = fDet2/ fDet1;
		pOut[0] = P3 + fBeta * L2;
		pOut[1] = pOut[0];

		// 충돌한 점의 개수를 돌려준다.
		return 1;
	}


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


INT LcMath_LineToCylinderIntersection(D3DXVECTOR3* pOut			// Intersection point
									, const LcLine* pV1			// Input Line
									, const LnCylinder* pV2		// Input Cylinder
									  )
{
	INT iInsc=0;

	D3DXVECTOR3 vcInsc[2];			// 실린더 중심선과 직선이 교차하는 지점
	D3DXVECTOR3	L1 = pV1->t;
	D3DXVECTOR3	L2 = pV2->t;

	FLOAT	fR = pV2->r;			// 실린더의 반지름
	FLOAT	fD = 0.f;				// 실린더와 직선의 거리
	FLOAT	fK = 0.f;
	FLOAT	fSinTheta = 0.f;

	iInsc = LcMath_LineToLineIntersection(&fSinTheta, &fD, vcInsc, pV1, (LcLine*)pV2);

	// 부정이나 불능 두 가지 중 하나
	if(FAILED(iInsc))
	{
		// 원통의 반경과 비교
		// 직선이 원통 안에 완전히 존재
		if(fD <= pV2->r)
			return 0;	// 충돌 점을 정할 수가 없음

		// 직선이 원통 밖에 존재
		else
			return -1;
	}

	// 직선이 원통 밖에 존재
	if(fabsf(fD)>=fR)
		return -1;


	// 충돌한 두 점의 위치를 구하기 위해 K 값을 결정
	fK = fabsf(fSinTheta);
	fK = sqrtf(fR*fR - fD*fD)/fK;

	// vcInsc[0]은 실린더 쪽 최 근접 점
	// vcInsc[1]은 직선 쪽  최 근접 점
	pOut[0] = vcInsc[1] - fK * L1;
	pOut[1] = vcInsc[1] + fK * L1;

	return 2;
}


CMcCollision::CMcCollision()
{
	m_pDev	= NULL;

	m_bColl = FALSE;
	m_pMsh	= NULL;
	m_pCyl	= NULL;
}

CMcCollision::~CMcCollision()
{
	Destroy();
}


INT CMcCollision::Create(LPDIRECT3DDEVICE9 pDev)
{
	m_pDev	= pDev;

	FLOAT fR = 5;

	m_vcSphere[0] = D3DXVECTOR3(50, 100, 150);
	m_vcSphere[1] = D3DXVECTOR3(50, 100, 150);
	D3DXCreateSphere(m_pDev, fR, 10, 10, &m_pMsh, 0);


	m_pTstL[0].p = D3DXVECTOR3(  -800, 100, -2300);
	m_pTstL[1].p = D3DXVECTOR3(   400, 200,   1200);


	m_CylnO[0].p = D3DXVECTOR3(  -500,  -100,  -1000);
	m_CylnO[1].p = D3DXVECTOR3(   500,   400,   1000);
	m_CylnO[0].d = 0xFFFF00FF;
	m_CylnO[1].d = 0xFFFF00FF;

	m_Cyln = LnCylinder(m_CylnO[0].p, m_CylnO[1].p - m_CylnO[0].p, 50.f, 5000.f);
	D3DXVec3Normalize(&m_Cyln.t, &m_Cyln.t);


	D3DXCreateCylinder(	m_pDev
		, m_Cyln.r
		, m_Cyln.r
		, m_Cyln.h/4.f
		, 40
		, 100
		, &m_pCyl
		, NULL);

	D3DXMatrixLookAtLH(&m_mtCyl, &(m_CylnO[0].p), &(m_CylnO[1].p), &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixInverse(&m_mtCyl, NULL, &m_mtCyl);

	D3DXVECTOR3	vcCenter= (m_CylnO[0].p + m_CylnO[1].p)/2.f;
	m_mtCyl._41 = vcCenter.x;
	m_mtCyl._42 = vcCenter.y;
	m_mtCyl._43 = vcCenter.z;

	return 0;
}


void CMcCollision::Destroy()
{
	SAFE_RELEASE(	m_pMsh	);
	SAFE_RELEASE(	m_pCyl	);
}


INT	CMcCollision::FrameMove()
{
	CMcInput*	pInput = g_pApp->m_pInput;

	if(pInput->KeyState(VK_UP))
	{
		m_pTstL[0].p.z += 1;
		m_pTstL[1].p.z += 1;
	}

	if(pInput->KeyState(VK_DOWN))
	{
		m_pTstL[0].p.z -= 1;
		m_pTstL[1].p.z -= 1;
	}

	if(pInput->KeyState(VK_HOME))
	{
		m_pTstL[0].p.y += 1;
		m_pTstL[1].p.y += 1;
	}

	if(pInput->KeyState(VK_END))
	{
		m_pTstL[0].p.y -= 1;
		m_pTstL[1].p.y -= 1;
	}

	if(pInput->KeyState(VK_LEFT))
	{
		m_pTstL[0].p.x -= 1;
		m_pTstL[1].p.x -= 1;
	}

	if(pInput->KeyState(VK_RIGHT))
	{
		m_pTstL[0].p.x += 1;
		m_pTstL[1].p.x += 1;
	}


	D3DXVECTOR3	vcT[2];

	vcT[0] = m_pTstL[0].p - m_pTstL[1].p;
	vcT[1] = m_CylnO[1].p - m_CylnO[0].p;

	LcLine	Line1(m_pTstL[0].p, vcT[0]);
	LnCylinder	Line2(m_CylnO[0].p, vcT[1], 50.f, 10000.f);

	for(int i=0; i<500; ++i)
	{
		D3DXVec3Normalize(&Line1.t, &Line1.t);
		D3DXVec3Normalize(&Line2.t, &Line2.t);
		m_bColl = LcMath_LineToCylinderIntersection(m_vcSphere, &Line1, &Line2);
	}

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

	m_pDev->SetTexture(0, 0);
	m_pDev->SetFVF(VtxD::FVF);

	m_pDev->DrawPrimitiveUP(D3DPT_LINELIST, 1, m_pTstL, sizeof(VtxD));
	m_pDev->DrawPrimitiveUP(D3DPT_LINELIST, 1, m_CylnO, sizeof(VtxD));

	D3DUtil_InitLight( Lgt, D3DLIGHT_DIRECTIONAL, -1.0f, -1.0f, 2.0f );
	m_pDev->SetLight( 0, &Lgt );
	m_pDev->LightEnable( 0, TRUE );
	m_pDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pDev->SetRenderState( D3DRS_AMBIENT, 0x000F0F0F );


	if(SUCCEEDED(m_bColl))
	{
		D3DUtil_InitMaterial(mtl,1.0f, 0.0f,0.0f);
		m_pDev->SetMaterial( &mtl );

		D3DXMatrixIdentity(&mtW);

		mtW._41 = m_vcSphere[0].x;
		mtW._42 = m_vcSphere[0].y;
		mtW._43 = m_vcSphere[0].z;

		m_pDev->SetTransform(D3DTS_WORLD,&mtW);
		m_pMsh->DrawSubset(0);


		D3DUtil_InitMaterial(mtl,0.0f, 1.0f,1.0f);
		m_pDev->SetMaterial( &mtl );

		mtW._41 = m_vcSphere[1].x;
		mtW._42 = m_vcSphere[1].y;
		mtW._43 = m_vcSphere[1].z;

		m_pDev->SetTransform(D3DTS_WORLD,&mtW);
		m_pMsh->DrawSubset(0);

		m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}



	D3DUtil_InitMaterial(mtl,1.0f, 1.0f,0.0f);
	m_pDev->SetMaterial( &mtl );

	m_pDev->SetTransform(D3DTS_WORLD,&m_mtCyl);
	m_pCyl->DrawSubset(0);



	D3DXMatrixIdentity(&mtW);
	m_pDev->SetTransform(D3DTS_WORLD,&mtW);

	m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
}

