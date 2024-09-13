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
	ModelManager::GetInstance()->LoadObjModel("ground/ground.obj");
	ModelManager::GetInstance()->LoadObjModel("skydome/skydome.obj");
	ModelManager::GetInstance()->LoadObjModel("cube.obj");
	ModelManager::GetInstance()->LoadAnimationModel("Player/player.gltf", 200);
	ModelManager::GetInstance()->LoadAnimationModel("Player/jumpPlayer.gltf", 201);
	isTransition_ = false;
	postProcess_ = std::make_unique<PostProcess>();
	postProcess_->Initialize();
	postProcess_->SetEffect(BloomDissolve);
	TextureResources();
	postProcess_->SetMaskTexture(texHandleMask_);
	spriteTitle_.reset(Sprite::Create(texHandleStart_, { 335.0f,388.0f }));
	spriteTitle2_.reset(Sprite::Create(texHandleOp_, { 335.0f,481.0f }));
	spriteTitle3_.reset(Sprite::Create(texHandleEnd_, { 335.0f,574.0f }));
	spriteTitlename_.reset(Sprite::Create(texHandleTitle_, { 288.0f,132.0f }));

	worldTransform_.Initialize();
	worldTransform_.scale = { 0.5f,0.5f,0.5f };





	spriteMask_.reset(Sprite::Create(texHandleWhite_));

	param_.stepWidth = 0.001f;
	param_.sigma = 0.005f;
	param_.lightStrength = 0.3f;
	param_.bloomThreshold = 0.3f;
	param_.threshold = 0.0f;
	postProcess_->SetBloomDissolveParam(param_);

	level_ = Level::EASY;
	select_ = Select::START;
    optionMode_ = false;
    optionTimer_ = 5.0f;


  switch (Title::GetLevel()) {
  case Level::EASY: {
	  //GlobalVariables::GetInstance()->LoadFiles();
	  break;
  }
  case Level::NORMAL: {
	  break;
  }
  case Level::HARD: {
	  break;
  }


  }

  camera_.Initialize();
  camera_.translate = { -18.0f , 96.8f , -24.8f };
  camera_.rotate = { -0.17f , 0.59f , 0.0f };


  player_ = std::make_unique<Player>();
  player_->Init({ 0.0f,100.0f,0.0f });
  player_->SetCamera(&camera_);
  ground_ = std::make_unique<Ground>();
  ground_->Init({ 0.0f,0.0f,0.0f });

  skydoem_ = std::make_unique<Skydome>();
  skydoem_->Init();
  Loader::LoadJsonFile("resources/stage", "result", player_.get(), ground_.get(), obstacles_, walls_);

 
}

void Title::Update()
{
	Transition();
	SelectMode();
	OptionMode();
	ground_->Update();
	player_->TitleUpdate();

	for (auto itr = obstacles_.begin(); itr != obstacles_.end(); itr++) {
		(*itr)->Update();
	}
	for (auto itr = walls_.begin(); itr != walls_.end(); itr++) {
		(*itr)->ResultUpdate();
	}

	skydoem_->Update();

	camera_.UpdateMatrix();

}

void Title::Draw()
{
	
	
	spriteMask_->Draw();

	postProcess_->Draw();

}

void Title::PostProcessDraw()
{

	
	
	postProcess_->PreDraw();

	
	ground_->Draw(camera_);
	player_->Draw(camera_);
	skydoem_->Draw(camera_);

	for (auto itr = obstacles_.begin(); itr != obstacles_.end(); itr++) {
		(*itr)->Draw(camera_);
	}
	for (auto itr = walls_.begin(); itr != walls_.end(); itr++) {
		(*itr)->Draw(camera_);
	}

	spriteTitlename_->Draw();
	spriteTitle_->Draw();
	spriteTitle2_->Draw();
	spriteTitle3_->Draw();

	postProcess_->PostDraw();
}

void Title::OptionMode()
{
	// オプション
	if (optionMode_) {
		spriteTitle_->SetTexHandle(texHandleEasy_);
		spriteTitle2_->SetTexHandle(texHandleNormal_);
		spriteTitle3_->SetTexHandle(texHandleHard_);

		--optionTimer_;

		
		if (level_ == Level::EASY && optionTimer_ <= 0.0f) {
			spriteTitle_->SetTexHandle(texHandleEasyR_);
			


			if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
				optionTimer_ = 5.0f;
				optionMode_ = false;
				spriteTitle_->SetTexHandle(texHandleStart_);
				spriteTitle2_->SetTexHandle(texHandleOp_);
				spriteTitle3_->SetTexHandle(texHandleEnd_);

			}
		}
		else if (level_ == Level::NORMAL && optionTimer_ <= 0.0f) {
			spriteTitle2_->SetTexHandle(texHandleNormalR_);
			if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
				optionTimer_ = 5.0f;
				optionMode_ = false;
				spriteTitle_->SetTexHandle(texHandleStart_);
				spriteTitle2_->SetTexHandle(texHandleOp_);
				spriteTitle3_->SetTexHandle(texHandleEnd_);
			}
		}
		else if (level_ == Level::HARD && optionTimer_ <= 0.0f) {
			spriteTitle3_->SetTexHandle(texHandleHardR_);
			if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
				optionTimer_ = 5.0f;
				optionMode_ = false;
				spriteTitle_->SetTexHandle(texHandleStart_);
				spriteTitle2_->SetTexHandle(texHandleOp_);
				spriteTitle3_->SetTexHandle(texHandleEnd_);
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
		spriteTitle_->SetTexHandle(texHandleStartR_);
		spriteTitle2_->SetTexHandle(texHandleOp_);
		spriteTitle3_->SetTexHandle(texHandleEnd_);

		// 難易度によって変える
		if (level_ == Level::EASY) {
			// ゲームシーンにいく
			if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
				isTransition_ = true;
			}
		}
		else if (level_ == Level::NORMAL) {
			// ゲームシーンにいく
			if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
				isTransition_ = true;
			}
		}
		else if (level_ == Level::HARD) {
			// ゲームシーンにいく
			// ゲームシーンにいく
			if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
				isTransition_ = true;
			}
		}

	}
	else if (select_ == Select::OPTION && !optionMode_) {
		spriteTitle_->SetTexHandle(texHandleStart_);
		spriteTitle2_->SetTexHandle(texHandleOpR_);
		spriteTitle3_->SetTexHandle(texHandleEnd_);
		// オプションにいく
		if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
			optionMode_ = true;
		}
	}
	else if (select_ == Select::END && !optionMode_) {
		spriteTitle_->SetTexHandle(texHandleStart_);
		spriteTitle2_->SetTexHandle(texHandleOp_);
		spriteTitle3_->SetTexHandle(texHandleEndR_);
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
	texHandleMask_ = TextureManager::Load("resources/noise9.png");
	texHandleWhite_ = TextureManager::Load("resources/Title/white.png");

	texHandleStartR_ = TextureManager::Load("resources/Title/startR.png");
	texHandleOpR_ = TextureManager::Load("resources/Title/opR.png");
	texHandleEndR_ = TextureManager::Load("resources/Title/endR.png");
	texHandleEasyR_ = TextureManager::Load("resources/Title/easyR.png");
	texHandleNormalR_ = TextureManager::Load("resources/Title/normalR.png");
	texHandleHardR_ = TextureManager::Load("resources/Title/hardR.png");
}

void Title::Transition()
{
	if (isTransition_) {
		postProcess_->SetBloomDissolveParam(param_);
		param_.threshold += 0.02f;
		if (param_.threshold >= 1.2f) {
			isTransition_ = false;
			GameManager::GetInstance()->ChangeScene("GAME");
		}
	}

}
