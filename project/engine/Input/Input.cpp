#include "Input.h"
#include <iostream>
const float Input::DEADZONE_THRESHOLD = 0.5f;
Input* Input::GetInstance() {

	static Input instance;
	return &instance;
}

void Input::Initialize() {

	HRESULT result{};
	// InputDeviceの作成
	result = DirectInput8Create(WinApp::GetInstance()->GetWc().hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&Input::GetInstance()->directInput, nullptr);

	assert(SUCCEEDED(result));
	// キーボードデバイスの作成
	result = Input::GetInstance()->directInput->CreateDevice(GUID_SysKeyboard, &Input::GetInstance()->keyboard, NULL);
	assert(SUCCEEDED(result));

	// 入力データ形式のセット
	result = Input::GetInstance()->keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));

	// 排制御レベルのセット
	result = Input::GetInstance()->keyboard->SetCooperativeLevel(
		WinApp::GetInstance()->GetHwnd(),
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);



}

void Input::Update() {

	memcpy(Input::GetInstance()->preKeys, Input::GetInstance()->keys, 256);
	Input::GetInstance()->keyboard->Acquire();
	Input::GetInstance()->keyboard->GetDeviceState(sizeof(Input::GetInstance()->keys), Input::GetInstance()->keys);
	Input::GetInstance()->preState_ = Input::GetInstance()->state_;
	GetJoystickState();
}

bool Input::PushKey(uint8_t keyNum) {

	if (Input::GetInstance()->keys[keyNum] == 0x80)
	{
		return true;
	}
	return false;

}

bool Input::PressedKey(uint32_t keyNum) {

	if (Input::GetInstance()->keys[keyNum] == 0x80 && Input::GetInstance()->preKeys[keyNum] == 0x00)
	{
		return true;
	}
	return false;
}

bool Input::GetJoystickState()
{
	DWORD dwResult = XInputGetState(0, &Input::GetInstance()->state_);
	if (dwResult == ERROR_SUCCESS) {
		return true;
	}

	return false;
}

bool Input::GetJoystickState(XINPUT_STATE& out)
{
	DWORD dwResult = XInputGetState(0, &out);
	if (dwResult == ERROR_SUCCESS) {
		return true;
	}

	return false;
}

float Input::JoyStickParmLX(float num)
{
	// スティックの入力値を取得
	float lx = (float)state_.Gamepad.sThumbLX / SHRT_MAX;

	// デッドゾーンの適用
	if (fabs(lx) < DEADZONE_THRESHOLD) lx = 0.0f;


	lx = lx * num;

	return lx;
}

float Input::JoyStickParmLY(float num)
{
	float ly = (float)state_.Gamepad.sThumbLY / SHRT_MAX;

	// デッドゾーンの適用
	if (fabs(ly) < DEADZONE_THRESHOLD) ly = 0.0f;

	ly = ly * num;

	return ly;
}

float Input::JoyStickParmRX(float num)
{
	float rx = (float)state_.Gamepad.sThumbRX / SHRT_MAX;

	if (fabs(rx) < DEADZONE_THRESHOLD) rx = 0.0f;
	rx = rx * num;

	return rx;
}
float Input::JoyStickParmRY(float num)
{
	float ry = (float)state_.Gamepad.sThumbRY / SHRT_MAX;

	if (fabs(ry) < DEADZONE_THRESHOLD) ry = 0.0f;
	ry = ry * num;

	return ry;
}

bool Input::PressedButton(WORD button)
{

	bool flag = false;

	if (Input::GetInstance()->preState_.Gamepad.wButtons & button)
	{
		flag = true;
	}

	if (!flag && state_.Gamepad.wButtons & button)
	{
		return true;
	}

	return false;
}
