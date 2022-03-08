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
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	
	// パイプラインセット
	struct PipelineSet
	{
		// ルートシグネチャ
		ComPtr<ID3D12RootSignature> rootsignature;
		// パイプラインステートオブジェクト
		ComPtr<ID3D12PipelineState> pipelinestate;
	};

	// 定数バッファ用データ構造体
	struct ConstBufferDataB0
	{
		//a
		//XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
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

	// モデルとの連携
	void SetModel(Model* model) { this->model = model; };

	//void SetShape(Shape* shape) { this->shape = shape; };


	void SetBillboard(bool isBillboard) { this->isBillboard = isBillboard; }

private:

	// デバイス
	static ID3D12Device* dev;

	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;

	// パイプライン
	static PipelineSet pipelineSet;

	ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ

	// 色
	XMFLOAT4 color = { 1,0,0,1 };
	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	// 親オブジェクト
	Object3d* parent = nullptr;

	Model* model = nullptr;
	Shape* shape = nullptr;
	// カメラ
	static Camera* camera;
	// ビルボード
	bool isBillboard = false;
};

