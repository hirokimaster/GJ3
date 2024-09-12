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
	// postEffect
	isTransition_ = true;
	postProcess_ = std::make_unique<PostProcess>();
	postProcess_->Initialize();
	postProcess_->SetEffect(Dissolve);
	texHandleMask_ = TextureManager::Load("resources/noise9.png");
	postProcess_->SetMaskTexture(texHandleMask_);
	param_.threshold = 1.0f;
	postProcess_->SetDissolveParam(param_);

	ModelManager::GetInstance()->LoadAnimationModel("sneakWalk.gltf");
	ModelManager::GetInstance()->LoadObjModel("ground/ground.obj");
	ModelManager::GetInstance()->LoadObjModel("skydome/skydome.obj");
	ModelManager::GetInstance()->LoadObjModel("cube.obj");
	ModelManager::GetInstance()->LoadAnimationModel("Player/player.gltf");
	//ModelManager::GetInstance()->LoadAnimationModel("Player/player2.gltf");
	//ModelManager::GetInstance()->LoadObjModel("Player/player.obj");
	

	camera_.Initialize();

	player_ = std::make_unique<Player>();
	player_->Init({0.0f,100.0f,0.0f});

	
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
		/*-----------------------あまりよくない感じ-------------------*/
		GlobalVariables* globalVariables = GlobalVariables::GetInstance();
		groupName_ = "normalTimeScore";
		GlobalVariables::GetInstance()->LoadFileTimeScore(groupName_);
		break;
	}
	case Level::HARD: {
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
		
		GameManager::GetInstance()->ChangeScene("RESULT");
		GlobalVariables::GetInstance()->AddTime(groupName_,timer->GetElapsedSeconds());
		//GlobalVariables::GetInstance()->SaveFileTimer();
	}

}

void GameScene::Draw()
{
	
	spriteMask_->Draw();
	postProcess_->Draw();
	
	
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

	timerSprite1->Draw();
	timerSprite10->Draw();
	timerSprite100->Draw();

	//タイマーの更新
	timer->Start();

	postProcess_->PostDraw();
	
}

void GameScene::Transition()
{
	if (isTransition_) {
		postProcess_->SetDissolveParam(param_);
		param_.threshold -= 0.02f;
		if (param_.threshold <= 0.0f) {
			isTransition_ = false;
			param_.threshold = 0.0f;
		}
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


