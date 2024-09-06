#include "Title.h"
#include "engine/ModelManager/ModelManager.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::Initialize()
{
	texHandleTitle_ = TextureManager::Load("resources/Title/title.png");
	spriteTitle_.reset(Sprite::Create(texHandleTitle_));
}

void Title::Update()
{

	// ステージ番号選択

	if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_DPAD_UP) && selectNum_ < 2) {
		selectNum_ += 1;
	}
	else if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_DPAD_DOWN) && selectNum_ > 0) {
		selectNum_ -= 1;
	}


	if (selectNum_ == 0) {
		if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
			GameManager::GetInstance()->ChangeScene("GAME");
		}
	}
	else if (selectNum_ == 1) {

	}
	else if (selectNum_ == 2) {

	}
}

void Title::Draw()
{
	spriteTitle_->Draw();
}

void Title::PostProcessDraw()
{
}
