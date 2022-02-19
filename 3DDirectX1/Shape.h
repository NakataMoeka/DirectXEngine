#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "Camera.h"
/// <summary>
/// �}�`���f��
/// </summary>
class Shape
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Shape();

	void Init(ID3D12Device* dev);
public://�}�`���f��

	static bool StaticInitialize(ID3D12Device* device, Camera* camera);

	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static Shape* Create();

	static void CreateTriangularPyramid(const float width, const float height);
	
	static void CreateRect(const float width, const float height);

	static void CreateCircle(const float r, const int num);

	static void CreateSquare(const float width, const float height, const float depth);

	static void CreateCylinder(int division, int prizmHeight, int radius);

	static bool LoadTexture();

	void Update(XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 matRot, XMFLOAT4 color);

	void Draw(XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 matRot, XMFLOAT4 color);

private:
	static ID3D12Device* dev;					//�f�o�C�X

	ComPtr<ID3D12Resource> constBuff; // �萔�o�b�t�@
	// �F
	XMFLOAT4 color = { 1,0,0,1 };
	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	// �e�I�u�W�F�N�g
	Shape* parent = nullptr;
};


