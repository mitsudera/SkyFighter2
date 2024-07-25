//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 
//
//=============================================================================
#pragma once
#include "CameraComponent.h"
#include "World.h"
#include "GameEngine.h"
#include "Renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VIEW_ANGLE		(XMConvertToRadians(45.0f))						// ビュー平面の視野角
#define	VIEW_ASPECT		(16.0f / 9.0f)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(0.1f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(10000.0f)										// ビュー平面のFarZ値

#define	VALUE_MOVE_CAMERA	(2.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(XM_PI * 0.01f)								// カメラの回転量

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int				g_ViewPortType = TYPE_VIEWPORT;


CameraComponent::CameraComponent()
{


}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::Init(void)
{
	PrimitiveComponent::Init();

	SetName("Camera");

	this->SetTransform(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1), XMVECTOR());
	this->at = { 0.0f, 0.0f, 0.0f };
	this->up = { 0.0f, 1.0f, 0.0f };

	// 視点と注視点の距離を計算
	float vx, vz;
	XMFLOAT3 location = GetTransform()->GetLocation();
	vx = location.x - this->at.x;
	vz = location.z - this->at.z;
	this->len = sqrtf(vx * vx + vz * vz);



	// 仮
	this->aspect = VIEW_ASPECT;	// アスペクト比 
	this->angle = VIEW_ANGLE;	// 視野角
	this->nearZ = VIEW_NEAR_Z;
	this->farZ = VIEW_FAR_Z;



	// ビューポートタイプの初期化
	//SetViewPort(g_ViewPortType);
}

void CameraComponent::Update(void)
{
	PrimitiveComponent::Update();

	if (!this->editorCamera) return;

	SetCameraPos();
	SetCamera();
}

void CameraComponent::Draw(void)
{
	PrimitiveComponent::Draw();

	if (!this->editorCamera) return;

	SetViewPort(g_ViewPortType);
	//SetCameraAT(XMFLOAT3(0, 0, 1));
}

void CameraComponent::Uninit(void)
{
	PrimitiveComponent::Uninit();

	if (!this->editorCamera) return;

}

void CameraComponent::BeginPlay(void)
{
	PrimitiveComponent::BeginPlay();
	SetViewPort(g_ViewPortType);

}

void CameraComponent::UpdatePlay(void)
{
	PrimitiveComponent::UpdatePlay();
	SetCameraPos();
	SetCamera();

}

void CameraComponent::EndPlay(void)
{
	PrimitiveComponent::EndPlay();

}


//=============================================================================
// カメラの更新
//=============================================================================
void CameraComponent::SetCamera(void)
{
	Renderer* renderer = GetWorld()->GetGameEngine()->GetRenderer();
	// ビューマトリックス設定@
	XMMATRIX mtxView;

	GetWorldMatrix();

	XMFLOAT3 LocalPos = GetTransform()->GetLocation();
	XMFLOAT3 OwnerPos = GetOwner()->GetTransform()->GetLocation();
	XMFLOAT3 Pos;
	Pos.x = OwnerPos.x + LocalPos.x;
	Pos.y = OwnerPos.y + LocalPos.y;
	Pos.z = OwnerPos.z + LocalPos.z;

	XMFLOAT3 At = this->at;
	XMFLOAT3 Up  = XMFLOAT3(0,1,0);
	//mtxView = XMMatrixLookAtLH(XMLoadFloat3(&pos), XMLoadFloat3(&this->at), XMLoadFloat3(&this->up));
	mtxView = XMMatrixLookAtLH(XMLoadFloat3(&GetWorldLocation()), XMLoadFloat3(&At), XMLoadFloat3(&Up));
	renderer->SetViewMatrix(&mtxView);
	XMStoreFloat4x4(&this->mtxView, mtxView);

	XMMATRIX mtxInvView;
	mtxInvView = XMMatrixInverse(nullptr, mtxView);
	XMStoreFloat4x4(&this->mtxInvView, mtxInvView);


	// プロジェクションマトリックス設定
	XMMATRIX mtxProjection;
	mtxProjection = XMMatrixPerspectiveFovLH(VIEW_ANGLE, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z);

	renderer->SetProjectionMatrix(&mtxProjection);
	XMStoreFloat4x4(&this->mtxProjection, mtxProjection);

	renderer->SetShaderCamera(this->GetTransform()->GetLocation());
}

void CameraComponent::GetViewPort(XMFLOAT2& size, XMFLOAT2& pos)
{
	size = GetWorld()->GetGameEngine()->GetWindowSize();// カメラが表示するスクリーンのサイズをセット
	pos = XMFLOAT2(0, 0);
}

//=============================================================================
// ビューポートの設定
//=============================================================================
void CameraComponent::SetViewPort(int m_type)
{
	Renderer* renderer = GetWorld()->GetGameEngine()->GetRenderer();
	ID3D11DeviceContext *ImmediateContext = renderer->GetDeviceContext();
	D3D11_VIEWPORT vp;

	g_ViewPortType = m_type;

	XMFLOAT2 screen = GetWorld()->GetGameEngine()->GetWindowSize();


	// ビューポート設定
	switch (g_ViewPortType)
	{
	case TYPE_FULL_SCREEN:
		vp.Width = (FLOAT)screen.x;
		vp.Height = (FLOAT)screen.y;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		break;

	case TYPE_LEFT_HALF_SCREEN:
		vp.Width = (FLOAT)screen.x / 2;
		vp.Height = (FLOAT)screen.y;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		break;

	case TYPE_RIGHT_HALF_SCREEN:
		vp.Width = (FLOAT)screen.x / 2;
		vp.Height = (FLOAT)screen.y;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = (FLOAT)screen.x / 2;
		vp.TopLeftY = 0;
		break;

	case TYPE_UP_HALF_SCREEN:
		vp.Width = (FLOAT)screen.x;
		vp.Height = (FLOAT)screen.y / 2;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		break;

	case TYPE_DOWN_HALF_SCREEN:
		vp.Width = (FLOAT)screen.x;
		vp.Height = (FLOAT)screen.y / 2;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = (FLOAT)screen.y / 2;
		break;
	case TYPE_VIEWPORT:
		vp.Width = (FLOAT)screen.x * 0.6f;
		vp.Height = (FLOAT)screen.y * 0.6f + GetSystemMetrics(SM_CYCAPTION);
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = (FLOAT)screen.x * 0.2f;
		vp.TopLeftY = (FLOAT)screen.y * 0.1f;
		break;
	}
	ImmediateContext->RSSetViewports(1, &vp);

}


int CameraComponent::GetViewPortType(void)
{
	return g_ViewPortType;
}



// カメラの視点と注視点をセット
void CameraComponent::SetCameraAT(XMFLOAT3 pos)
{
	// カメラの注視点を引数の座標にしてみる
	this->at = pos;

	XMFLOAT3 camLoc = GetTransform()->GetLocation();
	XMFLOAT3 camRot = GetTransform()->GetRotation();
	// カメラの視点をカメラのY軸回転に対応させている
	camLoc.x = this->at.x - sinf(camRot.y) * this->len;
	camLoc.z = this->at.z - cosf(camRot.y) * this->len;
	
	GetTransform()->SetLocation(camLoc);
}

//=============================================================================
// カメラの位置のみをセット
//=============================================================================
void CameraComponent::SetCameraPos(void)
{
	XMMATRIX mtxWorld, mtxRot, mtxTranslate;
	// ワールドマトリックスの初期化
	mtxWorld = XMMatrixIdentity();

	// 移動を反映
	mtxTranslate = XMMatrixTranslation(0.0f, 0.0f, 1.0f);	//前ベクトル
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);


	XMFLOAT3 rot = GetTransform()->GetRotation();
	// 回転を反映
	mtxRot = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	XMFLOAT3 result = XMFLOAT3(mtxWorld.r[3].m128_f32[0], mtxWorld.r[3].m128_f32[1], mtxWorld.r[3].m128_f32[2]);

	XMFLOAT3 LocalPos = GetTransform()->GetLocation();
	XMFLOAT3 OwnerPos = GetOwner()->GetTransform()->GetLocation();
	XMFLOAT3 Pos = GetWorldLocation();


	//ワールドに変換し代入
	this->at = XMFLOAT3(Pos.x + result.x, Pos.y + result.y, Pos.z + result.z);
}

void CameraComponent::SetEditorCamera(void)
{
	this->editorCamera = true;
}

//=============================================================================
// カメラのx軸回転　マウス上下
//=============================================================================
void CameraComponent::AddCameraYaw(float value)
{
	XMFLOAT3 rot = GetTransform()->GetRotation();
	rot.x += value;


	if (rot.x > XM_PI / 3.0f)
	{
		rot.x = XM_PI / 3.0f;
	}
	if (rot.x < -XM_PI / 3.0f)
	{
		rot.x = -XM_PI / 3.0f;
	}

	GetTransform()->SetRotation(rot);

}

//=============================================================================
// カメラのy軸回転　マウス左右
//=============================================================================
void CameraComponent::AddCameraPitch(float value)
{
	XMFLOAT3 rot = GetTransform()->GetRotation();
	rot.y += value;

	if (rot.y > XM_PI)
	{
		rot.y -= XM_PI * 2.0f;
	}
	if (rot.y < -XM_PI)
	{
		rot.y += XM_PI * 2.0f;
	}

	GetTransform()->SetRotation(rot);

}


XMFLOAT4X4 CameraComponent::CameraInverseViewMatrix(void) const {
	return this->mtxInvView;
}

XMFLOAT4X4 CameraComponent::CameraViewMatrix(void) const {
	return this->mtxView;
}
