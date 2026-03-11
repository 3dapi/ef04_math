// Interface for the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _McCollision_H_
#define _McCollision_H_



struct LcLine																	// 직선의 방정식
{
	union	{	struct	{	D3DXVECTOR3 x0;	D3DXVECTOR3 t;	};	FLOAT m[6];	};				// Start Pointer, Tranverse Vector

	LcLine(){}
	LcLine(const FLOAT*_m)			{	if(_m){m[0]=_m[0];m[1]=_m[1];m[2]=_m[2];m[3]=_m[3];m[4]=_m[4];m[5]=_m[5];}else{m[0]=m[1]=m[2]=m[3]=m[4]=m[5]=0;}}
	LcLine(const LcLine& _rh)		{	x0 = _rh.x0; t = _rh.t;	}
	LcLine(FLOAT a,FLOAT b,FLOAT c,FLOAT d,FLOAT e,FLOAT f)	{	m[0]=a;m[1]=b;m[2]=c;m[3]=d;m[4]=e;m[5]=f;}

	// casting
	operator FLOAT*()						{	return (FLOAT *) &x0.x;			}
	operator const FLOAT*() const			{	return (const FLOAT *) &x0.x;	}

	// unary operators
	LcLine operator+() const				{	return *this;												}
	LcLine operator-() const				{	return LcLine(-x0.x, -x0.y, -x0.z, -t.x, -t.y, -t.z);		}

	bool operator==(const LcLine& v) const	{	return x0.x == v.x0.x && x0.y == v.x0.y && x0.z == v.x0.z && t.x == v.t.x && t.y == v.t.y && t.z == v.t.z;	}
	bool operator!=(const LcLine& v) const	{	return x0.x != v.x0.x || x0.y != v.x0.y || x0.z != v.x0.z || t.x != v.t.x || t.y != v.t.y || t.z != v.t.z;	}
};




struct LcTri																	// 삼각형
{
	union
	{
		D3DVECTOR	m[3];

		struct
		{
			D3DXVECTOR3	_0;
			D3DXVECTOR3	_1;
			D3DXVECTOR3	_2;
		};


	};				// Start Pointer, Tranverse Vector

	LcTri();
	LcTri(const D3DXVECTOR3*_m);
	LcTri(D3DXVECTOR3 __0,D3DXVECTOR3 __1,D3DXVECTOR3 __2);

	LcTri(const LcTri& _r);
	LcTri(const FLOAT* _p);

	LcTri(FLOAT _0x,FLOAT _0y,FLOAT _0z
		, FLOAT _1x,FLOAT _1y,FLOAT _1z
		, FLOAT _2x,FLOAT _2y,FLOAT _2z);

	// casting
	operator FLOAT*();
	operator const FLOAT*() const;

	bool operator==(const LcTri& v) const;
	bool operator!=(const LcTri& v) const;


	void Set(D3DXVECTOR3 __0, D3DXVECTOR3 __1, D3DXVECTOR3 __2);
};



// Hexahedron
struct LnCubeH
{
	union
	{
		D3DVECTOR	m[8];

		struct
		{
			D3DXVECTOR3 _0;	D3DXVECTOR3 _1;	D3DXVECTOR3 _2;	D3DXVECTOR3 _3;
			D3DXVECTOR3 _4;	D3DXVECTOR3 _5;	D3DXVECTOR3 _6;	D3DXVECTOR3 _7;
		};
	};


	LnCubeH();
	LnCubeH(const D3DXVECTOR3* _m);
	LnCubeH(	  const D3DXVECTOR3& __0
				, const D3DXVECTOR3& __1
				, const D3DXVECTOR3& __2
				, const D3DXVECTOR3& __3
				, const D3DXVECTOR3& __4
				, const D3DXVECTOR3& __5
				, const D3DXVECTOR3& __6
				, const D3DXVECTOR3& __7);

	operator FLOAT*();
	operator const FLOAT*() const;

//	D3DXVECTOR3* operator[](int nIdx) const
//	{
//		return (D3DXVECTOR3*)(&_0.x + nIdx * sizeof( D3DXVECTOR3));
//	}

	BOOL operator==(const LnCubeH& v) const;
	BOOL operator !=(const LnCubeH& v) const;

	void Set(const D3DXVECTOR3* _m);
	void Set(const LnCubeH& r);
};

class CMcCollision
{
public:
	struct VtxD
	{
		D3DXVECTOR3	p;
		DWORD		d;

		VtxD()								{	p.x=p.y=p.z=0.f;d=0xFFFFFFFF;	}
		VtxD(FLOAT X,FLOAT Y,FLOAT Z,DWORD D){	p.x=X; p.y=Y; p.z=Z; d=D;		}
		enum	{FVF = (D3DFVF_XYZ|D3DFVF_DIFFUSE),};
	};

protected:
	LPDIRECT3DDEVICE9	m_pDev;

	LnCubeH		m_pHexa;
	VtxD		m_pLine[2];

	BOOL		m_bColl;

	D3DXVECTOR3 m_vcPick;
	LPD3DXMESH	m_pMsh;

	VtxD	m_BoxLine[24];

public:
	CMcCollision();
	~CMcCollision();

	INT		Create(LPDIRECT3DDEVICE9 pDev);
	void	Destroy();

	INT		FrameMove();
	void	Render();
};

#endif