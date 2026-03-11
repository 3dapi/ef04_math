// Implementation of the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


INT LcMath_CollisionPointToTriangle(const D3DXVECTOR3* pTri, const D3DXVECTOR3* pPoint)
{
	D3DXVECTOR3	vcA = pTri[1] - pTri[0];
	D3DXVECTOR3	vcB = pTri[2] - pTri[0];
	D3DXVECTOR3	vcP = *pPoint - pTri[0];

	FLOAT	AA = D3DXVec3Dot(&vcA, &vcA);
	FLOAT	AB = D3DXVec3Dot(&vcA, &vcB);
	FLOAT	BB = D3DXVec3Dot(&vcB, &vcB);
	FLOAT	AP = D3DXVec3Dot(&vcA, &vcP);
	FLOAT	BP = D3DXVec3Dot(&vcB, &vcP);

	FLOAT	fA = AP * BB - AB * BP;
	FLOAT	fB = AA * BP - AB * AP;
	FLOAT	fD = AA * BB - AB * AB;

	if( fA>=0 && fB>=0 && (fA+fB)<=fD)
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
		m_bColl = LcMath_CollisionPointToTriangle(pTri, &m_Pos);

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

