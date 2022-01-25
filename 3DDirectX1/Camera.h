#pragma once

#include <DirectXMath.h>

class Camera{
private:// �G�C���A�X

	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	static const XMFLOAT3& GetEye() { return eye; }

	static void SetEye(XMFLOAT3 eye);

	static const XMFLOAT3& GetTarget() { return target; }

	static void SetTarget(XMFLOAT3 target);

	static const XMMATRIX& GetView() { return matView;}

	static const XMMATRIX& GetProjection() { return matProjection;}

	static void CameraMoveVector(XMFLOAT3 move);

	static void InitializeCamera(int window_width, int window_height);

	static void UpdateViewMatrix();
	// �r���[�s��
	static XMMATRIX matView;
	// �ˉe�s��
	static XMMATRIX matProjection;
	// ���_���W
	static XMFLOAT3 eye;
	// �����_���W
	static XMFLOAT3 target;
	// ������x�N�g��
	static XMFLOAT3 up;
};