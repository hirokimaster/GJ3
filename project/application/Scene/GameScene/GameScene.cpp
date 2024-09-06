#include "GameScene.h"
#include "engine/ModelManager/ModelManager.h"
#include "application/GlovalVariables/GlobalVariables.h"
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
	player_->Init({100.0f,0.0f,0.0f});

	
	gameCamera_ = std::make_unique<GameCamera>();
	gameCamera_->Init();
	player_->SetCamera(&gameCamera_->GetCamera());
	ground_ = std::make_unique<Ground>();
	ground_->Init({ 0.0f,0.0f,0.0f });
	
	skydoem_ = std::make_unique<Skydome>();
	skydoem_->Init();

	/*std::unique_ptr<Obstacles>*/ obstacles = std::make_unique<Obstacles>();
	obstacles->Init({ 0.0f,20.0f,0.0f });
	/*obstacles_.push_back(obstacles.get());
	for (std::list<Obstacles*>::iterator itr = obstacles_.begin(); itr != obstacles_.end(); itr++) {
		(*itr)->Init();
	}*/
	collisionManager_ = std::make_unique<CollisionManager>(); // コリジョンマネージャ
}

void GameScene::Update()
{
	camera_ = gameCamera_->GetCamera();
	//GlobalVariables::GetInstance()->Update();
	skydoem_->Update();
	ground_->Update();
	player_->Update();
	gameCamera_->Update();
	obstacles->Update();
	/*for (std::list<Obstacles*>::iterator itr = obstacles_.begin(); itr != obstacles_.end(); itr++) {
		(*itr)->Update();
	}*/
	//CheckAllCollision();
}

void GameScene::Draw()
{
	
	
	skydoem_->Draw(camera_);
	ground_->Draw(camera_);
	player_->Draw(camera_);
	obstacles->Draw(camera_);
	/*for (std::list<Obstacles*>::iterator itr = obstacles_.begin(); itr != obstacles_.end(); itr++) {
		(*itr)->Draw(camera_);
	}*/
}

void GameScene::PostProcessDraw()
{
}


