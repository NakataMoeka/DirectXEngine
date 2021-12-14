#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <d3dx12.h>
#include <cstdlib>
#include "WinApp.h"

class DirectXCommon {
public:
	void Initialize(WinApp* winapp);
	void preDraw();
	void postDraw();
	ID3D12Device* Getdev() { return dev.Get(); }

	ID3D12GraphicsCommandList* GetCmdList() { return cmdList.Get(); }
private:
	void InitializeDevice();//デバイス初期化
	void InitializeCommand();//コマンド初期化
	void InitializeSwapchain();//スワップチェーン
	void InitializeRenderTargetView();//レンダーターゲット
	void InitializeDepthBuffer();//深度バッファ
	void InitializeFance();//フェンス生成

private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	WinApp* winapp = nullptr;
	ComPtr<ID3D12Device> dev;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<IDXGISwapChain4> swapchain;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	ComPtr<ID3D12Fence> fence;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;//これをメンバ変数にしないと例外スローが起こるので注意!!
	UINT64 fenceVal = 0;
};
