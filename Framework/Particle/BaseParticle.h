//=====================================
//
//ベースパーティクルヘッダ[BaseParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEPARTICLE_H_
#define _BASEPARTICLE_H_

#include "../../main.h"
#include "../Renderer3D/BillboardObject.h"

/**************************************
前方宣言
***************************************/

/**************************************
パーティクルのUV座標
***************************************/
class ParticleUV
{
public:
	float u, v;

	ParticleUV() :
		u(0.0f),
		v(0.0f)
	{

	}

	ParticleUV(float u, float v) :
		u(u),
		v(v)
	{

	}
};

/**************************************
BaseParticleクラス
※継承先でInit(), Update()を実装する
***************************************/
class BaseParticle : public BillboardObject
{
public:
	BaseParticle();
	BaseParticle(int life);
	BaseParticle(int lifeMin, int lifeMax);
	BaseParticle(float u, float v, int lifeMin, int lifeMax);
	virtual ~BaseParticle();

	virtual void Init() = 0;
	virtual void Update() = 0;

	virtual bool IsActive() const override;
	virtual D3DXMATRIX GetWorldMtx();

	ParticleUV uv;

protected:
	int cntFrame;
	int lifeFrame;

};

#endif