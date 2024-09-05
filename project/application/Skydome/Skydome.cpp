#include "Skydome.h"
#include "engine/Utility/ImGuiManager/ImGuiManager.h"

void Skydome::Init()
{
	
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 1000.0f,1000.0f,1000.0f };
	object_ = std::make_unique<Object3d>();
	object_->Init();
	object_->SetModel("skydome.obj");
	skinTex_ = TextureManager::GetInstance()->StoreTexture("Resources/skydome.png");
}

void Skydome::Update()
{
	worldTransform_.UpdateMatrix();
	object_->SetWorldTransform(worldTransform_);
}

void Skydome::Draw(Camera* camera)
{
	object_->Draw(skinTex_, camera);
}
