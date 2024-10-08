#include "ResultScene.h"
#include "application/GlovalVariables/GlobalVariables.h"
#include "application/Scene/Title/Title.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	 //BGM,SE
	gameAudio_ = GameAudio::GetInstance();
	gameAudio_->ResultBGM(true);
	title_ = false;

	// postEffect
	isTransition_ = true;
	isTransition2_ = false;
	postProcess_ = std::make_unique<PostProcess>();
	postProcess_->Initialize();
	postProcess_->SetEffect(BloomDissolve);
	texHandleMask_ = TextureManager::Load("resources/noise9.png");
	texHandleA_ = TextureManager::Load("resources/A.png");
	texHandleSpace_ = TextureManager::Load("resources/space.png");

	postProcess_->SetMaskTexture(texHandleMask_);
	param_.threshold = 1.0f;
	param_.stepWidth = 0.001f;
	param_.sigma = 0.005f;
	param_.lightStrength = 0.3f;
	param_.bloomThreshold = 0.3f;
	postProcess_->SetBloomDissolveParam(param_);

	spriteA_.reset(Sprite::Create(texHandleA_, { 1100.0f,600.0f }));

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
	timeScores_ = GlobalVariables::GetInstance()->GetTimes();

	playerTex = TextureManager::GetInstance()->Load("resources/Player/jumpPlayer.png");

	//テクスチャの初期化
	for (int i = 0; i < 10; i++)
	{
		numberTexture[i] = TextureManager::Load("resources/Timer/num_" + std::to_string(i) + ".png");
	}
	uint32_t index1;	//一桁目の取得
	uint32_t index10;   //二桁目の取得
	uint32_t index100;  //二桁目の取得

	uint32_t indexNum = 0;
	std::sort(timeScores_.begin(), timeScores_.end());
	if (timeScores_.size() > 9) {
		timeScores_.erase(timeScores_.begin() + 9, timeScores_.end());
	}
	for (auto itr = timeScores_.begin(); itr != timeScores_.end(); itr++, ++indexNum) {
		index1 = (*itr) % 10;
		index10 = ((*itr) / 10) % 10;
		index100 = ((*itr) / 100) % 10;
		if (indexNum == 0) {
			std::unique_ptr<Sprite> timerSprite1;// = std::make_unique<Sprite>();
			timerSprite1.reset(Sprite::Create(numberTexture[0], { 393.0f,indexNum * 64.0f+162.0f }));
			timerSprite1->SetTexHandle(numberTexture[index1]);
			timerSprite1->SetTextureSize({ 128.0f,128.0f });
			timerSprite1->SetAnchorPoint({0.5f,0.0f});
			timerSprites1_.push_back(std::move(timerSprite1));

			std::unique_ptr<Sprite> timerSprite10;// = std::make_unique<Sprite>();
			timerSprite10.reset(Sprite::Create(numberTexture[0], { 329.0f,indexNum * 64.0f + 162.0f }));
			timerSprite10->SetTexHandle(numberTexture[index10]);
			timerSprite10->SetTextureSize({ 128.0f,128.0f });
			timerSprite10->SetAnchorPoint({ 0.5f,0.0f });
			timerSprites10_.push_back(std::move(timerSprite10));

			std::unique_ptr<Sprite> timerSprite100;// = std::make_unique<Sprite>();
			timerSprite100.reset(Sprite::Create(numberTexture[0], { 265.0f,indexNum * 64.0f + 162.0f }));
			timerSprite100->SetTexHandle(numberTexture[index100]);
			timerSprite100->SetTextureSize({ 128.0f,128.0f });
			timerSprite100->SetAnchorPoint({ 0.5f,0.0f });
			timerSprites100_.push_back(std::move(timerSprite100));
		}
		else if (indexNum == 1) {
			std::unique_ptr<Sprite> timerSprite1;// = std::make_unique<Sprite>();
			timerSprite1.reset(Sprite::Create(numberTexture[0], { 393.0f,indexNum * 128.0f + 162.0f }));
			timerSprite1->SetTexHandle(numberTexture[index1]);
			timerSprite1->SetTextureSize({ 96.0f,96.0f });
			timerSprite1->SetAnchorPoint({ 0.5f,0.0f });

			timerSprites1_.push_back(std::move(timerSprite1));

			std::unique_ptr<Sprite> timerSprite10;// = std::make_unique<Sprite>();
			timerSprite10.reset(Sprite::Create(numberTexture[0], { 329.0f,indexNum * 128.0f + 162.0f }));
			timerSprite10->SetTexHandle(numberTexture[index10]);
			timerSprite10->SetTextureSize({ 96.0f,96.0f });
			timerSprite10->SetAnchorPoint({ 0.5f,0.0f });
			timerSprites10_.push_back(std::move(timerSprite10));

			std::unique_ptr<Sprite> timerSprite100;// = std::make_unique<Sprite>();
			timerSprite100.reset(Sprite::Create(numberTexture[0], { 265.0f,indexNum * 128.0f + 162.0f }));
			timerSprite100->SetTexHandle(numberTexture[index100]);
			timerSprite100->SetTextureSize({ 96.0f,96.0f });
			timerSprite100->SetAnchorPoint({ 0.5f,0.0f });
			timerSprites100_.push_back(std::move(timerSprite100));
		}
		else if (indexNum == 2) {
			std::unique_ptr<Sprite> timerSprite1;// = std::make_unique<Sprite>();
			timerSprite1.reset(Sprite::Create(numberTexture[0], { 393.0f,128+ ((indexNum -1) * 96.0f) + 162.0f }));
			timerSprite1->SetTexHandle(numberTexture[index1]);
			timerSprite1->SetAnchorPoint({ 0.5f,0.0f });
			timerSprites1_.push_back(std::move(timerSprite1));

			std::unique_ptr<Sprite> timerSprite10;// = std::make_unique<Sprite>();
			timerSprite10.reset(Sprite::Create(numberTexture[0], { 329,128 + ((indexNum - 1) * 96.0f) + 162.0f }));
			timerSprite10->SetTexHandle(numberTexture[index10]);
			timerSprite10->SetAnchorPoint({ 0.5f,0.0f });
			timerSprites10_.push_back(std::move(timerSprite10));

			std::unique_ptr<Sprite> timerSprite100;// = std::make_unique<Sprite>();
			timerSprite100.reset(Sprite::Create(numberTexture[0], { 265.0f,128 + ((indexNum - 1) * 96.0f) + 162.0f }));
			timerSprite100->SetTexHandle(numberTexture[index100]);
			timerSprite100->SetAnchorPoint({ 0.5f,0.0f });
			timerSprites100_.push_back(std::move(timerSprite100));
		}
		else {
			std::unique_ptr<Sprite> timerSprite1;// = std::make_unique<Sprite>();
			timerSprite1.reset(Sprite::Create(numberTexture[0], { 717.0f, ((indexNum - 2) * 64.0f) + 116.0f }));
			timerSprite1->SetTexHandle(numberTexture[index1]);
			timerSprite1->SetAnchorPoint({ 0.5f,0.0f });
			timerSprites1_.push_back(std::move(timerSprite1));

			std::unique_ptr<Sprite> timerSprite10;// = std::make_unique<Sprite>();
			timerSprite10.reset(Sprite::Create(numberTexture[0], { 653.0f, ((indexNum - 2) * 64.0f) + 116.0f }));
			timerSprite10->SetTexHandle(numberTexture[index10]);
			timerSprite10->SetAnchorPoint({ 0.5f,0.0f });
			timerSprites10_.push_back(std::move(timerSprite10));

			std::unique_ptr<Sprite> timerSprite100;// = std::make_unique<Sprite>();
			timerSprite100.reset(Sprite::Create(numberTexture[0], { 589.0f,  ((indexNum - 2) * 64.0f) + 116.0f }));
			timerSprite100->SetTexHandle(numberTexture[index100]);
			timerSprite100->SetAnchorPoint({ 0.5f,0.0f });
			timerSprites100_.push_back(std::move(timerSprite100));
		}

	}
	camera_.Initialize();
	
	camera_.translate = {-2.3f , 1.6f , -10.4f};
	camera_.rotate = { 0.0f , 0.0f , 0.0f };
	
	skydoem_ = std::make_unique<Skydome>();
	skydoem_->Init();

	player_ = std::make_unique<Player>();
	player_->Init({ 0.0f,0.0f,0.0f });
	player_->ModelChange("Player/jumpPlayer.gltf");
	player_->ModelTextureChange(playerTex);
	player_->SetCamera(&camera_);
	player_->SetIsFall(true);
	ground_ = std::make_unique<Ground>();
	ground_->Init({ 0.0f,0.0f,0.0f });
	Loader::LoadJsonFile("resources/stage", "result", player_.get(), ground_.get(), obstacles_, walls_);

	texHandleWhite_ = TextureManager::Load("resources/Title/white.png");
	spriteMask_.reset(Sprite::Create(texHandleWhite_));

	if (Input::GetInstance()->GetJoystickState())
	{
		spriteA_->SetTexHandle(texHandleA_);
	}
}

void ResultScene::Update()
{


	skydoem_->Update();
	Transition();

	Transition2();
			   
	ground_->Update();
	player_->ResultUpdate();
	
	if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)||Input::GetInstance()->PressedKey(DIK_SPACE)) {
		gameAudio_->ResultBGM(false);
		gameAudio_->ClickSE();
		//gameAudio_->ResultBGM(false);
		isTransition2_ = true;
	}

	for (auto itr = obstacles_.begin(); itr != obstacles_.end(); itr++) {
		(*itr)->Update();
	}
	for (auto itr = walls_.begin(); itr != walls_.end(); itr++) {
		(*itr)->ResultUpdate();
	}

	camera_.UpdateMatrix();

	if (Input::GetInstance()->GetJoystickState())
	{
		spriteA_->SetTexHandle(texHandleA_);
	}
	else
	{
		spriteA_->SetTexHandle(texHandleSpace_);
	}

}

void ResultScene::Draw()
{
	
	spriteMask_->Draw();
	postProcess_->Draw();


	if (!isTransition2_ && param_.threshold <= 0.2f) {

		for (auto itr = obstacles_.begin(); itr != obstacles_.end(); itr++) {
			(*itr)->Draw(camera_);
		}
		for (auto itr = walls_.begin(); itr != walls_.end(); itr++) {
			(*itr)->Draw(camera_);
		}

		for (auto itr = timerSprites1_.begin(); itr != timerSprites1_.end(); itr++) {
			(*itr)->Draw();
		}
		for (auto itr = timerSprites10_.begin(); itr != timerSprites10_.end(); itr++) {
			(*itr)->Draw();
		}
		for (auto itr = timerSprites100_.begin(); itr != timerSprites100_.end(); itr++) {
			(*itr)->Draw();
		}

		spriteA_->Draw();
	}
}

void ResultScene::PostProcessDraw()
{
	postProcess_->PreDraw();

	skydoem_->Draw(camera_);
	ground_->Draw(camera_);
	player_->Draw(camera_);


	postProcess_->PostDraw();
}


void ResultScene::Transition()
{
	if (isTransition_) {
		postProcess_->SetBloomDissolveParam(param_);
		param_.threshold -= 0.02f;
		if (param_.threshold <= 0.0f) {
			isTransition_ = false;
			param_.threshold = 0.0f;
		}
	}

}

void ResultScene::Transition2()
{
	if (isTransition2_) {
		postProcess_->SetBloomDissolveParam(param_);
		param_.threshold += 0.02f;
		if (param_.threshold >= 1.2f) {
			isTransition_ = false;
			title_ = true;
			GameManager::GetInstance()->ChangeScene("TITLE");
		}
	}

}
