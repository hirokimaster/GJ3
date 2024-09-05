#pragma once
#include"engine/Base/WinApp/WinApp.h"
#include <cassert>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")
#pragma comment(lib,"dinput8.lib")

class Input {
public:

	static Input* GetInstance();

	static void Initialize();

	static void Update();

	bool PushKey(uint8_t keyNum);

	bool PressedKey(uint32_t keyNum);

	static bool GetJoystickState();

	bool GetJoystickState(XINPUT_STATE& out);
	float JoyStickParmLX(float num);
	float JoyStickParmLY(float num);
	float JoyStickParmRX(float num);
	float JoyStickParmRY(float num);
	bool PressedButton(WORD button);

private:

	IDirectInput8* directInput = nullptr;
	IDirectInputDevice8* keyboard = nullptr;

	BYTE keys[256] = {};
	BYTE preKeys[256] = {};

	bool isInitialize = false;

	XINPUT_STATE state_{};
	XINPUT_STATE preState_{};

	// デッドゾーンの閾値を定義
	const static float DEADZONE_THRESHOLD;
private:

	Input() = default;
	~Input() = default;
	Input(const Input&) = delete;
	const Input& operator=(const Input&) = delete;
};