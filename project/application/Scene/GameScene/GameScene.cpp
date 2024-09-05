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
	camera_.Initialize();
	player_ = std::make_unique<Player>();
	player_->Init();

	
	gameCamera_ = std::make_unique<GameCamera>();
	gameCamera_->Init();
	player_->SetCamera(&gameCamera_->GetCamera());
	ground_ = std::make_unique<Ground>();
	ground_->Init();
	
}

void GameScene::Update()
{
	camera_ = gameCamera_->GetCamera();
	//GlobalVariables::GetInstance()->Update();
	ground_->Update();
	player_->Update();
	gameCamera_->Update();
	
}

void GameScene::Draw()
{
	player_->Draw(camera_);
	ground_->Draw(camera_);
}

void GameScene::PostProcessDraw()
{
}
