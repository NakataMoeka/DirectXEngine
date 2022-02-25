//#include "Shape.h"
//#include <d3dcompiler.h>
//#include <DirectXTex.h>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <vector>
//#pragma comment(lib, "d3dcompiler.lib")
//using namespace DirectX;
//using namespace Microsoft::WRL;
//
//using namespace std;
//
//ID3D12Device* Shape::dev = nullptr;
//UINT Shape::descriptorHandleIncrementSize = 0;
//
//bool Shape::StaticInitialize(ID3D12Device* dev)
//{
//	// nullptrチェック
//	assert(dev);
//
//	Shape::dev = dev;
//
//	return true;
//}
//bool Shape::InitializeDescriptorHeap()
//{
//	HRESULT result = S_FALSE;
//	//設定構造体
//	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
//	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
//	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
//	descHeapDesc.NumDescriptors = 1;
//
//	result = dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));
//
//	if (FAILED(result)) {
//		assert(0);
//		return false;
//	}
//	descriptorHandleIncrementSize = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
//
//	return true;
//}
//Shape* Shape::CreateSquare(const float width, const float height, const float depth) {
//	// 3Dオブジェクトのインスタンスを生成
//	Shape* square = new Shape();
//	if (square == nullptr)
//	{
//		return nullptr;
//	}
//
//	// 初期化
//	if (!square->InitializeSquare(width, height, depth))
//	{
//		delete square;
//		assert(0);
//		return nullptr;
//	}
//
//	return square;
//}
//void Shape::Square(const float width, const float height, const float depth)
//{
//	//前
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { -width / 2,-height / 2,-depth / 2 };
//	vertices[vertices.size() - 1].uv = { 0.0f,1.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { -width / 2,height / 2,-depth / 2 };
//	vertices[vertices.size() - 1].uv = { 0.0f,0.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { width / 2,-height / 2,-depth / 2 };
//	vertices[vertices.size() - 1].uv = { 1.0f,1.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { width / 2,height / 2,-depth / 2 };
//	vertices[vertices.size() - 1].uv = { 1.0f,0.0f };
//
//	//後ろ
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { -width / 2,-height / 2,depth / 2 };
//	vertices[vertices.size() - 1].uv = { 0.0f,1.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { -width / 2,height / 2,depth / 2 };
//	vertices[vertices.size() - 1].uv = { 0.0f,0.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { width / 2,-height / 2,depth / 2 };
//	vertices[vertices.size() - 1].uv = { 1.0f,1.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { width / 2,height / 2,depth / 2 };
//	vertices[vertices.size() - 1].uv = { 1.0f,0.0f };
//
//	//左
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { -width / 2,-height / 2,-depth / 2 };
//	vertices[vertices.size() - 1].uv = { 0.0f,1.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { -width / 2,-height / 2,depth / 2 };
//	vertices[vertices.size() - 1].uv = { 0.0f,0.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { -width / 2,height / 2,-depth / 2 };
//	vertices[vertices.size() - 1].uv = { 1.0f,1.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { -width / 2,height / 2,depth / 2 };
//	vertices[vertices.size() - 1].uv = { 1.0f,0.0f };
//
//
//	//右
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { width / 2,-height / 2,-depth / 2 };
//	vertices[vertices.size() - 1].uv = { 0.0f,1.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { width / 2,-height / 2,depth / 2 };
//	vertices[vertices.size() - 1].uv = { 0.0f,0.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { width / 2,height / 2,-depth / 2 };
//	vertices[vertices.size() - 1].uv = { 1.0f,1.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { width / 2,height / 2,depth / 2 };
//	vertices[vertices.size() - 1].uv = { 1.0f,0.0f };
//
//
//	//上
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { -width / 2,-height / 2,depth / 2 };
//	vertices[vertices.size() - 1].uv = { 0.0f,1.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { -width / 2,-height / 2,-depth / 2 };
//	vertices[vertices.size() - 1].uv = { 0.0f,0.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { width / 2,-height / 2,depth / 2 };
//	vertices[vertices.size() - 1].uv = { 1.0f,1.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { width / 2,-height / 2,-depth / 2 };
//	vertices[vertices.size() - 1].uv = { 1.0f,0.0f };
//
//	//下
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { -width / 2,height / 2,depth / 2 };
//	vertices[vertices.size() - 1].uv = { 0.0f,1.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { -width / 2,height / 2,-depth / 2 };
//	vertices[vertices.size() - 1].uv = { 0.0f,0.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { width / 2,height / 2,depth / 2 };
//	vertices[vertices.size() - 1].uv = { 1.0f,1.0f };
//
//	vertices.emplace_back(new VertexPosNormalUv);
//	vertices[vertices.size() - 1].pos = { width / 2,height / 2,-depth / 2 };
//	vertices[vertices.size() - 1].uv = { 1.0f,0.0f };
//	//前
//	indices.emplace_back(new unsigned short(0)), indices.emplace_back(new unsigned short(1)), indices.emplace_back(new unsigned short(2));
//	indices.emplace_back(new unsigned short(2)), indices.emplace_back(new unsigned short(1)), indices.emplace_back(new unsigned short(3));
//	//後ろ
//	indices.emplace_back(new unsigned short(5)), indices.emplace_back(new unsigned short(4)), indices.emplace_back(new unsigned short(6));
//	indices.emplace_back(new unsigned short(5)), indices.emplace_back(new unsigned short(6)), indices.emplace_back(new unsigned short(7));
//	//左
//	indices.emplace_back(new unsigned short(8)), indices.emplace_back(new unsigned short(9)), indices.emplace_back(new unsigned short(10));
//	indices.emplace_back(new unsigned short(10)), indices.emplace_back(new unsigned short(9)), indices.emplace_back(new unsigned short(11));
//	//右
//	indices.emplace_back(new unsigned short(13)), indices.emplace_back(new unsigned short(12)), indices.emplace_back(new unsigned short(14));
//	indices.emplace_back(new unsigned short(13)), indices.emplace_back(new unsigned short(14)), indices.emplace_back(new unsigned short(15));
//	//上
//	indices.emplace_back(new unsigned short(16)), indices.emplace_back(new unsigned short(17)), indices.emplace_back(new unsigned short(18));
//	indices.emplace_back(new unsigned short(18)), indices.emplace_back(new unsigned short(17)), indices.emplace_back(new unsigned short(19));
//	//下
//	indices.emplace_back(new unsigned short(21)), indices.emplace_back(new unsigned short(20)), indices.emplace_back(new unsigned short(22));
//	indices.emplace_back(new unsigned short(21)), indices.emplace_back(new unsigned short(22)), indices.emplace_back(new unsigned short(23));
//
//	HRESULT result = S_FALSE;
//	for (size_t i = 0; i < indices.size() / 3; i++)
//	{//三角形1つごとに計算していく
//		//三角形のインデックスを取り出して、一時的な変数に入れる
//		unsigned short indices0 = indices[i * 3 + 0];
//		unsigned short indices1 = indices[i * 3 + 1];
//		unsigned short indices2 = indices[i * 3 + 2];
//		//三角形を構成する頂点座標をベクトルに代入
//		XMVECTOR p0 = XMLoadFloat3(&vertices[indices0].pos);
//		XMVECTOR p1 = XMLoadFloat3(&vertices[indices1].pos);
//		XMVECTOR p2 = XMLoadFloat3(&vertices[indices2].pos);
//		//p0→p1ベクトル、p0→p2ベクトルを計算（ベクトルの減算）
//		XMVECTOR v1 = XMVectorSubtract(p1, p0);
//		XMVECTOR v2 = XMVectorSubtract(p2, p0);
//
//		//外積は両方から垂直なベクトル
//		XMVECTOR normal;
//		normal = XMVector3Cross(v1, v2);
//		//正規化（長さを１にする）
//		normal = XMVector3Normalize(normal);
//		//求めた法線を頂点データに代入
//		XMStoreFloat3(&vertices[indices0].normal, normal);
//		XMStoreFloat3(&vertices[indices1].normal, normal);
//		XMStoreFloat3(&vertices[indices2].normal, normal);
//	}
//
//
//	// 頂点データ全体のサイズ = 頂点データ一つ分のサイズ * 頂点データの要素数
//	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUv) * vertices.size());
//	//インデックスデータの全サイズ
//	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());
//
//
//	result = dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr, IID_PPV_ARGS(&vertBuff)
//	);
//
//	result = dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr, IID_PPV_ARGS(&indexBuff)
//	);
//
//	// 頂点バッファへのデータ転送
//	VertexPosNormalUv* vertMap = nullptr;
//	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
//	if (SUCCEEDED(result)) {
//		std::copy(vertices.begin(), vertices.end(), vertMap);
//		vertBuff->Unmap(0, nullptr);
//	}
//	if (FAILED(result)) {
//		assert(0);
//		return;
//	}
//
//	// インデックスバッファへのデータ転送
//	unsigned short* indexMap = nullptr;
//	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
//	if (SUCCEEDED(result)) {
//		//全インデックスに対して
//		std::copy(indices.begin(), indices.end(), indexMap);
//		//つながりを解除
//		indexBuff->Unmap(0, nullptr);
//	}
//
//
//
//	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
//	vbView.SizeInBytes = sizeVB;
//	vbView.StrideInBytes = sizeof(VertexPosNormalUv);
//
//	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
//	ibView.Format = DXGI_FORMAT_R16_UINT;
//	ibView.SizeInBytes = sizeIB;
//
//}
//bool Shape::LoadTexture()
//{
//	HRESULT result = S_FALSE;
//
//	// WICテクスチャのロード
//	TexMetadata metadata{};
//	ScratchImage scratchImg{};
//
//	result = LoadFromWICFile(
//		L"Resources/white.png", WIC_FLAGS_NONE,
//		&metadata, scratchImg);
//	if (FAILED(result)) {
//		return result;
//	}
//
//	const Image* img = scratchImg.GetImage(0, 0, 0); // 生データ抽出
//
//	// リソース設定
//	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
//		metadata.format,
//		metadata.width,
//		(UINT)metadata.height,
//		(UINT16)metadata.arraySize,
//		(UINT16)metadata.mipLevels
//	);
//
//	// テクスチャ用バッファの生成
//	result = dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
//		D3D12_HEAP_FLAG_NONE,
//		&texresDesc,
//		D3D12_RESOURCE_STATE_GENERIC_READ, // テクスチャ用指定
//		nullptr,
//		IID_PPV_ARGS(&texbuff));
//	if (FAILED(result)) {
//		return result;
//	}
//
//	// テクスチャバッファにデータ転送
//	result = texbuff->WriteToSubresource(
//		0,
//		nullptr, // 全領域へコピー
//		img->pixels,    // 元データアドレス
//		(UINT)img->rowPitch,  // 1ラインサイズ
//		(UINT)img->slicePitch // 1枚サイズ
//	);
//	if (FAILED(result)) {
//		return result;
//	}
//
//	// シェーダリソースビュー作成
//	cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);
//	gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);
//
//	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // 設定構造体
//	D3D12_RESOURCE_DESC resDesc = texbuff->GetDesc();
//
//	srvDesc.Format = resDesc.Format;
//	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
//	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
//	srvDesc.Texture2D.MipLevels = 1;
//
//	dev->CreateShaderResourceView(texbuff.Get(), //ビューと関連付けるバッファ
//		&srvDesc, //テクスチャ設定情報
//		cpuDescHandleSRV
//	);
//
//	return true;
//}
//
//bool Shape::InitializeSquare(const float width, const float height, const float depth)
//{
//
//	// nullptrチェック
//	assert(dev);
//
//	HRESULT result;
//
//	result = dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB1) + 0xff) & ~0xff),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr, IID_PPV_ARGS(&constBuffB1));
//
//	Square(width, height, depth);
//	InitializeDescriptorHeap();
//	LoadTexture();
//	ConstBufferDataB1* constMap1 = nullptr;
//	result = constBuffB1->Map(0, nullptr, (void**)&constMap1);
//	constMap1->ambient = material.ambient;
//	constMap1->diffuse = material.diffuse;
//	constMap1->specular = material.specular;
//	constMap1->alpha = material.alpha;
//	constBuffB1->Unmap(0, nullptr);
//
//
//	return true;
//}
//void Shape::Draw(ID3D12GraphicsCommandList* cmdList)
//{
//	// nullptrチェック
//	assert(dev);
//
//
//	// 頂点バッファの設定
//	cmdList->IASetVertexBuffers(0, 1, &vbView);
//	// インデックスバッファの設定
//	cmdList->IASetIndexBuffer(&ibView);
//
//	// デスクリプタヒープの配列
//	ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
//	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
//
//	// 定数バッファビューをセット
//	cmdList->SetGraphicsRootConstantBufferView(1, constBuffB1->GetGPUVirtualAddress());
//	//// シェーダリソースビューをセット
//	cmdList->SetGraphicsRootDescriptorTable(2, gpuDescHandleSRV);
//
//	// 描画コマンド
//	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);
//}
