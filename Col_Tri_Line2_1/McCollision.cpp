// Implementation of the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


INT LcMath_IntersectTri2(D3DXVECTOR3* pOut			// 충돌 위치
						, const D3DXVECTOR3* V0		// 삼각형 꼭지점
						, const D3DXVECTOR3* V1		// 삼각형 꼭지점
						, const D3DXVECTOR3* V2		// 삼각형 꼭지점
						, const D3DXVECTOR3* L0		// 직선의 시작 위치
						, const D3DXVECTOR3* L		// 직선의 방향 벡터
						, FLOAT* pU=NULL			// Barycentric Hit Coordinates
						, FLOAT* pV=NULL			// Barycentric Hit Coordinates
						, FLOAT* pDist=NULL)		// 충돌점까지 거리
{
//
// 삼각형 내부의 충돌 지점을 X라 하면
// X = Pos + k * Lay Dir
//   = Pos + T + u * A  + v * B, (단 T = V0 - Pos)
//
// 수식을 정리하면
// k * D = -T + u * A + v * B		--------(1)
//
// 이 때 3개의 수직 벡터를 구한다.
// Nda = D X A	( D, A 수직 벡터)
// Ndb = D X B	( D, B 수직 벡터)
// Nab = A X B	( A, B 수직 벡터)
//
// (1)식의 양변에 Ndb 벡터를 Dot 연산하면 Ndb가 D, B에 수직이므로 D, B 벡터 부분은 0이 된다.
// k * D ㆍ Ndb = -T ㆍ Ndb  + u * A ㆍ Ndb  +  v * Bㆍ Ndb
//           0  = -T ㆍ Ndb  + u * A ㆍ Ndb  +  0
// 이렇게 u가 구해진다.
// u = ( T ㆍ Ndb)/(A ㆍ Ndb)
//
// 마찬가지 방법으로 Nda, Nab 차례로 적용하면 v, k를 구할 수 있다.
// v = ( T ㆍ Nda)/(B ㆍ Nda)
// k =-( T ㆍ Nab)/(D ㆍ Nab)
//
// 벡터는 다음과 같은 성질이 있다.
// det = Aㆍ(D X B) = Bㆍ(A X D) = - Bㆍ(D X A) = Dㆍ(B X A) = -Dㆍ(A X B)
//
// 따라서 B ㆍ Nda와 D ㆍ Nab는 A ㆍ Ndb 와 같다.
// 수식을 다시 정리 하면 다음과 같이 된다.
//
// u = T ㆍ Ndb/(A ㆍ Ndb)						--------(2)
// v = T ㆍ Nda/(B ㆍ Nda) = -T ㆍ Nda/det		--------(3)
// k =-T ㆍ Nab/(D ㆍ Nab) =  T ㆍ Nab/det		--------(4)
//
// u (0, 1), v(0, 1), u+v (0,1) 범이 안에 있으면 삼각형과 충돌이다.
//
// 프로그램을 작성할 때는 한 줄이라도 더 줄여야 하므로 나눗셈 연산은 마지막에 한다.
// det 값을 먼저 계산한다.
// det가 0 근처 이면 나눗셈이 불가능 하므로 충돌이 아니다.
// 위의 수식은 det의 부호와 상관없이 잘 동작한다.
// 그러나 나눗셈을 나중에 하기 위해서 det를 먼저 계산 하는 경우에 u와 v의 경계 판단이 안된다.
// 따라서 det가 음수이면 양수로 바꾼다. 이 경우에 (2), (3), (4)에 영향을 주므로
// 똑같이 T도 음수로 바꾼다.


	// 1. A, B, D, T를 정한다.
	D3DXVECTOR3 A = *V1 - *V0;
	D3DXVECTOR3 B = *V2 - *V0;
	D3DXVECTOR3 D = *L;
	D3DXVECTOR3 T = *L0 - *V0;
	D3DXVECTOR3 Nab;		// Nab = A X B
	D3DXVECTOR3 Nda;		// Nda = D X A
	D3DXVECTOR3 Ndb;		// Ndb = D X B

	FLOAT	k, u, v, det;
	D3DXVECTOR3 P;

//	D3DXVec3Cross(&Ndb, &D, &B);
//	u = D3DXVec3Dot(&T, &Ndb)/D3DXVec3Dot(&A, &Ndb);
//
//	if(u<0 || u>1)
//		return -1;
//
//	D3DXVec3Cross(&Nda, &D, &A);
//	v = D3DXVec3Dot(&T, &Nda)/D3DXVec3Dot(&B, &Nda);
//
//	if(v<0 || (u+v)>1)
//		return -1;
//
//	D3DXVec3Cross(&Nab, &A, &B);
//	k = - D3DXVec3Dot(&T, &Nab)/D3DXVec3Dot(&D, &Nab);
//
//	*pU = u;
//	*pV = v;
//	*pDist = k;

	
	// 2. D, B 두 벡터에 수직인 벡터를 구한다.
	D3DXVec3Cross(&Ndb, &D, &B);
	

	// 3. Determinant를 구한다. det가 음수면 양수로 바꾼다. 또한 T의 방향도 바꾼다.
	det= D3DXVec3Dot(&A, &Ndb);	// det = Aㆍ(D X B)
	if(det<0)
	{
		det = -det;
		T = -T;
	}

	// Determinant 0 근처면 나눗셈이 안되므로 충돌이 안된 것으로 판정하고 나간다.
	if(det < 0.00001f)
		return -1;


	// 4. u를 계산한다.
	u = D3DXVec3Dot(&T, &Ndb);
	
	// u의 범위는 (0, 1) 이다. 나눗셈을 하지 않았으므로 det와 비교한다.
	if(u<0 || u>det)
		return -1;


	// 5. Nda, v를 계산한다.
	D3DXVec3Cross(&Nda, &D, &A);
	v = -D3DXVec3Dot(&T, &Nda);

	// u+v의 범위는 (0, 1) 이다. v도 나눗셈을 하지 않았으므로 det와 비교한다.
	if(v<0 || (u+v)>det)
		return -1;


	// 6. 충돌 결과를 계산하기 위해 det를 역수 취하고 나머지 숫자에 곱한다.
	det = 1/det;
	u*= det;
	v*= det;

	if(pU)	*pU = u;
	if(pV)	*pV = v;


	// 7. 거리를 계산한다.
	if(pDist)
	{
		D3DXVec3Cross(&Nab, &A, &B);
		k = D3DXVec3Dot(&T, &Nab);
		k *=det;
		*pDist = k;
	}

	// 8. 충돌 지점을 구한다.
	if(pOut)
	{
		P = u * A + v * B;
		P +=*V0;
		*pOut = P;
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

	FLOAT u, v;

//	for(int i=0; i<100000;++i)
		m_bColl = LcMath_IntersectTri2(&m_vcPick, &pTri[0], &pTri[1], &pTri[2], &pLine.p, &pLine.t, &u, &v);
	
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

