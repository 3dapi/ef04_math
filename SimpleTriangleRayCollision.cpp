INT SimpleCollisionRayTriangle(	const D3DXVECTOR3* pLinePos
								,	const D3DXVECTOR3* pLineDir
								,	const D3DXVECTOR3* pV0
								,	const D3DXVECTOR3* pV1
								,	const D3DXVECTOR3* pV2
						 )
{
	D3DXVECTOR3	vcRayDir = * pLineDir;


	D3DXVECTOR3	t;
	D3DXVECTOR3	a;
	D3DXVECTOR3	b;


	FLOAT fDot0;
	FLOAT fDot1;
	FLOAT fDot2;

	a = *pV0 - *pLinePos;
	b = *pV1 - *pLinePos;
	D3DXVec3Cross(&t, &a, &b);
	fDot0 = D3DXVec3Dot(&vcRayDir, &t);


	a = *pV1 - *pLinePos;
	b = *pV2 - *pLinePos;
	D3DXVec3Cross(&t, &a, &b);
	fDot1 = D3DXVec3Dot(&vcRayDir, &t);


	a = *pV2 - *pLinePos;
	b = *pV0 - *pLinePos;
	D3DXVec3Cross(&t, &a, &b);
	fDot2 = D3DXVec3Dot(&vcRayDir, &t);

	if( fDot0* fDot1<0 ||
		fDot1* fDot2<0 ||
		fDot2* fDot0<0)
		return -1;

	return 0;
}