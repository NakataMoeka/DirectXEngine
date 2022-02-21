#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "Material.h"
#include <vector>

class Mesh
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス

	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT3 normal; // 法線ベクトル
		XMFLOAT2 uv;  // uv座標
	};

public: // 静的メンバ関数

	static void StaticInitialize(ID3D12Device* dev);

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* dev;

public: // メンバ関数

	const std::string& GetName() { return name; }

	void SetName(const std::string& name);

	void AddVertex(const VertexPosNormalUv& vertex);

	void AddIndex(unsigned short index);

	inline size_t GetVertexCount() { return vertices.size(); }

	Material* GetMaterial() { return material; }

	void SetMaterial(Material* material);

	void CreateBuffers();

	const D3D12_VERTEX_BUFFER_VIEW& GetVBView() { return vbView; }

	const D3D12_INDEX_BUFFER_VIEW& GetIBView() { return ibView; }

	void Draw(ID3D12GraphicsCommandList* cmdList);


private: // メンバ変数
	// 名前
	std::string name;
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	// 頂点データ配列
	std::vector<VertexPosNormalUv> vertices;
	// 頂点インデックス配列
	std::vector<unsigned short> indices;
	// マテリアル
	Material* material = nullptr;
};

