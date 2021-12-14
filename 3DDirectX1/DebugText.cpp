#include "DebugText.h"

DebugText::DebugText()
{

}

DebugText::~DebugText()
{
	for (int i = 0; i < _countof(sprite); i++) {
		delete sprite[i];
	}
}


void DebugText::Initialize(UINT texnumber)
{
	// �S�ẴX�v���C�g�f�[�^�ɂ���
	for (int i = 0; i < _countof(sprite); i++)
	{
		// �X�v���C�g�𐶐�����
		sprite[i] = Sprite::CreateSprite(texnumber, { 0,0 });
	}
}

void DebugText::Print( const std::string& text, float x, float y, float scale = 1.0f)
{
	// �S�Ă̕����ɂ���
	for (int i = 0; i < text.size(); i++)
	{
		// �ő啶��������
		if (spriteIndex >= maxCharCount) {
			break;
		}

		// 1�������o��(��ASCII�R�[�h�ł������藧���Ȃ�)
		const unsigned char& character = text[i];

		// ASCII�R�[�h��2�i����΂����ԍ����v�Z
		int fontIndex = character - 32;
		if (character >= 0x7f) {
			fontIndex = 0;
		}

		int fontIndexY = fontIndex / fontLineCount;
		int fontIndexX = fontIndex % fontLineCount;

		// ���W�v�Z
		sprite[spriteIndex]->SetPosition({ x + fontWidth * scale * i, y});
		sprite[spriteIndex]->SetTextureRect({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight }, { (float)fontWidth ,(float)fontHeight });
		sprite[spriteIndex]->SetSize({ fontWidth * scale, fontHeight * scale });
		// �������P�i�߂�
		spriteIndex++;
	}
}

// �܂Ƃ߂ĕ`��
void DebugText::DrawAll(ID3D12GraphicsCommandList* cmdList)
{
	// �S�Ă̕����̃X�v���C�g�ɂ���
	for (int i = 0; i < spriteIndex; i++)
	{
		// �X�v���C�g�`��
		sprite[i]->Draw();
	}

	spriteIndex = 0;
}