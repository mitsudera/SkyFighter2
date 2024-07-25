//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 
//
//=============================================================================
#pragma once
#include "PrimitiveComponent.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


enum VIEWPORT_TYPE
{
	TYPE_FULL_SCREEN,
	TYPE_LEFT_HALF_SCREEN,
	TYPE_RIGHT_HALF_SCREEN,
	TYPE_UP_HALF_SCREEN,
	TYPE_DOWN_HALF_SCREEN,
	TYPE_VIEWPORT,
	TYPE_NONE,

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
class CameraComponent : public PrimitiveComponent
{
public:
	CameraComponent();
	~CameraComponent();


	void SetCameraAT(XMFLOAT3 pos);

	void AddCameraYaw(float value);
	void AddCameraPitch(float value);

	XMFLOAT4X4 CameraInverseViewMatrix(void) const;
	XMFLOAT4X4 CameraViewMatrix(void) const;

	void SetEditorCamera(void);

	void GetViewPort(XMFLOAT2& size, XMFLOAT2& pos);	// ビューポートの取得
	void SetViewPort(int m_type);
	int GetViewPortType(void);

protected:
	virtual void Init(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	virtual void Uninit(void) override;
	virtual void BeginPlay(void) override;
	virtual void UpdatePlay(void) override;
	virtual void EndPlay(void) override;


private:
	void SetCamera(void);

	XMFLOAT4X4			mtxView;		// ビューマトリックス
	XMFLOAT4X4			mtxInvView;		// ビューマトリックス
	XMFLOAT4X4			mtxProjection;	// プロジェクションマトリックス

	XMFLOAT3			at;				// カメラの注視点
	XMFLOAT3			up;				// カメラの上方向ベクトル

	float				angle;			// 視野角
	float				aspect;			// アスペクト比
	float				len;			// カメラの視点と注視点の距離
	float				nearZ;			// カメラのクリッピング最小値Z
	float				farZ;			// カメラのクリッピング最大値Z

private:


	void SetCameraPos(void);
	bool editorCamera;

};