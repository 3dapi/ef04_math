// Implementation of the CMcPicking class.
//
////////////////////////////////////////////////////////////////////////////////


#include <time.h>

#include "_StdAfx.h"


// 정규화 된 직선에 대한 충돌
BOOL LcMath_CollisionLineToSphere(D3DXVECTOR3*			vcOut		// 직선에서 구 중심까지 가장 가까운 지점
								  , const D3DXVECTOR3*	pLineBegin	// 직선의 시작점
								  , const D3DXVECTOR3*	pLineDir	// 직선의 방향
								  , D3DXVECTOR3*		pCenter		// 충돌한 구의 중심
								  , FLOAT				fRadius		// 구의 반지름
								  )
{
	D3DXVECTOR3 vcL = *pLineDir;
	D3DXVECTOR3 vcT = *pCenter - *pLineBegin;

	// 외부에서 정규화 하면 이부분에 대한 부하를 줄일 수 있다.
	//D3DXVec3Normalize(&vcL, &vcL);

	if(vcOut)
	{
		FLOAT		fT;
		FLOAT		fC;

		fC = D3DXVec3LengthSq(&vcT);
		fT = D3DXVec3Dot(&vcL, &vcT);

		*vcOut = *pLineBegin + fT * vcL;
		fC -= fT * fT;

		if(fC < fRadius*fRadius)
			return TRUE;
	}
	else
	{
		D3DXVECTOR3 vcN;
		FLOAT		fN;

		D3DXVec3Cross(&vcN, &vcL, &vcT);

		fN = D3DXVec3LengthSq(&vcN);

		if(fN < fRadius*fRadius)
			return TRUE;
	}

	return FALSE;
}






CMcPicking::CMcPicking()
{
	m_pDev	= NULL;

	srand( (unsigned)time(NULL));
}

CMcPicking::~CMcPicking()
{
	Destroy();
}


INT CMcPicking::Create(LPDIRECT3DDEVICE9 pDev)
{
	m_pDev	= pDev;


	for(int i=0; i<MAX_OBJECT; ++i)
	{
		FLOAT		fRadius = 10.f + rand()%90;
		LPD3DXMESH	pMesh;


		m_pObj[i].fRadius = fRadius;
		D3DXCreateSphere(m_pDev, fRadius, 15, 15, &pMesh, 0);

		m_pObj[i].pMsh = pMesh;

		m_pObj[i].bWire=FALSE;

		FLOAT	x = 8.f * (rand()%100);
		FLOAT	y = 8.f * (rand()%100);
		FLOAT	z = 8.f * (rand()%100);

		m_pObj[i].vcPos= D3DXVECTOR3(x, y, z);
		D3DXMatrixTranslation(&m_pObj[i].mtWld, x, y, z);

	}

	return 0;
}


void CMcPicking::Destroy()
{
	for(int i=0; i<MAX_OBJECT; ++i)
	{
		LPD3DXMESH	pMesh = m_pObj[i].pMsh;
		SAFE_RELEASE(	pMesh	);

		m_pObj[i].pMsh = NULL;
	}
}


INT	CMcPicking::FrameMove()
{
	CMcInput*	pInput = g_pApp->m_pInput;


	// 0. 디바이스에서 윈도우 핸들 가져오기
	D3DDEVICE_CREATION_PARAMETERS	Params={0};
	m_pDev->GetCreationParameters(&Params);
	
	D3DXMATRIX		mtViw;
	D3DXMATRIX		mtPrj;
	D3DXMATRIX		mtVpt;
	D3DVIEWPORT9	vp;

	// 1. 뷰 행렬, 투영 행렬, 뷰포트를 가져온다.
	m_pDev->GetTransform(D3DTS_VIEW, &mtViw);
	m_pDev->GetTransform(D3DTS_PROJECTION, &mtPrj);
	m_pDev->GetViewport(&vp);

	// 2. 마우스의 위치를 가져온다.
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(Params.hFocusWindow, &mouse);
	D3DXVECTOR3	vcScn( FLOAT(mouse.x), float(mouse.y), 0);

	// 3. 마우스의 위치를 월드 공간으로 바꾼다.
	D3DXVec3Unproject(&vcScn, &vcScn, &vp, &mtPrj, &mtViw, NULL);

	// 4. 뷰행렬의 역행렬에서 카메라의 위치를 구한다.
	D3DXMatrixInverse(&mtViw, NULL, &mtViw);

	// 5. 직선의 시작점(카메라 위치), 방향을 정한다.
	D3DXVECTOR3 vcLineBegin	= D3DXVECTOR3(mtViw._41, mtViw._42, mtViw._43);
	D3DXVECTOR3 vcLineDir	= vcScn - vcLineBegin;

	// 6. 직선의 방향은 정규화한다.
	D3DXVec3Normalize(&vcLineDir, &vcLineDir);


	for(int i=0; i<MAX_OBJECT; ++i)
	{
		float		fRadius	= m_pObj[i].fRadius;
		D3DXVECTOR3	vcPos	= m_pObj[i].vcPos;

		// 충돌이 성공하면 Wire로 그릴 수 있도록 한다.
		if(TRUE == LcMath_CollisionLineToSphere(NULL, &vcLineBegin, &vcLineDir, &vcPos, fRadius))
			m_pObj[i].bWire = TRUE;
		else
			m_pObj[i].bWire = FALSE;
	}

	return 0;
}

void CMcPicking::Render()
{
	m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pDev->SetRenderState( D3DRS_LIGHTING,  FALSE);
	m_pDev->SetRenderState( D3DRS_ALPHABLENDENABLE,  FALSE);
	m_pDev->SetRenderState( D3DRS_ALPHATESTENABLE,  FALSE);

	m_pDev->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);

	m_pDev->SetTexture(0, 0);




	D3DLIGHT9		Lgt;
	D3DMATERIAL9	mtl1;
	D3DMATERIAL9	mtl2;
	D3DUtil_InitLight( Lgt, D3DLIGHT_DIRECTIONAL, -1.0f, -1.0f, 2.0f );

	D3DUtil_InitMaterial(mtl2,1.0f, 0.0f,0.0f);
	D3DUtil_InitMaterial(mtl1,1.0f, 1.0f,0.0f);

	m_pDev->SetLight( 0, &Lgt );
	m_pDev->LightEnable( 0, TRUE );
	m_pDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pDev->SetRenderState( D3DRS_AMBIENT, 0x000F0F0F );

	for(int i=0; i<MAX_OBJECT; ++i)
	{
		LPD3DXMESH	pMesh = m_pObj[i].pMsh;

		if(m_pObj[i].bWire)
		{
			m_pDev->SetMaterial( &mtl1 );
			m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
		else
		{
			m_pDev->SetMaterial( &mtl2 );
			m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}


		m_pDev->SetTransform(D3DTS_WORLD,&m_pObj[i].mtWld);
		pMesh->DrawSubset(0);
	}

	D3DXMATRIX mtW;
	D3DXMatrixIdentity(&mtW);
	m_pDev->SetTransform(D3DTS_WORLD,&mtW);

	m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
}

