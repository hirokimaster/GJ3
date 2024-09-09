#include "Title.h"
#include "engine/ModelManager/ModelManager.h"
Level Title::level_ = Level::EASY;

Title::Title()
{
}

Title::~Title()
{
}

void Title::Initialize()
{
	postProcess_ = std::make_unique<PostProcess>();
	postProcess_->Initialize();
	postProcess_->SetEffect(Dissolve);
	TextureResources();
	postProcess_->SetMaskTexture(texHandleMask_);
	spriteTitle_.reset(Sprite::Create(texHandleStart_));

	param_.threshold = 0.0f;
	param_.maskColor = { 1.0f,0.0f,0.0f,1.0f };
	postProcess_->SetDissolveParam(param_);
}

void Title::Update()
{
	postProcess_->SetDissolveParam(param_);
	param_.threshold += 0.01f;
	if (param_.threshold >= 1.0f) {
		param_.threshold = 0.0f;
	}

	SelectMode();
	OptionMode();
}

void Title::Draw()
{
	postProcess_->Draw();
	spriteTitle_->Draw();
}

void Title::PostProcessDraw()
{
	postProcess_->PreDraw();

	postProcess_->PostDraw();
}

void Title::OptionMode()
{
	// オプション
	if (optionMode_) {
		spriteTitle_->SetTexHandle(texHandleLevel_);
		--optionTimer_;
		
		if (level_ == Level::EASY && optionTimer_ <= 0.0f) {
			spriteTitle_->SetTexHandle(texHandleEasy_);
			if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
				optionTimer_ = 5.0f;
				optionMode_ = false;
				spriteTitle_->SetTexHandle(texHandleStart_);
			}
		}
		else if (level_ == Level::NORMAL && optionTimer_ <= 0.0f) {
			spriteTitle_->SetTexHandle(texHandleNormal_);
			if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
				optionTimer_ = 5.0f;
				optionMode_ = false;
				spriteTitle_->SetTexHandle(texHandleStart_);
			}
		}
		else if (level_ == Level::HARD && optionTimer_ <= 0.0f) {
			spriteTitle_->SetTexHandle(texHandleHard_);
			if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
				optionTimer_ = 5.0f;
				optionMode_ = false;
				spriteTitle_->SetTexHandle(texHandleStart_);
			}
		}
	}

	// 選択
	if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_DPAD_DOWN) && level_ == Level::EASY && optionMode_) {
		level_ = Level::NORMAL;
	}
	else if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_DPAD_DOWN) && level_ == Level::NORMAL && optionMode_) {
		level_ = Level::HARD;
	}

	if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_DPAD_UP) && level_ == Level::HARD && optionMode_) {
		level_ = Level::NORMAL;
	}
	else if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_DPAD_UP) && level_ == Level::NORMAL && optionMode_) {
		level_ = Level::EASY;
	}
}

void Title::SelectMode()
{
	// 選択
	if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_DPAD_DOWN) && select_ == Select::START && !optionMode_) {
		select_ = Select::OPTION;
	}
	else if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_DPAD_DOWN) && select_ == Select::OPTION && !optionMode_) {
		select_ = Select::END;
	}

	if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_DPAD_UP) && select_ == Select::OPTION && !optionMode_) {
		select_ = Select::START;
	}
	else if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_DPAD_UP) && select_ == Select::END && !optionMode_) {
		select_ = Select::OPTION;
	}

	// 番号によって変える
	if (select_ == Select::START && !optionMode_) {
		spriteTitle_->SetTexHandle(texHandleStart_);

		// 難易度によって変える
		if (level_ == Level::EASY) {
			// ゲームシーンにいく
			if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
				GameManager::GetInstance()->ChangeScene("GAME");
			}
		}
		else if (level_ == Level::NORMAL) {
			// ゲームシーンにいく
			if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
				GameManager::GetInstance()->ChangeScene("GAME");
			}
		}
		else if (level_ == Level::HARD) {
			// ゲームシーンにいく
			if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
				GameManager::GetInstance()->ChangeScene("GAME");
			}
		}
		
	}
	else if (select_ == Select::OPTION && !optionMode_) {
		spriteTitle_->SetTexHandle(texHandleOp_);
		// オプションにいく
		if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
			optionMode_ = true;
		}
	}
	else if (select_ == Select::END && !optionMode_) {
		spriteTitle_->SetTexHandle(texHandleEnd_);
	}
}

void Title::TextureResources()
{
	texHandleTitle_ = TextureManager::Load("resources/Title/title.png");
	texHandleStart_ = TextureManager::Load("resources/Title/start.png");
	texHandleOp_ = TextureManager::Load("resources/Title/op.png");
	texHandleEnd_ = TextureManager::Load("resources/Title/end.png");
	texHandleLevel_ = TextureManager::Load("resources/Title/level.png");
	texHandleEasy_ = TextureManager::Load("resources/Title/easy.png");
	texHandleNormal_ = TextureManager::Load("resources/Title/normal.png");
	texHandleHard_ = TextureManager::Load("resources/Title/hard.png");
	texHandleMask_ = TextureManager::Load("resources/noise1.png");
}
