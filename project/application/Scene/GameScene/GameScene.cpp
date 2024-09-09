#include "GameScene.h"
#include "engine/ModelManager/ModelManager.h"
#include "application/GlovalVariables/GlobalVariables.h"
#include "engine/Loader/Loader.h"
GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	ModelManager::GetInstance()->LoadAnimationModel("sneakWalk.gltf");
	ModelManager::GetInstance()->LoadObjModel("ground/ground.obj");
	ModelManager::GetInstance()->LoadObjModel("skydome/skydome.obj");
	ModelManager::GetInstance()->LoadObjModel("cube.obj");

	

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
	
	Loader::LoadJsonFile("resources/stage","easy",player_.get(),ground_.get(),obstacles_);
	
	collisionManager_ = std::make_unique<CollisionManager>(); // コリジョンマネージャ

	//テクスチャの初期化
	for (int i = 0; i < 10; i++)
	{
		numberTexture[i] = TextureManager::Load("resources/Timer/num_" + std::to_string(i) + ".png");
	}

	//スプライトの初期化
	timerSprite1.reset(Sprite::Create(numberTexture[0], { 128.0f,0.0f }));
	timerSprite10.reset(Sprite::Create(numberTexture[0], { 64.0f,0.0f }));
	timerSprite100.reset(Sprite::Create(numberTexture[0], { 0.0f,0.0f }));

	timer = std::make_unique<Timer>();
	timer->Reset();
	timer->Stop();

	// ギミック
	gimmick_ = std::make_unique<Gimmick>();
	gimmick_->SetPlayer(player_.get());
	gimmick_->Initialize();

	/*-----------------------あまりよくない感じ-------------------*/
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "Time";
	// グループを追加
	GlobalVariables::GetInstance()->CreateGroup(groupName);
	globalVariables->AddItme(groupName, "time", timer->GetElapsedSeconds());
	//------------------------------------------------------------//

}

void GameScene::Update()
{
	camera_ = gameCamera_->GetCamera();
	GlobalVariables::GetInstance()->Update();
	skydoem_->Update();
	ground_->Update();
	player_->Update();
	gameCamera_->Update();
	//obstacles->Update();
	for (auto itr = obstacles_.begin(); itr != obstacles_.end(); itr++) {
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
}

void GameScene::Draw()
{
	
	
	skydoem_->Draw(camera_);
	ground_->Draw(camera_);
	player_->Draw(camera_);
	//obstacles->Draw(camera_);
	for (auto itr = obstacles_.begin(); itr != obstacles_.end(); itr++) {
		(*itr)->Draw(camera_);
	}

	// ギミック
	gimmick_->Draw(camera_);

	timerSprite1->Draw();
	timerSprite10->Draw();
	timerSprite100->Draw();

	//タイマーの更新
	timer->Start();
}

void GameScene::PostProcessDraw()
{
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


