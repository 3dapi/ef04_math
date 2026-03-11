// Interface for the CMcPicking class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _McPicking_H_
#define _McPicking_H_



struct McObj
{
	LPD3DXMESH	pMsh;
	D3DXMATRIX	mtWld;

	FLOAT		fRadius;
	D3DXVECTOR3	vcPos;

	BOOL		bWire;
};


#define MAX_OBJECT	50

class CMcPicking
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
	McObj		m_pObj[MAX_OBJECT];
	

public:
	CMcPicking();
	~CMcPicking();

	INT		Create(LPDIRECT3DDEVICE9 pDev);
	void	Destroy();

	INT		FrameMove();
	void	Render();
};

#endif



