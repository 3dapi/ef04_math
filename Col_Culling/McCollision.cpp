// Implementation of the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


D3DXVECTOR3* GetPointCrossPlane(D3DXVECTOR3*p, const D3DXPLANE& n1,const D3DXPLANE& n2,const D3DXPLANE& n3)
{
	float	X;
	float	Y;
	float	Z;
	float	D;
	
	D3DXMATRIX	mtX(	-n1.d,	n1.b,	n1.c,	0,
						-n2.d,	n2.b,	n2.c,	0,
						-n3.d,	n3.b,	n3.c,	0,
						0,		0,		0,		1);
	
	D3DXMATRIX	mtY(	n1.a,	-n1.d,	n1.c,	0,
						n2.a,	-n2.d,	n2.c,	0,
						n3.a,	-n3.d,	n3.c,	0,
						0,		0,		0,		1);
	
	D3DXMATRIX	mtZ(	n1.a,	n1.b,	-n1.d,	0,
						n2.a,	n2.b,	-n2.d,	0,
						n3.a,	n3.b,	-n3.d,	0,
						0,		0,		0,		1);
	
	D3DXMATRIX	mtD(	n1.a,	n1.b,	n1.c,	0,
						n2.a,	n2.b,	n2.c,	0,
						n3.a,	n3.b,	n3.c,	0,
						0,		0,		0,		1);
	
	D = D3DXMatrixDeterminant(&mtD);
	X = D3DXMatrixDeterminant(&mtX);
	Y = D3DXMatrixDeterminant(&mtY);
	Z = D3DXMatrixDeterminant(&mtZ);
	
	p->x = X/D;
	p->y = Y/D;
	p->z = Z/D;
	
	return p;
}




CMcCollision::McObj::McObj()
{
	m_pMsh	= NULL;
	m_bCul	= NULL;
	m_fR	= 20.f;

	D3DXMatrixIdentity(&m_mtW);
}



INT CMcCollision::McObj::FrameMove()
{
	D3DXMATRIX mtY;
	D3DXMATRIX mtZ;

	++m_iTh;
	++m_iPh;

	m_iTh %= 360;
	m_iPh %= 720;

	D3DXMatrixRotationY(&mtY,D3DXToRadian(m_iTh)); 
	D3DXMatrixRotationY(&mtZ,D3DXToRadian(m_iPh));

	m_mtW = mtY * mtZ;

	m_mtW._41 = m_fO * sinf( D3DXToRadian(m_iTh) )  * cosf( D3DXToRadian(m_iPh) );
	m_mtW._42 = m_fO * cosf( D3DXToRadian(m_iTh) );
	m_mtW._43 = m_fO * sinf( D3DXToRadian(m_iTh) )  * sinf( D3DXToRadian(m_iPh) );

	return 0;
}


void CMcCollision::McObj::Render(LPDIRECT3DDEVICE9 pDev)
{
	if (m_bCul)
	{
		pDev->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
		pDev->SetRenderState(D3DRS_AMBIENT, 0x007F7F0F);
	}
	else
	{
		pDev->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		pDev->SetRenderState( D3DRS_AMBIENT, 0x000F0F0F );
	}

	pDev->SetMaterial(&m_Mtl);
	pDev->SetTransform(D3DTS_WORLD,&m_mtW);
	m_pMsh->DrawSubset(0);

	D3DXMATRIX mtW;
	D3DXMatrixIdentity(&mtW);
	pDev->SetTransform(D3DTS_WORLD,&mtW);
}




void CMcCollision::McObj::SetCul(BOOL bCol)
{
	m_bCul = bCol;
	
	if (m_bCul)
	{
		D3DUtil_InitMaterial(m_Mtl,1.0f,1.0f,0.0f);
	}
	else
	{
		D3DUtil_InitMaterial( m_Mtl, 1.0f, 0.0f, 0.0f );
	}

	
}


D3DXVECTOR3 CMcCollision::McObj::GetPos()
{
	return D3DXVECTOR3(m_mtW._41, m_mtW._42, m_mtW._43);
}



CMcCollision::CMcCollision()
{
	m_pDev	= NULL;

	m_iN	= NULL;
	m_pObj	= NULL;
}

CMcCollision::~CMcCollision()
{
	Destroy();
}


INT CMcCollision::Create(LPDIRECT3DDEVICE9 pDev)
{
	m_pDev	= pDev;

	m_pLine[ 0].d = 0xFFFFFF44;	m_pLine[ 1].d = 0xFFFFFF44;
	m_pLine[ 2].d = 0xFFFFFF44;	m_pLine[ 3].d = 0xFFFFFF44;
	
	m_pLine[ 4].d = 0xFFFFFF44;	m_pLine[ 5].d = 0xFFFFFF44;
	m_pLine[ 6].d = 0xFFFFFF44;	m_pLine[ 7].d = 0xFFFFFF44;
	
	m_pLine[ 8].d = 0xFFFFFF44;	m_pLine[ 9].d = 0xFFFFFF44;
	m_pLine[10].d = 0xFFFFFF44;	m_pLine[11].d = 0xFFFFFF44;
	
	m_pLine[12].d = 0xFFFFFF44;	m_pLine[13].d = 0xFFFFFF44;
	m_pLine[14].d = 0xFFFFFF44;	m_pLine[15].d = 0xFFFFFF44;
	
	m_pLine[16].d = 0xFFFFFF44;	m_pLine[17].d = 0xFFFFFF44;
	m_pLine[18].d = 0xFFFFFF44;	m_pLine[19].d = 0xFFFFFF44;
	
	m_pLine[20].d = 0xFFFFFF44;	m_pLine[21].d = 0xFFFFFF44;
	m_pLine[22].d = 0xFFFFFF44;	m_pLine[23].d = 0xFFFFFF44;

	

	m_iN = 150;
	m_pObj = new McObj*[m_iN];

	for(int i=0; i<m_iN; ++i)
	{
		m_pObj[i] = new McObj;

		m_pObj[i]->m_fR = (5 + rand()%10);
		m_pObj[i]->m_fO = (5 + rand()%30)* 10.f;

		m_pObj[i]->m_iTh = rand()%180;
		m_pObj[i]->m_iPh = rand()%360;

		D3DXCreateSphere(m_pDev, m_pObj[i]->m_fR, 8, 8, &m_pObj[i]->m_pMsh, 0);
	}

	D3DUtil_InitLight( m_Lgt, D3DLIGHT_DIRECTIONAL, -1.0f, -1.0f, 2.0f );

	return 0;
}


void CMcCollision::Destroy()
{
	if(m_pObj)
	{
		for(int i=0; i<m_iN; ++i)
		{
			SAFE_RELEASE(	m_pObj[i]->m_pMsh	);
			SAFE_DELETE(	m_pObj[i]			);
		}

		SAFE_DELETE_ARRAY(	m_pObj	);
	}
}


INT	CMcCollision::FrameMove()
{
	INT			i;
	D3DXVECTOR3		p1[8];
	
	D3DXMATRIX		mtViw;
	D3DXMATRIX		mtPrj;

	D3DXMATRIX		mtViwI;
	D3DXVECTOR3		vcEye;
	FLOAT			fNear;
	float			fFar;

	D3DXMATRIX		mtViwPrj;
	
	m_pDev->GetTransform(D3DTS_VIEW, &mtViw);
	m_pDev->GetTransform(D3DTS_PROJECTION, &mtPrj);

	mtViwPrj	= mtViw * mtPrj;

	D3DXMatrixInverse(&mtViwI, NULL, &mtViw);
	vcEye		= D3DXVECTOR3( mtViwI._41, mtViwI._42, mtViwI._43);				// Camera Position ReSetting

	float	a = mtPrj._33;

	fNear	= - mtPrj._43/mtPrj._33;
	fFar	= (1.f + 1/(a-1.f)) * fNear;


	D3DXVECTOR3 vcLf = -D3DXVECTOR3(mtViwPrj._14 + mtViwPrj._11, mtViwPrj._24 + mtViwPrj._21, mtViwPrj._34 + mtViwPrj._31);		// Left
	D3DXVECTOR3 vcRg = -D3DXVECTOR3(mtViwPrj._14 - mtViwPrj._11, mtViwPrj._24 - mtViwPrj._21, mtViwPrj._34 - mtViwPrj._31);		// Right
	D3DXVECTOR3 vcTp = -D3DXVECTOR3(mtViwPrj._14 - mtViwPrj._12, mtViwPrj._24 - mtViwPrj._22, mtViwPrj._34 - mtViwPrj._32);		// Top
	D3DXVECTOR3 vcBt = -D3DXVECTOR3(mtViwPrj._14 + mtViwPrj._12, mtViwPrj._24 + mtViwPrj._22, mtViwPrj._34 + mtViwPrj._32);		// Bottom
	D3DXVECTOR3 vcNr = -D3DXVECTOR3(mtViwI._31, mtViwI._32, mtViwI._33);				// Near
	D3DXVECTOR3 vcFr = -vcNr;															// Far

	D3DXVECTOR3 vcZn = vcEye - vcNr * fNear*100;											// 안에서 밖으로 나오는 방향이기 때문에 -를 했음.
	D3DXVECTOR3 vcZf = vcEye - vcNr * fFar*0.1f;

	D3DXPlaneFromPointNormal((D3DXPLANE*)&m_Frsm[0], &vcZn, &vcNr);				// Near Plane
	D3DXPlaneFromPointNormal((D3DXPLANE*)&m_Frsm[1], &vcZf, &vcFr);				// Far Plane
	D3DXPlaneFromPointNormal((D3DXPLANE*)&m_Frsm[2], &vcEye, &vcLf);			// Left Plane
	D3DXPlaneFromPointNormal((D3DXPLANE*)&m_Frsm[3], &vcEye, &vcRg);			// Right Plane
	D3DXPlaneFromPointNormal((D3DXPLANE*)&m_Frsm[4], &vcEye, &vcTp);			// Top Plane
	D3DXPlaneFromPointNormal((D3DXPLANE*)&m_Frsm[5], &vcEye, &vcBt);			// Bottom Plane


	
	GetPointCrossPlane(&p1[0], m_Frsm[0], m_Frsm[2], m_Frsm[4]);
	GetPointCrossPlane(&p1[1], m_Frsm[0], m_Frsm[4], m_Frsm[3]);
	GetPointCrossPlane(&p1[2], m_Frsm[0], m_Frsm[3], m_Frsm[5]);
	GetPointCrossPlane(&p1[3], m_Frsm[0], m_Frsm[5], m_Frsm[2]);
	
	GetPointCrossPlane(&p1[4], m_Frsm[1], m_Frsm[2], m_Frsm[4]);
	GetPointCrossPlane(&p1[5], m_Frsm[1], m_Frsm[4], m_Frsm[3]);
	GetPointCrossPlane(&p1[6], m_Frsm[1], m_Frsm[3], m_Frsm[5]);
	GetPointCrossPlane(&p1[7], m_Frsm[1], m_Frsm[5], m_Frsm[2]);
	
	D3DXVECTOR3 zD(mtViwI._31, mtViwI._32, mtViwI._33);
	
	for(i=0; i<8; ++i)
		p1[i] += zD*200.f;

	

	m_pLine[ 0].p = p1[0];	m_pLine[ 1].p = p1[1];
	m_pLine[ 2].p = p1[1];	m_pLine[ 3].p = p1[2];
	m_pLine[ 4].p = p1[2];	m_pLine[ 5].p = p1[3];
	m_pLine[ 6].p = p1[3];	m_pLine[ 7].p = p1[0];
	
	m_pLine[ 8].p = p1[4];	m_pLine[ 9].p = p1[5];
	m_pLine[10].p = p1[5];	m_pLine[11].p = p1[6];
	m_pLine[12].p = p1[6];	m_pLine[13].p = p1[7];
	m_pLine[14].p = p1[7];	m_pLine[15].p = p1[4];
	
	m_pLine[16].p = p1[0];	m_pLine[17].p = p1[4];
	m_pLine[18].p = p1[1];	m_pLine[19].p = p1[5];
	m_pLine[20].p = p1[2];	m_pLine[21].p = p1[6];
	m_pLine[22].p = p1[3];	m_pLine[23].p = p1[7];


	D3DXPlaneFromPoints(&m_Frsm[0], &p1[0], &p1[1], &p1[2]);
	D3DXPlaneFromPoints(&m_Frsm[1], &p1[4], &p1[6], &p1[5]);
	D3DXPlaneFromPoints(&m_Frsm[2], &p1[0], &p1[3], &p1[7]);
	D3DXPlaneFromPoints(&m_Frsm[3], &p1[1], &p1[5], &p1[2]);
	D3DXPlaneFromPoints(&m_Frsm[4], &p1[0], &p1[4], &p1[5]);
	D3DXPlaneFromPoints(&m_Frsm[5], &p1[3], &p1[2], &p1[7]);
	for(i=0; i<m_iN; ++i)
	{
		SAFE_FRMOV(m_pObj[i]);

		if( IsInFrustum(m_pObj[i]->GetPos()))
			m_pObj[i]->SetCul(TRUE);

		else
			m_pObj[i]->SetCul();

	}

	return 0;
}

void CMcCollision::Render()
{
	m_pDev->SetRenderState( D3DRS_LIGHTING,  FALSE);
	m_pDev->SetRenderState( D3DRS_ALPHABLENDENABLE,  FALSE);
	m_pDev->SetRenderState( D3DRS_ALPHATESTENABLE,  FALSE);
	
	m_pDev->SetTexture(0, NULL);
	m_pDev->SetFVF(CMcCollision::VtxD::FVF);
	m_pDev->DrawPrimitiveUP(D3DPT_LINELIST, 12, m_pLine, sizeof(CMcCollision::VtxD));


	m_pDev->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	m_pDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_pDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	m_pDev->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	m_pDev->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	m_pDev->SetRenderState( D3DRS_DITHERENABLE,	FALSE );
	m_pDev->SetRenderState( D3DRS_SPECULARENABLE,	FALSE );
	m_pDev->SetRenderState( D3DRS_ZENABLE,			TRUE );
	m_pDev->SetRenderState( D3DRS_LIGHTING,		TRUE );
	m_pDev->SetRenderState( D3DRS_ALPHABLENDENABLE,  FALSE);
	m_pDev->SetRenderState( D3DRS_ALPHATESTENABLE,  FALSE);
	
	m_pDev->SetTexture(0, 0);
	m_pDev->SetLight(0, &m_Lgt );
	m_pDev->LightEnable( 0, TRUE );

	for(int i=0; i<m_iN; ++i)
	{
		m_pObj[i]->Render(m_pDev);
	}

	m_pDev->SetRenderState( D3DRS_LIGHTING,  FALSE);
}


BOOL CMcCollision::IsInFrustum(const D3DXVECTOR3& pos)
{
	if(D3DXPlaneDotCoord(&m_Frsm[0], &pos)>0)
		return false;

	if(D3DXPlaneDotCoord(&m_Frsm[1], &pos)>0)
		return false;

	if(D3DXPlaneDotCoord(&m_Frsm[2], &pos)>0)
		return false;

	if(D3DXPlaneDotCoord(&m_Frsm[3], &pos)>0)
		return false;

	if(D3DXPlaneDotCoord(&m_Frsm[4], &pos)>0)
		return false;

	if(D3DXPlaneDotCoord(&m_Frsm[5], &pos)>0)
		return false;

	return true;
}
