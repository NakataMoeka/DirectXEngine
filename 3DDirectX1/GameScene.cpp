#include "GameScene.h"
#include <cassert>

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(object3d);
	safe_delete(object3d2);
	safe_delete(model);
	safe_delete(model2);
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

	object3d2 = Object3d::Create();
	model2 = model->Create("duck");
	object3d2->LinkModel(model2);
	object3d2->SetRotation({0,180,0});
	object3d2->SetPosition({ 0,-80,0 });
	object3d2->Update();

	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// �f�o�b�O�e�L�X�g������
	debugText.Initialize(debugTextTexNumber);

	Sprite::LoadTexture(1, L"Resources/Arrow.png");

	sprite = Sprite::CreateSprite(1, { 10,10 });

	audio->SoundPlayWave("Resources/�V���b�g.wav",true);
	
}

void GameScene::Update()
{
	XMFLOAT3 playerPosition = object3d->GetPosition();
	if (input->PushKey(DIK_D)) { playerPosition.x += 1.0f; }
	if (input->PushKey(DIK_A)) { playerPosition.x -= 1.0f; }

	if (input->PushMouse(0)) {
		debugText.Print("www", 100, 100, 5.0f);
	}

	object3d->SetPosition(playerPosition);
	object3d->Update();
	object3d2->Update();
	
}

void GameScene::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	object3d->Draw();
	object3d2->Draw();
	Object3d::PostDraw();


	sprite->PreDraw(dxCommon->GetCmdList());
	sprite->Draw();
	char str[256];

	debugText.Print("MauseLeftClick", 100, 20, 3.0f);
	debugText.DrawAll(dxCommon->GetCmdList());
	sprite->PostDraw();
}
