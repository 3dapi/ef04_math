// Implementation of the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


LcTri::LcTri()
{
}

LcTri::LcTri(const D3DXVECTOR3*_m)
{
	if(_m)
	{
		_0=_m[0];
		_1=_m[1];
		_2=_m[2];
	}
	else
	{
		_0.x =0; _0.y =0; _0.z =0;
		_1.x =0; _1.y =0; _1.z =0;
		_2.x =0; _2.y =0; _2.z =0;
	}
}

LcTri::LcTri(const LcTri& _r)
{
	_0 = _r._0;
	_1 = _r._1;
	_2 = _r._2;
}

LcTri::LcTri(const FLOAT* _p)
{
	_0.x =_p[0]; _0.y =_p[1]; _0.z =_p[2];
	_1.x =_p[3]; _1.y =_p[4]; _1.z =_p[5];
	_2.x =_p[6]; _2.y =_p[7]; _2.z =_p[8];
}

LcTri::LcTri(D3DXVECTOR3 __0,D3DXVECTOR3 __1,D3DXVECTOR3 __2)
{
	_0 = __0;
	_1 = __1;
	_2 = __2;
}


LcTri::LcTri(FLOAT _0x,FLOAT _0y,FLOAT _0z
	, FLOAT _1x,FLOAT _1y,FLOAT _1z
	, FLOAT _2x,FLOAT _2y,FLOAT _2z)
{
	_0.x =_0x; _0.y =_0y; _0.z =_0z;
	_1.x =_1x; _1.y =_1y; _1.z =_1z;
	_2.x =_2x; _2.y =_2y; _2.z =_2z;
}



void LcTri::Set(D3DXVECTOR3 __0, D3DXVECTOR3 __1, D3DXVECTOR3 __2)
{
	_0 = __0;
	_1 = __1;
	_2 = __2;
}


// casting
LcTri::operator FLOAT*()
{
	return (FLOAT *) &_0.x;
}

LcTri::operator const FLOAT*() const
{
	return (const FLOAT *) &_0.x;
}

bool LcTri::operator==(const LcTri& v) const
{
	return	   _0.x == v._0.x && _0.y == v._0.y && _0.z == v._0.z
			&& _1.x == v._1.x && _1.y == v._1.y && _1.z == v._1.z
			&& _2.x == v._2.x && _2.y == v._2.y && _2.z == v._2.z
			;
}

bool LcTri::operator!=(const LcTri& v) const
{
	return	   _0.x != v._0.x || _0.y != v._0.y || _0.z != v._0.z
			|| _1.x != v._1.x || _1.y != v._1.y || _1.z != v._1.z
			|| _2.x != v._2.x || _2.y != v._2.y || _2.z != v._2.z
			;
}









LnCubeH::LnCubeH()
{
}

LnCubeH::LnCubeH(const D3DXVECTOR3* _m)
{
	if(_m)
	{
		_0 = _m[0];
		_1 = _m[1];
		_2 = _m[2];
		_3 = _m[3];
		_4 = _m[4];
		_5 = _m[5];
		_6 = _m[6];
		_7 = _m[7];
	}
	else
	{
		_0.x = 0; _0.y = 0; _0.z = 0;
		_1.x = 0; _1.y = 0; _1.z = 0;
		_2.x = 0; _2.y = 0; _2.z = 0;
		_3.x = 0; _3.y = 0; _3.z = 0;
		_4.x = 0; _4.y = 0; _4.z = 0;
		_5.x = 0; _5.y = 0; _5.z = 0;
		_6.x = 0; _6.y = 0; _6.z = 0;
		_7.x = 0; _7.y = 0; _7.z = 0;
	}
}

LnCubeH::LnCubeH(	  const D3DXVECTOR3& __0
			, const D3DXVECTOR3& __1
			, const D3DXVECTOR3& __2
			, const D3DXVECTOR3& __3
			, const D3DXVECTOR3& __4
			, const D3DXVECTOR3& __5
			, const D3DXVECTOR3& __6
			, const D3DXVECTOR3& __7)
{
	_0 = __0;	_1 = __1;	_2 = __2;	_3 = __3;
	_4 = __4;	_5 = __5;	_6 = __6;	_7 = __7;
}


LnCubeH::operator FLOAT*()
{
	return (FLOAT *) &_0.x;
}

LnCubeH::operator const FLOAT*() const
{
	return (const FLOAT *) &_0.x;
}


BOOL LnCubeH::operator==(const LnCubeH& v) const
{
	return	_0 == v._0 &&
			_1 == v._1 &&
			_2 == v._2 &&
			_3 == v._3 &&
			_4 == v._4 &&
			_5 == v._5 &&
			_6 == v._6 &&
			_7 == v._7;
}

BOOL LnCubeH::operator !=(const LnCubeH& v) const
{
	return	_0 != v._0 ||
			_1 != v._1 ||
			_2 != v._2 ||
			_3 != v._3 ||
			_4 != v._4 ||
			_5 != v._5 ||
			_6 != v._6 ||
			_7 != v._7;
}

void LnCubeH::Set(const D3DXVECTOR3* _m)
{
	if(_m)
	{
		_0 = _m[0];
		_1 = _m[1];
		_2 = _m[2];
		_3 = _m[3];
		_4 = _m[4];
		_5 = _m[5];
		_6 = _m[6];
		_7 = _m[7];
	}
	else
	{
		_0.x = 0; _0.y = 0; _0.z = 0;
		_1.x = 0; _1.y = 0; _1.z = 0;
		_2.x = 0; _2.y = 0; _2.z = 0;
		_3.x = 0; _3.y = 0; _3.z = 0;
		_4.x = 0; _4.y = 0; _4.z = 0;
		_5.x = 0; _5.y = 0; _5.z = 0;
		_6.x = 0; _6.y = 0; _6.z = 0;
		_7.x = 0; _7.y = 0; _7.z = 0;
	}
}

void LnCubeH::Set(const LnCubeH& r)
{
	_0 = r._0;
	_1 = r._1;
	_2 = r._2;
	_3 = r._3;
	_4 = r._4;
	_5 = r._5;
	_6 = r._6;
	_7 = r._7;
}



BOOL LcMath_CollisionLineToTriangle(D3DXVECTOR3* vcOut
									, D3DXVECTOR3* pTri
									, LcLine* pLine
									, BOOL bRectangle=FALSE
									, BOOL bPositiveDirection=FALSE)
{
	D3DXPLANE plane;
	D3DXVECTOR3 vcN;
	FLOAT		fD;

	D3DXVECTOR3 vcA = pTri[1] - pTri[0];
	D3DXVECTOR3 vcB = pTri[2] - pTri[0];

	D3DXVec3Cross(&vcN, &vcA, &vcB);
	D3DXVec3Normalize(&vcN,&vcN);

	fD = -D3DXVec3Dot(&vcN, &pTri[0]);

	plane = D3DXPLANE(vcN.x, vcN.y, vcN.z, fD);

	D3DXVECTOR3 vcC;
	D3DXVECTOR3 vcD;

	FLOAT		fT;
	FLOAT		fAC;
	FLOAT		fBC;
	FLOAT		fAB;

	FLOAT		fA;
	FLOAT		fB;
	FLOAT		fU;
	FLOAT		fV;

	D3DXVECTOR3 vcL = pLine->t;

	fT = D3DXVec3Dot(&vcL, &vcN);
	fT = -( fD+ D3DXVec3Dot(&vcN, &pLine->x0))/fT;

	if(bPositiveDirection && fT<=0)
		return FALSE;

	vcC = pLine->x0 + fT * vcL;
	vcC -= pTri[0];

	fA = D3DXVec3Length(&vcA);
	fB = D3DXVec3Length(&vcB);

	fAC = D3DXVec3Dot(&vcA, &vcC);
	fBC = D3DXVec3Dot(&vcB, &vcC);
	fAB = D3DXVec3Dot(&vcA, &vcB);

	fD = fA * fA * fB * fB - fAB*fAB+0.000001f;
	fU = (fAC * fB*  fB - fAB * fBC)/fD;
	fV = (fA * fA * fBC - fAB * fAC)/fD;

	vcD = fU * vcA + fV * vcB;
	vcD += pTri[0];
	*vcOut = vcD;

	if(bRectangle)
	{
		if(fU>=0 && fU<=1 && fV>=0 && fV<=1)
			return TRUE;
	}
	else
	{
		if(fU>=0 && fU<=1 && fV>=0 && fV<=1 && (fU+fV)<1.f)
			return TRUE;
	}

	return FALSE;
}




BOOL LcMath_CollisionLineToCubeAABB(D3DXVECTOR3* vcOut
									, D3DXVECTOR3* pVcBox
									, LcLine* pLine
									, BOOL bRectangle=TRUE
									, BOOL bPositiveDirection=TRUE)
{
	BOOL	hr= FALSE;
	FLOAT	w;
	FLOAT	h;
	FLOAT	d;

	D3DXVECTOR3 vcP[8];
	D3DXVECTOR3 vcT;

	vcP[0] = pVcBox[0];
	vcP[7] = pVcBox[1];

	vcT = vcP[7]- vcP[0];
	w = vcT.x;
	h = vcT.y;
	d = vcT.z;

	vcP[1] = vcP[0] + D3DXVECTOR3(w, 0, 0);
	vcP[2] = vcP[0] + D3DXVECTOR3(0, h, 0);
	vcP[3] = vcP[0] + D3DXVECTOR3(w, h, 0);
	vcP[4] = vcP[0] + D3DXVECTOR3(0, 0, d);
	vcP[5] = vcP[0] + D3DXVECTOR3(w, 0, d);
	vcP[6] = vcP[0] + D3DXVECTOR3(0, h, d);

	LcTri	Tri;

	Tri.Set(vcP[0], vcP[1], vcP[2]);
	hr = LcMath_CollisionLineToTriangle(&vcT, (D3DXVECTOR3*)&Tri, pLine, bRectangle, bPositiveDirection);

	if(hr)
	{
		*vcOut= vcT;
		return TRUE;
	}

	Tri.Set(vcP[0], vcP[1], vcP[4]);
	hr = LcMath_CollisionLineToTriangle(&vcT, (D3DXVECTOR3*)&Tri, pLine, bRectangle, bPositiveDirection);

	if(hr)
	{
		*vcOut= vcT;
		return TRUE;
	}

	Tri.Set(vcP[0], vcP[2], vcP[4]);
	hr = LcMath_CollisionLineToTriangle(&vcT, (D3DXVECTOR3*)&Tri, pLine, bRectangle, bPositiveDirection);

	if(hr)
	{
		*vcOut= vcT;
		return TRUE;
	}

	Tri.Set(vcP[7], vcP[5], vcP[6]);
	hr = LcMath_CollisionLineToTriangle(&vcT, (D3DXVECTOR3*)&Tri, pLine, bRectangle, bPositiveDirection);

	if(hr)
	{
		*vcOut= vcT;
		return TRUE;
	}

	Tri.Set(vcP[7], vcP[5], vcP[3]);
	hr = LcMath_CollisionLineToTriangle(&vcT, (D3DXVECTOR3*)&Tri, pLine, bRectangle, bPositiveDirection);

	if(hr)
	{
		*vcOut= vcT;
		return TRUE;
	}

	Tri.Set(vcP[7], vcP[6], vcP[3]);
	hr = LcMath_CollisionLineToTriangle(&vcT, (D3DXVECTOR3*)&Tri, pLine, bRectangle, bPositiveDirection);

	if(hr)
	{
		*vcOut= vcT;
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

	D3DXVECTOR3	vcPos(50, 50, 50);

	FLOAT	w = 250;
	FLOAT	h = 280;
	FLOAT	d = 210;

	m_pHexa._0	= vcPos + D3DXVECTOR3(0, 0, 0);
	m_pHexa._1	= vcPos + D3DXVECTOR3(0, h, 0);
	m_pHexa._2	= vcPos + D3DXVECTOR3(w, 0, 0);
	m_pHexa._3	= vcPos + D3DXVECTOR3(w, h, 0);

	m_pHexa._4	= vcPos + D3DXVECTOR3(0, 0, d);
	m_pHexa._5	= vcPos + D3DXVECTOR3(0, h, d);
	m_pHexa._6	= vcPos + D3DXVECTOR3(w, 0, d);
	m_pHexa._7	= vcPos + D3DXVECTOR3(w, h, d);


	m_pLine[0].p = D3DXVECTOR3(  130, 230,  130);
	m_pLine[1].p = D3DXVECTOR3(  150, 240,  150);

	m_pLine[0].d = 0xFF000000;
	m_pLine[1].d = 0xFFFF0000;

	D3DXCreateSphere(m_pDev, 3, 8, 8, &m_pMsh, 0);


	for(int i=0; i<24; ++i)
	{
		m_BoxLine[i].d = 0xFFFFFF00;
	}

	m_BoxLine[ 0].p = m_pHexa._1;		m_BoxLine[ 1].p = m_pHexa._0;
	m_BoxLine[ 2].p = m_pHexa._2;		m_BoxLine[ 3].p = m_pHexa._0;
	m_BoxLine[ 4].p = m_pHexa._1;		m_BoxLine[ 5].p = m_pHexa._3;
	m_BoxLine[ 6].p = m_pHexa._2;		m_BoxLine[ 7].p = m_pHexa._3;

	m_BoxLine[ 8].p = m_pHexa._5;		m_BoxLine[ 9].p = m_pHexa._4;
	m_BoxLine[10].p = m_pHexa._6;		m_BoxLine[11].p = m_pHexa._4;
	m_BoxLine[12].p = m_pHexa._5;		m_BoxLine[13].p = m_pHexa._7;
	m_BoxLine[14].p = m_pHexa._6;		m_BoxLine[15].p = m_pHexa._7;

	m_BoxLine[16].p = m_pHexa._0;		m_BoxLine[17].p = m_pHexa._4;
	m_BoxLine[18].p = m_pHexa._1;		m_BoxLine[19].p = m_pHexa._5;
	m_BoxLine[20].p = m_pHexa._2;		m_BoxLine[21].p = m_pHexa._6;
	m_BoxLine[22].p = m_pHexa._3;		m_BoxLine[23].p = m_pHexa._7;

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


	LcLine Line;

	Line.x0 = pLine[0];
	Line.t = pLine[1]-pLine[0];

	D3DXVec3Normalize(&Line.t, &Line.t);



	D3DXVECTOR3 pBox[2];

	pBox[0] = m_pHexa._0;
	pBox[1] = m_pHexa._7;

//	for(int i=0; i<5000; ++i)
	m_bColl = LcMath_CollisionLineToCubeAABB(&m_vcPick, pBox, &Line);

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

	m_pDev->DrawPrimitiveUP(D3DPT_LINELIST, 12, m_BoxLine, sizeof(VtxD));


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

	m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
}

