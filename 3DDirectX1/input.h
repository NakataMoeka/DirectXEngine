#pragma once

#include <Windows.h>
#include <wrl.h>
#include "WinApp.h"
#define DIRECTINPUT_VERSION     0x0800          // DirectInput�̃o�[�W�����w��
#include <dinput.h>


class Input
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: 
	void Initialize(WinApp* winapp);

	void update();

	bool PushKey(BYTE keyNumber);

	bool TriggerKey(BYTE keyNumber);

private: // �����o�ϐ�
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};
	WinApp* winapp = nullptr;
};
