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
	safe_delete(particleMan);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);
	// �p�[�e�B�N���}�l�[�W������
	particleMan = ParticleManager::Create(dxCommon->Getdev(), camera);

	model = model->Create("bullet");
	model2 = model2->Create("duck");
	object3d = Object3d::Create(model);
	object3d2 = Object3d::Create(model2);
	
	//object3d2->SetRotation({ 0,180,0 });
	//object3d2->SetPosition({ 0,0,0 });
	//object3d->Update();

<<<<<<< HEAD
	object3d2->Update();
	//����������
=======
	//object3d2->Update();

>>>>>>> 改造中
	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// �f�o�b�O�e�L�X�g������
	debugText.Initialize(debugTextTexNumber);

	Sprite::LoadTexture(1, L"Resources/Arrow.png");

	sprite = Sprite::CreateSprite(1, { 10,10 });

	//audio->SoundPlayWave("Resources/�V���b�g.wav",true);
	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(20.0f);
}

void GameScene::Update()
{
	//XMFLOAT3 playerPosition
	if (input->PushKey(DIK_D)) { playerPosition.x += 0.5f; }
	if (input->PushKey(DIK_A)) { playerPosition.x -= 0.5f; }

	if (input->PushMouse(0)) {
		debugText.Print("www", 100, 100, 5.0f);
	}
	// �p�[�e�B�N������
	//CreateParticles();
	camera->Update();
	particleMan->Update();
	/*object3d->SetPosition(playerPosition);*/
/*	object3d->Update();
	object3d2->Update()*/;
	
}

void GameScene::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	object3d->Draw(playerPosition, { 1,1,1 }, {0,0,0});
	object3d2->Draw({0,0,0}, { 1,1,1 }, { 0,180,0 });
	Object3d::PostDraw();


	sprite->PreDraw(dxCommon->GetCmdList());
	sprite->Draw();
	char str[256];

	debugText.Print("MauseLeftClick", 100, 20, 3.0f);
	debugText.Print("Move:AD", 600, 20, 3.0f);
	debugText.DrawAll(dxCommon->GetCmdList());
	sprite->PostDraw();
}
void GameScene::CreateParticles()
{
	for (int i = 0; i < 10; i++) {
		// X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		XMFLOAT3 acc{};
		const float rnd_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		// �ǉ�
		particleMan->Add(60, pos, vel, acc, 1.0f, 0.0f);
	}
}

