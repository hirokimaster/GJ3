#include "GameScene.h"
#include "engine/ModelManager/ModelManager.h"
#include "application/GlovalVariables/GlobalVariables.h"
#include "engine/Loader/Loader.h"
#include "application/Scene/Title/Title.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	// BGM,SE
	 gameAudio_ = GameAudio::GetInstance();
	 gameAudio_->GameBGM(true);

	// postEffect
	isTransition_ = true;
	postProcess_ = std::make_unique<PostProcess>();
	postProcess_->Initialize();
	postProcess_->SetEffect(BloomDissolve);
	texHandleMask_ = TextureManager::Load("resources/noise9.png");
	postProcess_->SetMaskTexture(texHandleMask_);
	param_.threshold = 1.0f;
	param_.stepWidth = 0.001f;
	param_.sigma = 0.005f;
	param_.lightStrength = 0.3f;
	param_.bloomThreshold = 0.3f;
	postProcess_->SetBloomDissolveParam(param_);

	//ModelManager::GetInstance()->LoadAnimationModel("sneakWalk.gltf");
	ModelManager::GetInstance()->LoadObjModel("ground/ground.obj");
	ModelManager::GetInstance()->LoadObjModel("skydome/skydome.obj");
	ModelManager::GetInstance()->LoadObjModel("cube.obj");
	//ModelManager::GetInstance()->LoadAnimationModel("Player/player.gltf");
	//ModelManager::GetInstance()->LoadObjModel("Player/player.obj");
	

	camera_.Initialize();

	player_ = std::make_unique<Player>();
	

	
	gameCamera_ = std::make_unique<GameCamera>();
	gameCamera_->Init();
	player_->SetCamera(&gameCamera_->GetCamera());

	ground_ = std::make_unique<Ground>();
	ground_->Init({ 0.0f,0.0f,0.0f });
	
	skydoem_ = std::make_unique<Skydome>();
	skydoem_->Init();
	
	
	collisionManager_ = std::make_unique<CollisionManager>(); // コリジョンマネージャ

	//テクスチャの初期化
	for (int i = 0; i < 10; i++)
	{
		numberTexture[i] = TextureManager::Load("resources/Timer/num_" + std::to_string(i) + ".png");
	}

	texHandleWhite_ = TextureManager::Load("resources/Title/white.png");
	//スプライトの初期化
	timerSprite1.reset(Sprite::Create(numberTexture[0], { 128.0f,0.0f }));
	timerSprite10.reset(Sprite::Create(numberTexture[0], { 64.0f,0.0f }));
	timerSprite100.reset(Sprite::Create(numberTexture[0], { 0.0f,0.0f }));
	countdownSprite.reset(Sprite::Create(numberTexture[3], { 640.0f,360.0f }));


	stringTex_ = TextureManager::Load("resources/string.png");
	string_.reset(Sprite::Create(stringTex_, { 390.0f,150.0f }));
	string_->SetTextureSize({ 500.0f,100.0f });

	countdownSprite->SetTextureSize({ 192.0f,192.0f});
	countdownSprite->SetAnchorPoint({ 0.5f,0.5f });
	//countdownSprite->CreateVertex();

	spriteMask_.reset(Sprite::Create(texHandleWhite_));

	timer = std::make_unique<Timer>();
	timer->Reset();
	timer->Stop();

	// ギミック
	gimmick_ = std::make_unique<Gimmick>();
	gimmick_->SetPlayer(player_.get());
	gimmick_->Initialize();
	switch (Title::GetLevel()) {
	case Level::EASY: {
		Loader::LoadJsonFile("resources/stage", "easy", player_.get(), ground_.get(), obstacles_,walls_);
		//GlobalVariables::GetInstance()->LoadFiles();
		player_->Init({ 0.0f,100.0f,0.0f });
		/*-----------------------あまりよくない感じ-------------------*/
		GlobalVariables* globalVariables = GlobalVariables::GetInstance();
		groupName_ = "easyTimeScore";
		GlobalVariables::GetInstance()->LoadFileTimeScore(groupName_);
		// グループを追加
		//GlobalVariables::GetInstance()->CreateGroup("time");
		//globalVariables->AddItme(groupName, "time", timer->GetElapsedSeconds());
		//globalVariables->GetInstance()->SaveFileTimer();
		//------------------------------------------------------------//
		break;
	}
	case Level::NORMAL: {
		Loader::LoadJsonFile("resources/stage", "normal", player_.get(), ground_.get(), obstacles_, walls_);
		player_->Init({ 0.0f,200.0f,0.0f });
		/*-----------------------あまりよくない感じ-------------------*/
		GlobalVariables* globalVariables = GlobalVariables::GetInstance();
		groupName_ = "normalTimeScore";
		GlobalVariables::GetInstance()->LoadFileTimeScore(groupName_);
		break;
	}
	case Level::HARD: {
		Loader::LoadJsonFile("resources/stage", "hard", player_.get(), ground_.get(), obstacles_, walls_);
		player_->Init({ 0.0f,300.0f,0.0f });
		/*-----------------------あまりよくない感じ-------------------*/
		GlobalVariables* globalVariables = GlobalVariables::GetInstance();
		groupName_ = "hardTimeScore";
		GlobalVariables::GetInstance()->LoadFileTimeScore(groupName_);
		break;
	}
		
	}
}

void GameScene::Update()
{
	obstacles_.remove_if([](std::unique_ptr< Obstacles>& bullet) {
		if (bullet->IsDead()) {
			//bullet.reset();
			return true;
		}
		return false;
		});

	switch (phase_)
	{
	case GameScene::Phase::kWait:
		//待機中
		WaitPhase();
		break;
	case GameScene::Phase::kPlay:
		//ゲームプレイ
		PlayPhase();
		break;
	case GameScene::Phase::kAfterPlay:
		//ゲームプレイ
		AfterPlayPhase();
		break;
	}
}

void GameScene::Draw()
{

	spriteMask_->Draw();
	postProcess_->Draw();

	if (!isTransition_ && param_.threshold <= 0.2f) {

		timerSprite1->Draw();
		timerSprite10->Draw();
		timerSprite100->Draw();
		//タイマーの更新
		timer->Start();
	}
	
	if (phase_ == Phase::kWait)
	{
		string_->Draw();
		countdownSprite->Draw();
	}

}

void GameScene::PostProcessDraw()
{
	postProcess_->PreDraw();
	skydoem_->Draw(camera_);
	
	ground_->Draw(camera_);
	player_->Draw(camera_);
	
	//obstacles->Draw(camera_);
	for (auto itr = obstacles_.begin(); itr != obstacles_.end(); itr++) {
		(*itr)->Draw(camera_);
	}
	for (auto itr = walls_.begin(); itr != walls_.end(); itr++) {
		(*itr)->Draw(camera_);
	}
	// ギミック
	gimmick_->Draw(camera_);

	postProcess_->PostDraw();
	
}

void GameScene::Transition()
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

void GameScene::Transition2()
{
	if (isTransition_) {
		postProcess_->SetBloomDissolveParam(param_);
		param_.threshold += 0.02f;
		if (param_.threshold >= 1.2f) {
			gameAudio_->GameBGM(false);
			isTransition_ = false;
			GameManager::GetInstance()->ChangeScene("RESULT");
		}
	}

}




void GameScene::WaitPhase()
{
	Transition();
	camera_ = gameCamera_->GetCamera();
	//GlobalVariables::GetInstance()->Update();
	skydoem_->Update();
	ground_->Update();
	player_->Update();
	gameCamera_->Update();

	//obstacles->Update();
	for (auto itr = obstacles_.begin(); itr != obstacles_.end(); itr++) {
		(*itr)->Update();
	}
	for (auto itr = walls_.begin(); itr != walls_.end(); itr++) {
		(*itr)->Update();
	}

	int countdown = 4 - (timer->GetElapsedSeconds() % 5);		//一桁目の取得
	if(timer->GetElapsedSeconds() > 0)
	{
		countdownSprite->SetTexHandle(numberTexture[countdown]);
	}
	
	if (countdown == 0)
	{
		ChangePhase(Phase::kPlay);
		timer->Reset();
	}


}

void GameScene::PlayPhase()
{
	//Transition();
	camera_ = gameCamera_->GetCamera();
	//GlobalVariables::GetInstance()->Update();
	skydoem_->Update();
	ground_->Update();

	player_->Update();
	player_->SetIsFall(true);
	gameCamera_->Update();
	//obstacles->Update();
	for (auto itr = obstacles_.begin(); itr != obstacles_.end(); itr++) {
		(*itr)->Update();
	}
	for (auto itr = walls_.begin(); itr != walls_.end(); itr++) {
		(*itr)->Update();
	}
	//CheckAllCollision();

	

	// ギミック
	gimmick_->Update();

	int index1 = timer->GetElapsedSeconds() % 10;			//一桁目の取得
	int index10 = (timer->GetElapsedSeconds() / 10) % 10;	//二桁目の取得
	int index100 = (timer->GetElapsedSeconds() / 100) % 10;	//二桁目の取得

	//テクスチャをタイマーによって変更
	timerSprite1->SetTexHandle(numberTexture[index1]);
	timerSprite10->SetTexHandle(numberTexture[index10]);
	timerSprite100->SetTexHandle(numberTexture[index100]);
	Collision();

	if (player_->GetWorldPosition().y <= 0) {

		phase_ = Phase::kAfterPlay;
		timer->Stop();
		//GameManager::GetInstance()->ChangeScene("RESULT");
		GlobalVariables::GetInstance()->AddTime(groupName_, timer->GetElapsedSeconds());
		isTransition_ = true;
		//GlobalVariables::GetInstance()->SaveFileTimer();
	}
}

void GameScene::AfterPlayPhase()
{
	camera_ = gameCamera_->GetCamera();
	//GlobalVariables::GetInstance()->Update();
	skydoem_->Update();
	ground_->Update();
	
	player_->Update();
	gameCamera_->Update();

	//obstacles->Update();
	for (auto itr = obstacles_.begin(); itr != obstacles_.end(); itr++) {
		(*itr)->Update();
	}
	for (auto itr = walls_.begin(); itr != walls_.end(); itr++) {
		(*itr)->Update();
	}

	Transition2();

	int countdown = 4 - (timer->GetElapsedSeconds() % 5);		//一桁目の取得
	if (timer->GetElapsedSeconds() > 0)
	{
		//countdownSprite->SetTexHandle(numberTexture[countdown]);
	}

	if (countdown == 0)
	{
		//gameAudio_->LandingSE();
		isTransition_ = true;
		//timer->Reset();
	}

}

void GameScene::Collision()
{
	collisionManager_->ColliderClear(); // colliderのリストをクリア

	collisionManager_->ColliderPush(player_.get()); // playerをリストに追加

	gimmick_->ColliderPush(collisionManager_.get());

	for (auto obstacles = obstacles_.begin();
		obstacles != obstacles_.end(); ++obstacles) {

		collisionManager_->ColliderPush((*obstacles).get()); // enemyをリストに登録

	}

	collisionManager_->CheckAllCollision(); // 判定
}


