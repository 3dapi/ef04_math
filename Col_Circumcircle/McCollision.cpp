// Implementation of the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"





FLOAT LcMath_Circumcircle(D3DXVECTOR3* vcOut, D3DXVECTOR3* pTri)
{
	D3DXVECTOR3	p1, p2, p3;
	D3DXVECTOR3	t1, t2, t3;
	D3DXVECTOR3 n, n1, n2;
	D3DXVECTOR3	q1, q2, q3;
	D3DXVECTOR3	s1;

	FLOAT		a1=0.f;
	FLOAT		fR=0.f;
	D3DXVECTOR3	vcT;

	FLOAT		fD=0.f;

	p1 = pTri[0];
	p2 = pTri[1];
	p3 = pTri[2];

	t1 = (p2 - p1) * .5f;
	t2 = (p3 - p2) * .5f;
	t3 = (p1 - p3) * .5f;

	D3DXVec3Cross(&n, &t1, &t2);
	n *=-1.f;
	D3DXVec3Normalize(&n, &n);

	D3DXVec3Cross(&n1, &n, &t1);
	D3DXVec3Cross(&n2, &n, &t2);

	q1 = p1 + t1;
	q2 = p2 + t2;
	q3 = p3 + t3;

	s1 = q2 - q1;

	FLOAT fN1 = D3DXVec3LengthSq(&n1);
	FLOAT fN2 = D3DXVec3LengthSq(&n2);

	FLOAT fN12 = D3DXVec3Dot(&n1, &n2);

	fD	= fN12 * fN12 - fN1 * fN2;



	FLOAT fN1S1 = D3DXVec3Dot(&n1, &s1);
	FLOAT fN2S1 = D3DXVec3Dot(&n2, &s1);

	a1 = fN12 * fN2S1 - fN2 * fN1S1;
	a1 /= fD;

	vcT		= t1 + a1 * n1;
	*vcOut = p1 + vcT;

	fR = D3DXVec3Length(&vcT);

	return fR;
}

CMcCollision::CMcCollision()
{
	m_pMsh	= NULL;
}

CMcCollision::~CMcCollision()
{
	Destroy();
}


INT CMcCollision::Create(LPDIRECT3DDEVICE9 pDev)
{
	m_pDev	= pDev;

	m_pTri[0]	= VtxD(   0,  500,    0, 0xFFFF7777);
	m_pTri[1]	= VtxD(1000, -500,    0, 0xFF77FF77);
	m_pTri[2]	= VtxD( 500,    0, 1000, 0xFF7777FF);

	D3DXCreateSphere(m_pDev, 25, 32, 32, &m_pMsh, 0);

	return 0;
}


void CMcCollision::Destroy()
{
	SAFE_RELEASE(m_pMsh);
}


INT	CMcCollision::FrameMove()
{
	CMcInput*	pInput = g_pApp->m_pInput;

	if(pInput->KeyState(VK_UP))
	{
		m_pTri[0].p.z += 1;
		m_pTri[1].p.z += 1;
	}

	if(pInput->KeyState(VK_DOWN))
	{
		m_pTri[0].p.z -= 1;
		m_pTri[1].p.z -= 1;
	}

	if(pInput->KeyState(VK_HOME))
	{
		m_pTri[0].p.y += 1;
		m_pTri[1].p.y += 1;
	}

	if(pInput->KeyState(VK_END))
	{
		m_pTri[0].p.y -= 1;
		m_pTri[1].p.y -= 1;
	}

	if(pInput->KeyState(VK_LEFT))
	{
		m_pTri[0].p.x -= 1;
		m_pTri[1].p.x -= 1;
	}

	if(pInput->KeyState(VK_RIGHT))
	{
		m_pTri[0].p.x += 1;
		m_pTri[1].p.x += 1;
	}


	D3DXVECTOR3 pTri[3];
	pTri[0] = m_pTri[0].p;
	pTri[1] = m_pTri[1].p;
	pTri[2] = m_pTri[2].p;


	m_fR1 = LcMath_Circumcircle(&m_vcPick, pTri);
	m_fR2 = D3DXVec3Length( &(m_vcPick- pTri[1]));
	m_fR3 = D3DXVec3Length( &(m_vcPick- pTri[2]));

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

	m_pDev->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, m_pTri, sizeof(VtxD));



	{
		D3DLIGHT9		Lgt;
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

		mtW._41 = m_vcPick.x;
		mtW._42 = m_vcPick.y;
		mtW._43 = m_vcPick.z;

		m_pDev->SetTransform(D3DTS_WORLD,&mtW);
		m_pMsh->DrawSubset(0);

		D3DXMatrixIdentity(&mtW);
		m_pDev->SetTransform(D3DTS_WORLD,&mtW);
	}


	{
		LPD3DXMESH	pMsh;
		D3DXCreateSphere(m_pDev, m_fR1, 20, 20, &pMsh, 0);
		D3DLIGHT9		Lgt;
		D3DMATERIAL9	mtl;
		D3DUtil_InitLight( Lgt, D3DLIGHT_DIRECTIONAL, -1.0f, -1.0f, 2.0f );
		D3DUtil_InitMaterial(mtl,1.0f, 0.0f,1.0f);

		m_pDev->SetLight( 0, &Lgt );
		m_pDev->LightEnable( 0, TRUE );
		m_pDev->SetRenderState(D3DRS_LIGHTING, TRUE);
		m_pDev->SetRenderState( D3DRS_AMBIENT, 0x000F0F0F );

		m_pDev->SetMaterial( &mtl );

		m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		D3DXMATRIX mtW;
		D3DXMatrixIdentity(&mtW);

		mtW._41 = m_vcPick.x;
		mtW._42 = m_vcPick.y;
		mtW._43 = m_vcPick.z;

		m_pDev->SetTransform(D3DTS_WORLD,&mtW);
		pMsh->DrawSubset(0);

		D3DXMatrixIdentity(&mtW);
		m_pDev->SetTransform(D3DTS_WORLD,&mtW);

		pMsh->Release();
	}


	m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
}