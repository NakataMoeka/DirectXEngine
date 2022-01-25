#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "Model.h"
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


	// 定数バッファ用データ構造体
	struct ConstBufferDataB0
	{
		//XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
	};



	static bool StaticInitialize(ID3D12Device* dev, int window_width, int window_height);

	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	static void PostDraw();

	static Object3d* Create();

	static const XMFLOAT3& GetEye() { return eye; }

	static void SetEye(XMFLOAT3 eye);

	static const XMFLOAT3& GetTarget() { return target; }

	static void SetTarget(XMFLOAT3 target);

	static void CameraMoveVector(XMFLOAT3 move);

	bool Initialize();

	void Update();

	void Draw();

	const XMFLOAT3& GetPosition() { return position; }

	void SetPosition(XMFLOAT3 position) { this->position = position; }

	// モデルとの連携
	void LinkModel(Model* model) { this->model = model; };

private:

	

	static void InitializeCamera(int window_width, int window_height);

	static bool InitializeGraphicsPipeline();

	static void UpdateViewMatrix();

	// デバイス
	static ID3D12Device* dev;

	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;

	// ビュー行列
	static XMMATRIX matView;
	// 射影行列
	static XMMATRIX matProjection;
	// 視点座標
	static XMFLOAT3 eye;
	// 注視点座標
	static XMFLOAT3 target;
	// 上方向ベクトル
	static XMFLOAT3 up;


	ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ

	// 色
	XMFLOAT4 color = { 1,1,1,1 };
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

	Camera*camera=nullptr;
};

