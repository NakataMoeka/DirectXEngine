
#include"input.h"
#include"WinApp.h"
#include"Sprite.h"
#include"Audio.h"
#include"DirectXCommon.h"
#include"DebugText.h"
#include"Object3d.h"
#include"Model.h"

#include "GameScene.h"

#pragma region 初期化
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	HRESULT result;
	//ウィンドウの生成
	WinApp* winapp = nullptr;
	winapp = new WinApp();
	winapp->CreateGameWindow();
	DirectXCommon* dxcommon = nullptr;
	dxcommon = new DirectXCommon();
	dxcommon->Initialize(winapp);
	
	Audio* audio = nullptr;
	audio = new Audio();
	if (!audio->Initialize()) {
		assert(0);
		return 1;
	}

	Sprite* sprite = nullptr;

	if (!Sprite::StaticInitialize(dxcommon->Getdev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}

	// 3Dオブジェクト静的初期化
	if (!Object3d::StaticInitialize(dxcommon->Getdev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}

	Input* input = nullptr;
	input = new Input();
	input->Initialize(winapp);

	GameScene* gameScene = nullptr;
	gameScene = new GameScene();
	gameScene->Initialize(dxcommon, input, audio);

while (true) {
if (winapp->ProcessMessage()) { break; }


		input->update();
		
		gameScene->Update();

		dxcommon->preDraw();
		gameScene->Draw();
		dxcommon->postDraw();
		// DirectX毎フレーム処理　ここまで
	}
	 //ウィンドウクラスを登録解除
	winapp->TerminateGameWindow();
	// 各種解放
	safe_delete(gameScene);
	safe_delete(audio);
	safe_delete(input);
	safe_delete(dxcommon);
	safe_delete(winapp);

	return 0;
}

