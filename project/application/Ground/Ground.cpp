#include "Ground.h"
#include "engine/TextureManager/TextureManager.h"


void Ground::Init(Vector3 translate)
{
	worldTransform_.Initialize();
	worldTransform_.scale = {100.0f, 10.0f, 1.0f};
	worldTransform_.translate.y;

	skinTex_ = TextureManager::GetInstance()->Load("resources/ground/ground.png");

	object_ = std::make_unique<Object3DPlacer>();
	object_->Initialize();
	object_->SetModel("ground/ground.obj");
	object_->SetTexHandle(skinTex_);
	object_->SetWorldTransform(worldTransform_);
}

void Ground::Update()
{
	worldTransform_.UpdateMatrix();
}

void Ground::Draw(Camera& camera)
{
	object_->Draw(camera);
}