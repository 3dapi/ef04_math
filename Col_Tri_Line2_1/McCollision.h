// Interface for the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _McCollision_H_
#define _McCollision_H_


struct LcLine
{
	// Start Pointer, Tranverse Vector
	union	{	struct	{	D3DXVECTOR3 p;	D3DXVECTOR3 t;	};	FLOAT m[6];	};

	LcLine(){}
	LcLine(const FLOAT*_m)		{	if(!_m){m[0]=m[1]=m[2]=m[3]=m[4]=m[5]=0;}else{m[0]=_m[0];m[1]=_m[1];m[2]=_m[2];m[3]=_m[3];m[4]=_m[4];m[5]=_m[5];}}
	LcLine(const LcLine& rhs)	{	p = rhs.p; t = rhs.t;	}

	LcLine(FLOAT Px,FLOAT Py,FLOAT Pz,FLOAT Tx,FLOAT Ty,FLOAT Tz)
	{
		p.x = Px;
		p.y = Py;
		p.z = Pz;
		t.x = Tx;
		t.y = Ty;
		t.z = Tz;
	}

	LcLine(const D3DXVECTOR3& P, const D3DXVECTOR3& T)
	{
		p = P;
		t = T;
	}

	// casting
	operator FLOAT*()						{	return (FLOAT *) &p.x;			}
	operator const FLOAT*() const			{	return (const FLOAT *) &p.x;	}

	// unary operators
	LcLine operator+() const				{	return LcLine(p.x, p.y, p.z, t.x, t.y, t.z);		}
	LcLine operator-() const				{	return LcLine(-p.x, -p.y, -p.z, -t.x, -t.y, -t.z);	}

	bool operator==(const LcLine& v) const	{	return p.x == v.p.x && p.y == v.p.y && p.z == v.p.z && t.x == v.t.x && t.y == v.t.y && t.z == v.t.z;	}
	bool operator!=(const LcLine& v) const	{	return p.x != v.p.x || p.y != v.p.y || p.z != v.p.z || t.x != v.t.x || t.y != v.t.y || t.z != v.t.z;	}
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

	VtxD		m_pTri[3];
	VtxD		m_pLine[2];

	INT			m_bColl;
	D3DXVECTOR3 m_vcPick;

	LPD3DXMESH	m_pMsh;

public:
	CMcCollision();
	~CMcCollision();

	INT		Create(LPDIRECT3DDEVICE9 pDev);
	void	Destroy();

	INT		FrameMove();
	void	Render();
};

#endif