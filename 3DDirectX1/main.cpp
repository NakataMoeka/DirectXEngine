#include"WinApp.h"
#include"Audio.h"
#include"DirectXCommon.h"
#include "GameScene.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	HRESULT result;
	

	WinApp* winapp = nullptr;
	DirectXCommon* dxcommon = nullptr;
	Audio* audio = nullptr;
	Input* input = nullptr;
	GameScene* gameScene = nullptr;

	//ウィンドウの生成
	winapp = new WinApp();
	winapp->CreateGameWindow();
	//DirectXの初期化
	dxcommon = new DirectXCommon();
	dxcommon->Initialize(winapp);
	
	//汎用機能の初期化
	audio = new Audio();
	if (!audio->Initialize()) {
		assert(0);
		return 1;
	}

	if (!Sprite::StaticInitialize(dxcommon->Getdev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}

	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxcommon->Getdev());
	
	input = new Input();
	input->Initialize(winapp);
	input->InitializeMouse(winapp);
	//ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize(dxcommon, input, audio);

//ループ
	while (true) 
	{
		if (winapp->ProcessMessage()) { break; }
			//入力関連の毎フレーム処理
			input->update();
			input->updateMouse();
			//ゲームシーンの毎フレーム処理
			gameScene->Update();
			//描画
			dxcommon->preDraw();
			gameScene->Draw();
			dxcommon->postDraw();
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

