// Implementation of the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


INT LcMath_IntersectTri(D3DXVECTOR3* pOut			// 충돌 위치
						, const D3DXVECTOR3* V0		// 삼각형 꼭지점
						, const D3DXVECTOR3* V1		// 삼각형 꼭지점
						, const D3DXVECTOR3* V2		// 삼각형 꼭지점
						, const D3DXVECTOR3* L0		// 직선의 시작 위치
						, const D3DXVECTOR3* L		// 직선의 방향 벡터
						, FLOAT* u = NULL			// α 출력(선택)
						, FLOAT* v = NULL			// β 출력(선택)
						)
{
	int hr = -1;	// 충돌을 실패로 설정

	// 임시 벡터들을 선언한다.
	D3DXVECTOR3	A;
	D3DXVECTOR3	B;
	D3DXVECTOR3	N;
	D3DXVECTOR3	X;

	// 임시 변수들을 선언한다.
	FLOAT D, s, m;
	FLOAT aa, bb, ab, ax, bx, m0, m1, m2;

	// 위의 알고리듬 1번부터 구한다.
	A = *V1 - *V0;
	B = *V2 - *V0;
	D3DXVec3Cross(&N, &A, &B);

	D = D3DXVec3Dot(&N, V0);
	s = D3DXVec3Dot(&N, L0);
	m = D3DXVec3Dot(&N, L);

	// 충돌 점을 구한다.
	X = *L0 + (D-s)/m * (*L);

	if(pOut)	*pOut = X;

	X -= *V0;
	// 행렬식에 필요한 변수들을 계산한다.
	aa = D3DXVec3Dot(&A, &A);
	bb = D3DXVec3Dot(&B, &B);
	ab = D3DXVec3Dot(&A, &B);
	ax = D3DXVec3Dot(&A, &X);
	bx = D3DXVec3Dot(&B, &X);

	// 행렬식을 계산한다.
	m0 = aa * bb - ab * ab;
	m1 = ax * bb - ab * bx;
	m2 = aa * bx - ab * ax;

	if( m1>= 0 && m2 >= 0 && m0>=(m1 + m2))
		hr = 0;	// 충돌

	if(u)	*u = m1/m0;
	if(v)	*v = m2/m0;

	return hr;
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

	FLOAT u, v;
//	for(int i=0; i<100000;++i)
		m_bColl = LcMath_IntersectTri(&m_vcPick, &pTri[0], &pTri[1], &pTri[2], &pLine.p, &pLine.t, &u, &v);

		
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

	if(SUCCEEDED(m_bColl))
		m_pDev->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME);


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

	if(SUCCEEDED(m_bColl))
		m_pDev->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID);
}

