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



// Cylinder
struct LnCylinder
{
	// Start Pointer, Tranverse Vector, Radius, Height
	union{ struct{	D3DXVECTOR3 p;	D3DXVECTOR3 t;	FLOAT r; FLOAT h; };	FLOAT m[8];	};

	LnCylinder(){}

	LnCylinder(const FLOAT*_m)
	{
		if(!_m)
		{
			m[0]=m[1]=m[2]=m[3]=m[4]=m[5]=m[6]=m[7]=0;
		}
		else
		{
			m[0]=_m[0];
			m[1]=_m[1];
			m[2]=_m[2];
			m[3]=_m[3];
			m[4]=_m[4];
			m[5]=_m[5];
			m[6]=_m[6];
			m[7]=_m[7];
		}
	}

	LnCylinder(const LnCylinder& rhs)
	{
		p = rhs.p;
		t = rhs.t;
		r = rhs.r;
		h = rhs.h;
	}

	LnCylinder(FLOAT Px,FLOAT Py,FLOAT Pz,FLOAT Tx,FLOAT Ty,FLOAT Tz, FLOAT R, FLOAT H)
	{
		p.x = Px;
		p.y = Py;
		p.z = Pz;
		t.x = Tx;
		t.y = Ty;
		t.z = Tz;
		r	= R;
		h	= H;
	}

	LnCylinder(const D3DXVECTOR3& P, const D3DXVECTOR3& T, FLOAT R, FLOAT H)
	{
		p = P;
		t = T;
		r = R;
		h = H;
	}

	// casting
	operator FLOAT*()						{	return (FLOAT *) &p.x;			}
	operator const FLOAT*() const			{	return (const FLOAT *) &p.x;	}

	// unary operators
	bool operator==(const LnCylinder& v) const	{	return p.x == v.p.x && p.y == v.p.y && p.z == v.p.z && t.x == v.t.x && t.y == v.t.y && t.z == v.t.z && r == v.r && h == v.h;	}
	bool operator!=(const LnCylinder& v) const	{	return p.x != v.p.x || p.y != v.p.y || p.z != v.p.z || t.x != v.t.x || t.y != v.t.y || t.z != v.t.z || r != v.r || h != v.h;	}
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

	LnCylinder	m_Cyln;
	VtxD		m_pTstL[2];
	VtxD		m_CylnO[2];

	INT			m_bColl;
	D3DXVECTOR3 m_vcPick;

	D3DXVECTOR3 m_vcSphere[2];
	LPD3DXMESH	m_pMsh;
	LPD3DXMESH	m_pCyl;
	D3DXMATRIX	m_mtCyl;

public:
	CMcCollision();
	~CMcCollision();

	INT		Create(LPDIRECT3DDEVICE9 pDev);
	void	Destroy();

	INT		FrameMove();
	void	Render();
};

#endif