#pragma once
#include <Windows.h>

/// <summary>
/// ウィンドウズアプリケーション
/// </summary>
class WinApp
{
public: 
	// ウィンドウサイズ
	static const int window_width = 1280;	// 横幅
	static const int window_height = 720;	// 縦幅
	static const wchar_t windowClassName[];

	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void CreateGameWindow();


	void TerminateGameWindow();

	bool ProcessMessage();


	HWND GetHwnd() { return hwnd; }

	HINSTANCE GetInstance() { return w.hInstance; }

private: 
	// Window関連
	HWND hwnd = nullptr;	// ウィンドウハンドル
	WNDCLASSEX w{};			// ウィンドウクラス
};

