#include"Audio.h"
#include<fstream>
#include<cassert>

bool Audio::Initialize()
{
	HRESULT result;

	// XAudio�G���W���̃C���X�^���X�𐶐�
	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if FAILED(result) {
		assert(0);
		return false;
	}

	// �}�X�^�[�{�C�X�𐶐�
	result = xAudio2->CreateMasteringVoice(&masterVoice);
	if FAILED(result) {
		assert(0);
		return false;
	}

	return true;
}



void Audio::SoundPlayWave(const char* filename,bool LOOP)
{
	HRESULT result;

	//1.�t�@�C���ǂݍ���

	std::ifstream file;

	file.open(filename, std::ios_base::binary);

	assert(file.is_open());

	//2.wav�f�[�^�ǂݍ���

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

	//3.Wave�t�@�C�������
	file.close();


	WAVEFORMATEX wfex{};
	// �g�`�t�H�[�}�b�g�̐ݒ�
	memcpy(&wfex, &format.fmt, sizeof(format.fmt));
	wfex.wBitsPerSample = format.fmt.nBlockAlign * 8 / format.fmt.nChannels;

	
	result = xAudio2->CreateSourceVoice(&pSourceVoice, &wfex, 0, 2.0f, &voiceCallback);
	assert(SUCCEEDED(result));


	XAUDIO2_BUFFER buf{};
	buf.pAudioData = (BYTE*)pBuffer;
	buf.pContext = pBuffer;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	buf.AudioBytes = data.size;

	if (LOOP == TRUE)
	{
		buf.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	// �g�`�f�[�^�̍Đ�
	result = pSourceVoice->SubmitSourceBuffer(&buf);
	if FAILED(result) {
		delete[] pBuffer;
		assert(0);
		return;
	}

	result = pSourceVoice->Start();
	if FAILED(result) {
		delete[] pBuffer;
		assert(0);
		return;
	}
}

void Audio::StopWave()
{
	pSourceVoice->Stop();
}
