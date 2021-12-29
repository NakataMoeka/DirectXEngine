#include "GameScene.h"
#include <cassert>

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(object3d);
	safe_delete(sprite);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	object3d = Object3d::Create();
	model = model->Create("bullet");
	object3d->LinkModel(model);

	object3d->Update();

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	Sprite::LoadTexture(1, L"Resources/bullet.png");

	sprite = Sprite::CreateSprite(1, { 10,10 });

	//audio->SoundPlayWave("Resources/ショット.wav",true);
	
}

void GameScene::Update()
{
	XMFLOAT3 playerPosition = object3d->GetPosition();
	if (input->PushKey(DIK_D)) { playerPosition.x += 1.0f; }
	if (input->PushKey(DIK_A)) { playerPosition.x -= 1.0f; }
	object3d->SetPosition(playerPosition);
	object3d->Update();
}

void GameScene::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	object3d->Draw();
	Object3d::PostDraw();


	sprite->PreDraw(dxCommon->GetCmdList());
	sprite->Draw();
	char str[256];

	debugText.Print("abc", 20, 20, 1.0f);
	debugText.DrawAll(dxCommon->GetCmdList());
	sprite->PostDraw();
}
