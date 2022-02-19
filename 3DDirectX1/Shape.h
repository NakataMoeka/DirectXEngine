#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "Camera.h"
#include "Mesh.h"
class Shape
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
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT3 normal; // 法線ベクトル
		XMFLOAT2 uv;  // uv座標
	};

	// 定数バッファ用データ構造体
	struct ConstBufferData
	{
		XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
	};
	Shape();

	static bool StaticInitialize(ID3D12Device* device, Camera* camera);

	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	static void PostDraw();

	static Shape* Create();

	static void CreateTriangularPyramid(const float width, const float height);
	
	static void CreateRect(const float width, const float height);

	static void CreateCircle(const float r, const int num);

	static void CreateSquare(const float width, const float height, const float depth);

	static void CreateCylinder(int division, int prizmHeight, int radius);

	static bool LoadTexture();

	bool Initialize();

	static bool InitializeGraphicsPipeline();

	void Update(XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 matRot, XMFLOAT4 color);

	void Draw(XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 matRot, XMFLOAT4 color);

private:
	static ID3D12Device* dev;					//デバイス
	// デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// デスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// 頂点バッファ
	static ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	static ComPtr<ID3D12Resource> indexBuff;
	// テクスチャバッファ
	static ComPtr<ID3D12Resource> texbuff;
	// シェーダリソースビューのハンドル(CPU)
	static CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	static CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;

	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	// 頂点データ配列
	std::vector < VertexPosNormalUv> vertices;
	// 頂点インデックス配列
	// 頂点インデックス配列
	std::vector<unsigned short> indices;
	ComPtr<ID3D12Resource> constBuff; // 定数バッファ
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
	Shape* parent = nullptr;
};


