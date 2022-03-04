#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>

#include "Model.h"
#include "Shape.h"
#include "Camera.h"
class Object3d
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
	
	// �p�C�v���C���Z�b�g
	struct PipelineSet
	{
		// ���[�g�V�O�l�`��
		ComPtr<ID3D12RootSignature> rootsignature;
		// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
		ComPtr<ID3D12PipelineState> pipelinestate;
	};

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataB0
	{
		//XMFLOAT4 color;	// �F (RGBA)
		XMMATRIX mat;	// �R�c�ϊ��s��
	};



	static void StaticInitialize(ID3D12Device* dev, Camera* camera= nullptr);

	static void CreateGraphicsPipeline();

	static void SetCamera(Camera* camera) {
		Object3d::camera = camera;
	}

	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	static void PostDraw();

	static Object3d* Create(Model* model);

	//static Object3d* CreateShape(Shape* shape);

	bool Initialize();

	void Update();

	void Draw();

	const XMFLOAT3& GetPosition() { return position; }

	void SetPosition(XMFLOAT3 position) { this->position = position; }

	const XMFLOAT3& GetRotation() { return rotation; }

	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }

	void SetScale(XMFLOAT3 scale) { this->scale = scale; }

	// ���f���Ƃ̘A�g
	void SetModel(Model* model) { this->model = model; };

	//void SetShape(Shape* shape) { this->shape = shape; };


	void SetBillboard(bool isBillboard) { this->isBillboard = isBillboard; }

private:

	// �f�o�C�X
	static ID3D12Device* dev;

	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;

	// �p�C�v���C��
	static PipelineSet pipelineSet;

	ComPtr<ID3D12Resource> constBuffB0; // �萔�o�b�t�@

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
	Object3d* parent = nullptr;

	Model* model = nullptr;
	Shape* shape = nullptr;
	// �J����
	static Camera* camera;
	// �r���{�[�h
	bool isBillboard = false;
};

