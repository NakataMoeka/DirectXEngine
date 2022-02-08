#pragma once


#include"SafeDelete.h"
#include <DirectXMath.h>
#include"input.h"
#include"Sprite.h"
#include"Audio.h"
#include"DirectXCommon.h"
#include"DebugText.h"
#include"Object3d.h"
#include "ParticleManager.h"
#include"Model.h"
#include "DebugCamera.h"
class GameScene 
{
private: 
// Microsoft::WRL::‚ğÈ—ª
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::‚ğÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public: // ƒƒ“ƒoŠÖ”


	GameScene();


	~GameScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);


	void Update();

	void Draw();
	void CreateParticles();
private: // ƒƒ“ƒo•Ï”
	DirectXCommon* dxCommon = nullptr;

	Input* input = nullptr;

	Audio* audio = nullptr;

	DebugText debugText;

	DebugCamera* camera = nullptr;
	ParticleManager* particleMan = nullptr;

	Sprite* sprite = nullptr;

	Object3d* object3d = nullptr;
	Model*	model = nullptr;

	Object3d* object3d2 = nullptr;
	Model* model2 = nullptr;

	const int debugTextTexNumber = 0;
};


