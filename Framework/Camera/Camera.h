//=====================================
//
//カメラヘッダ[Camera.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../../main.h"

#include <vector>

class BaseCameraPlugin;
/**************************************
Cameraクラス
***************************************/
class Camera
{
	friend class BaseGame;
public:
	Camera();					//コンストラクタ
	virtual ~Camera();			//デストラクタ

	virtual void Update();		//更新
	virtual void Set();			//カメラ情報反映処理

	//プラグイン追加処理
	virtual void AddPlugin(BaseCameraPlugin* plugin);
	virtual void RemovePlugin(BaseCameraPlugin* plugin);

	//メインカメラセット、ゲット処理
	static void SetMainCamera(Camera* camera);
	static Camera* MainCamera();

	//与えたワールド座標をスクリーン座標に変換する関数
	void Projection(D3DXVECTOR3& out, const D3DXVECTOR3& pos);

	//与えたスクリーン座標をワールド座標に変換する関数
	void UnProjection(D3DXVECTOR3& out, const D3DXVECTOR3& pos, float z);

	//ビュー行列取得処理
	D3DXMATRIX GetViewMtx();

	//ビュー逆行列取得処理
	D3DXMATRIX GetInverseViewMtx();

	//プロジェクション行列取得処理
	D3DXMATRIX GetProjectionMtx();

protected:
	//SRT情報
	Transform transform;

	//注視点
	D3DXVECTOR3 target;

	//視点、注視点、上方向（作業用領域）
	D3DXVECTOR3 eyeWork;
	D3DXVECTOR3 targetWork;
	D3DXVECTOR3 upWork;

	//視野角、アスペクト比、ニア値、ファー値
	float viewAngle;
	float viewAspect;
	float viewNear;
	float viewFar;

	//ビュー、プロジェクション行列、ビューポート行列
	D3DXMATRIX view, projection, viewport;
	D3DXMATRIX VPV;

	//ビュー、プロジェクション、ビューポート逆行列
	D3DXMATRIX invView, invProjection, intViewport;
	D3DXMATRIX invVPV;

	//プラグインリスト
	std::vector<BaseCameraPlugin*> pluginList;
	
	//ゲームにセットされるカメラのインスタンス
	static Camera* mainCamera;

public:
	//カメラを揺らすプラグイン
	class ShakePlugin;
	
};

/**************************************
カメラプラグイン基底クラス
***************************************/
class BaseCameraPlugin
{
public:
	virtual void Update() = 0;
	virtual void Apply(Camera& camera) = 0;
};

#endif