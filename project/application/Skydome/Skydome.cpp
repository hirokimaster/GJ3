#include "Skydome.h"
#include "engine/Utility/ImGuiManager/ImGuiManager.h"
#include "engine/TextureManager/TextureManager.h"

void Skydome::Init()
{
	
	worldTransform_.Initialize();
	worldTransform_.scale = { 1000.0f,1000.0f,1000.0f };
	skinTex_ = TextureManager::GetInstance()->Load("resources/skydome/skydome.png");

	object_ = std::make_unique<Object3DPlacer>();
	object_->Initialize();
	object_->SetModel("skydome/skydome.obj");
	object_->SetWorldTransform(worldTransform_);
	object_->SetTexHandle(skinTex_);
	
}

void Skydome::Update()
{
	worldTransform_.UpdateMatrix();
	
}

void Skydome::Draw(Camera& camera)
{
	object_->Draw(camera);
}
