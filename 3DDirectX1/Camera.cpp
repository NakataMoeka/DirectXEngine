#include "Camera.h"

using namespace DirectX;

Camera::Camera(int window_width, int window_height)
{
	aspectRatio = (float)window_width / window_height;
	
	//�r���[�s��̌v�Z
	UpdateViewMatrix();

	// �ˉe�s��̌v�Z
	UpdateProjectionMatrix();

	// �r���[�v���W�F�N�V�����̍���
	matViewProjection = matView * matProjection;
}

void Camera::Update()
{
}

void Camera::UpdateViewMatrix()
{
}

void Camera::UpdateProjectionMatrix()
{
}

void Camera::MoveEyeVector(const XMFLOAT3& move)
{
}

void Camera::MoveEyeVector(const XMVECTOR& move)
{
}

void Camera::MoveVector(const XMFLOAT3& move)
{
}

void Camera::MoveVector(const XMVECTOR& move)
{
}
