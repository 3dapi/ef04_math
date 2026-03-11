// Interface for the CMcCollision class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _McCollision_H_
#define _McCollision_H_

class CMcCollision
{
public:
	struct McObj
	{
		LPD3DXMESH		m_pMsh;
		D3DXMATRIX		m_mtW;
		D3DMATERIAL9	m_Mtl;

		BOOL			m_bCul;
		FLOAT			m_fR;			// 반경
		FLOAT			m_fO;

		INT				m_iTh;
		INT				m_iPh;

		McObj();

		INT		FrameMove();
		void	Render(LPDIRECT3DDEVICE9 pDev);
		void	SetCul(BOOL bCol=FALSE);
		D3DXVECTOR3	GetPos();
	};

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

	CMcCollision::VtxD	m_pLine[24];

	INT				m_iN;
	McObj**			m_pObj;
	D3DXPLANE		m_Frsm[6];

	D3DLIGHT9		m_Lgt;
	
public:
	CMcCollision();
	~CMcCollision();

	INT		Create(LPDIRECT3DDEVICE9 pDev);
	void	Destroy();

	INT		FrameMove();
	void	Render();

	BOOL	IsInFrustum(const D3DXVECTOR3& pos);
};

#endif