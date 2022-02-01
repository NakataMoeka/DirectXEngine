#pragma once

#include <Windows.h>
#include <wrl.h>
#include "WinApp.h"
#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定
#include <dinput.h>


class Input
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: 
	void Initialize(WinApp* winapp);
	void InitializeMouse(WinApp* winapp);
	
	void update();
	void updateMouse();
	bool PushKey(BYTE keyNumber);
	bool TriggerKey(BYTE keyNumber);
	bool PushMouse(int MouseNumber);
	bool TriggerMouse(int MouseNumber);
private: // メンバ変数
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};

	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE mouse = { 0 };
	DIMOUSESTATE oldMouse = { 0 };

	WinApp* winapp = nullptr;
};
