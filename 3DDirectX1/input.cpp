#include "input.h"

//using namespace Microsoft::WRL;
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

void Input::Initialize(WinApp* winapp)
{
	HRESULT result;
	this->winapp = winapp;
	result = DirectInput8Create(
		winapp->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);

	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);

	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);

	result = devkeyboard->SetCooperativeLevel(
		winapp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::InitializeMouse(WinApp* winapp)
{
	HRESULT result;
	//マウスデバイス生成
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	//入力データ形式のセット
	result = devMouse->SetDataFormat(&c_dfDIMouse);
	//排他制御レベルのセット
	result = devMouse->SetCooperativeLevel(winapp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::update()
{
	HRESULT result;

	result = devkeyboard->Acquire();
	memcpy(keyPre, key, sizeof(key));

	result = devkeyboard->GetDeviceState(sizeof(key), key);


}

void Input::updateMouse()
{
	HRESULT result;

	//前回のキー入力を保存
	oldMouse = mouse;
	//マウスの情報取得開始
	result = devMouse->Acquire();
	//マウスの入力情報を取得
	result = devMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouse);
}

bool Input::PushKey(BYTE keyNumber)
{
	if (key[keyNumber]) {
		return true;
	}
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	if (!keyPre[keyNumber]&&key[keyNumber]) {
		return true;
	}
	return false;
}

bool Input::PushMouse(int MouseNumber)
{
	if (mouse.rgbButtons[MouseNumber])
	{
		return true;
	}
	return false;
}

bool Input::TriggerMouse(int MouseNumber)
{
	if (mouse.rgbButtons[MouseNumber] && !oldMouse.rgbButtons[MouseNumber])
	{
		return true;
	}
	return false;
}
Input::MouseMove Input::GetMouseMove()
{
	MouseMove tmp;
	tmp.lX = mouse.lX;
	tmp.lY = mouse.lY;
	tmp.lZ = mouse.lZ;
	return tmp;
}
