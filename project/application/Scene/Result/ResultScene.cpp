#include "ResultScene.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
}

void ResultScene::Update()
{
	// ゲームシーンにいく
	if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
		GameManager::GetInstance()->ChangeScene("TITLE");
	}
}

void ResultScene::Draw()
{
}

void ResultScene::PostProcessDraw()
{
}
