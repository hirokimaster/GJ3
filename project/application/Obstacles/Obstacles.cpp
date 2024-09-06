#include "Obstacles.h"
#include "engine/TextureManager/TextureManager.h"


void Obstacles::Init(Vector3 translate)
{
	worldTransform_.Initialize();
	worldTransform_.scale = { 5.0f, 3.0f, 1.0f };
	worldTransform_.translate = translate;

	skinTex_ = TextureManager::GetInstance()->Load("resources/ground/ground.png");

	object_ = std::make_unique<Object3DPlacer>();
	object_->Initialize();
	object_->SetModel("cube.obj");
	object_->SetTexHandle(skinTex_);
	object_->SetWorldTransform(worldTransform_);
}

void Obstacles::Update()
{
	worldTransform_.UpdateMatrix();
}

void Obstacles::Draw(Camera& camera)
{
	object_->Draw(camera);
}
