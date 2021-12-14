#include <Windows.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <vector>
#include <string>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#include <math.h>
#include<DirectXTex.h>
#include<wrl.h>
#include<stdio.h>
#include<xaudio2.h>
#include<fstream>
#include"input.h"
#include"WinApp.h"
#include"Sprite.h"
#include"Audio.h"
#include"DirectXCommon.h"
#include"DebugText.h"
#include"Object3d.h"
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#pragma comment(lib, "xaudio2.lib")
using namespace DirectX;
using namespace Microsoft::WRL;







#pragma region サウンド関数など
//チャンクヘッダ
struct ChunkHeader
{
	char id[4];			//チャンク毎のID
	int32_t size;		//チャンクサイズ
};

//RIFFヘッダチャンク
struct RiffHeader
{
	ChunkHeader chunk;		//"RIFF"
	char type[4];			//"WAVE"
};

//FMIチャンク
struct FormatChunk
{
	ChunkHeader chunk;		//"fmt"
	WAVEFORMATEX fmt;		//波形フォーマット
};

//音声データ
struct SoundData
{
	//波形フォーマット
	WAVEFORMATEX wfex;
	//バッファの先頭アドレス
	BYTE* pBuffer;
	//バッファのサイズ
	unsigned int bufferSize;
};

SoundData SoundLoadWave(const char* filename)
{
	HRESULT result;

	//1.ファイル読み込み

	std::ifstream file;

	file.open(filename, std::ios_base::binary);

	assert(file.is_open());

	//2.wavデータ読み込み

	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));

	if (strncmp(riff.chunk.id, "RIFF", 4) != 0)
	{
		assert(0);
	}
	if (strncmp(riff.type, "WAVE", 4) != 0)
	{
		assert(0);
	}

	FormatChunk format = {};

	file.read((char*)&format, sizeof(ChunkHeader));
	if (strncmp(format.chunk.id, "fmt ", 4) != 0)
	{
		assert(0);
	}


	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);

	ChunkHeader data;
	file.read((char*)&data, sizeof(data));

	if (strncmp(data.id, "JUNK ", 4) == 0)
	{

		file.seekg(data.size, std::ios_base::cur);

		file.read((char*)&data, sizeof(data));
	}

	if (strncmp(data.id, "data ", 4) != 0)
	{
		assert(0);
	}


	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);

	//3.Waveファイルを閉じる
	file.close();

	//4.読み込んだデータをreturn

	SoundData soundData = {};

	soundData.wfex = format.fmt;
	soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	soundData.bufferSize = data.size;

	return soundData;
}

void SoundUnload(SoundData* soundData)
{

	delete[] soundData->pBuffer;

	soundData->pBuffer = 0;
	soundData->bufferSize = 0;
	soundData->wfex = {};
}

void SoundPlayWave(IXAudio2* xAudio2, const SoundData& soundData)
{
	HRESULT result;


	IXAudio2SourceVoice* pSourceVoice = nullptr;
	result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
	assert(SUCCEEDED(result));


	XAUDIO2_BUFFER buf{};
	buf.pAudioData = soundData.pBuffer;
	buf.AudioBytes = soundData.bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;


	result = pSourceVoice->SubmitSourceBuffer(&buf);
	result = pSourceVoice->Start();

}

#pragma endregion 



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
	object3d->Update();

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

	
#pragma endregion

	const int constantBufferNum = 128;



#pragma region 


#pragma endregion


#pragma endregion


#pragma region ポジションなど

	/*XMMATRIX matWorld;
	matWorld = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 1000.0f
	);*/


	//ビュー変換行列
	XMMATRIX matView;
	XMFLOAT3 up(0, 1, 0);
	XMFLOAT3 eye(0, 0, -100);
	XMFLOAT3 target(0, 0, 0);
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
	float angle = 0.0f;

	XMMATRIX matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)WinApp::window_width/ WinApp::window_height,
		0.1f, 1000.0f
	);

	//スケーリング
	//int wallAlive[OBJECT_NUM];
	//for (int i = 0; i < _countof(wall); i++) {
	//	wallAlive[i] = { 1 };
	//}

	int gflag = 0;

	int gbflag = 0;



	char str[100];

	int frame = 0;
	int playerSpeed = 2;
	const float radius1 = 4.0f;
	const float radius2 = 4.0f;

#pragma endregion

while (true) {
if (winapp->ProcessMessage()) { break; }


		input->update();

	
		
	
		
				dxcommon->preDraw();
// ４．描画コマンドここから

#pragma region 描画
	
				Object3d::PreDraw(dxcommon->GetCmdList());
				object3d->Draw();
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

