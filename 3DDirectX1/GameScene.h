#pragma once


#include"SafeDelete.h"
#include <DirectXMath.h>
#include"input.h"
#include"Sprite.h"
#include"Audio.h"
#include"DirectXCommon.h"
#include"DebugText.h"
#include"Object3d.h"
#include"Model.h"
#include"Camera.h"

class GameScene 
{
private: 
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public: // メンバ関数


	GameScene();


	~GameScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);


	void Update();

	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;
	Sprite* sprite = nullptr;
	Object3d* object3d = nullptr;
	Model*	model = nullptr;
	Camera* camera = nullptr;
	const int debugTextTexNumber = 0;
};


