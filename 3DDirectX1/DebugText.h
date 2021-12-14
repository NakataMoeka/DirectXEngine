#pragma once
#include "Sprite.h"
#include <Windows.h>
#include <string>
class DebugText
{
public: // �萔�̐錾    
	static const int maxCharCount = 256;    // �ő啶����
	static const int fontWidth = 9;         // �t�H���g�摜��1�������̉���
	static const int fontHeight = 18;       // �t�H���g�摜��1�������̏c��
	static const int fontLineCount = 14;    // �t�H���g�摜��1�s���̕�����

public: // �����o�֐�


	DebugText();
	~DebugText();

	void Initialize(UINT texnumber);

	void Print(const std::string& text, float x, float y, float scale);

	void DrawAll(ID3D12GraphicsCommandList* cmdList);

private: // �����o�ϐ�     
	// �X�v���C�g�f�[�^�̔z��
	Sprite* sprite[maxCharCount] = {};
	// �X�v���C�g�f�[�^�z��̓Y�����ԍ�
	int spriteIndex = 0;
};

