// Interface for the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _McCollision_H_
#define _McCollision_H_

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

	D3DXVECTOR3 m_vcPick;
	LPD3DXMESH	m_pMsh;

public:
	FLOAT		m_fR1;
	FLOAT		m_fR2;
	FLOAT		m_fR3;
	
public:
	CMcCollision();
	~CMcCollision();

	INT		Create(LPDIRECT3DDEVICE9 pDev);
	void	Destroy();

	INT		FrameMove();
	void	Render();
};

#endif