
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

	const int debugTextTexNumber = 0;
	Sprite* sprite = nullptr;
	sprite = new Sprite(1, { 0 ,0 }, { 0 ,0 }, { 1,1,1,1 }, { 0,0 }, false, false);
	DebugText debugText;

	Object3d* object3d = nullptr;
	object3d = new Object3d();

	Object3d* object3d2 = nullptr;
	object3d2 = new Object3d();

	Model* model = nullptr;
	model = new Model();

	Model* model2 = nullptr;
	model2 = new Model();

	if (!Sprite::StaticInitialize(dxcommon->Getdev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	// 3Dオブジェクト静的初期化
	if (!Object3d::StaticInitialize(dxcommon->Getdev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}

	// 3Dオブジェクト生成
	object3d = Object3d::Create();
	model = model->Create("bullet");
	object3d->LinkModel(model);
	
	object3d->Update();

	object3d2 = Object3d::Create();
	model2 = model2->Create("bullet");
	object3d2->LinkModel(model2);
	

	object3d2->SetPosition({10.0f, 10.0f, 10.0f});
	
	object3d2->Update();

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return 1;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	Sprite::LoadTexture(1, L"Resources/bullet.png");

	sprite = Sprite::CreateSprite(1, { 10,10 });

	ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice;
	
	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	result = xAudio2->CreateMasteringVoice(&masterVoice);
	audio->SoundPlayWave("Resources/決定、ボタン押下14.wav",true);

	Input* input = nullptr;
	input = new Input();
	input->Initialize(winapp);

	







while (true) {
if (winapp->ProcessMessage()) { break; }


		input->update();
		
		if (input->TriggerKey(DIK_SPACE)) {
			audio->StopWave();
		}

// ４．描画コマンドここから

#pragma region 描画
				dxcommon->preDraw();
				Object3d::PreDraw(dxcommon->GetCmdList());
				object3d->Draw();
				object3d2->Draw();
				Object3d::PostDraw();

	
					sprite->PreDraw(dxcommon->GetCmdList());
					sprite->Draw();
					char str[256];

					debugText.Print("abc", 20, 20, 1.0f);
					debugText.DrawAll(dxcommon->GetCmdList());
					sprite->PostDraw();
	
#pragma endregion
			
		// ４．描画コマンドここまで
		dxcommon->postDraw();
		// DirectX毎フレーム処理　ここまで
	}
	 //ウィンドウクラスを登録解除
	winapp->TerminateGameWindow();
	delete input;
	delete winapp;
	delete dxcommon;
	delete sprite;
	delete object3d;

	xAudio2.Reset();

	return 0;
}

