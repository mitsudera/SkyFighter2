//=============================================================================
//
// �J�������� [camera.h]
// Author : 
//
//=============================================================================
#pragma once
#include "PrimitiveComponent.h"

//*****************************************************************************
// �}�N����`
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
// �v���g�^�C�v�錾
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

	void GetViewPort(XMFLOAT2& size, XMFLOAT2& pos);	// �r���[�|�[�g�̎擾
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

	XMFLOAT4X4			mtxView;		// �r���[�}�g���b�N�X
	XMFLOAT4X4			mtxInvView;		// �r���[�}�g���b�N�X
	XMFLOAT4X4			mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X

	XMFLOAT3			at;				// �J�����̒����_
	XMFLOAT3			up;				// �J�����̏�����x�N�g��

	float				angle;			// ����p
	float				aspect;			// �A�X�y�N�g��
	float				len;			// �J�����̎��_�ƒ����_�̋���
	float				nearZ;			// �J�����̃N���b�s���O�ŏ��lZ
	float				farZ;			// �J�����̃N���b�s���O�ő�lZ

private:


	void SetCameraPos(void);
	bool editorCamera;

};