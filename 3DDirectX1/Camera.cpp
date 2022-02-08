#include "Camera.h"

using namespace DirectX;

Camera::Camera(int window_width, int window_height)
{
	aspectRatio = (float)window_width / window_height;
	
	//ビュー行列の計算
	UpdateViewMatrix();

	// 射影行列の計算
	UpdateProjectionMatrix();

	// ビュープロジェクションの合成
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
