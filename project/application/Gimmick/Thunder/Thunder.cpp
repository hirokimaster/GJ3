#include "Thunder.h"

void Thunder::Initialize()
{
	worldTransform_.Initialize();
	object_ = std::make_unique<Object3DPlacer>();
	object_->Initialize();
	object_->SetModel("cube.obj");
	object_->SetWorldTransform(worldTransform_);
}

void Thunder::Update()
{
	worldTransform_.translate.y -= 1.0f;
	worldTransform_.UpdateMatrix();
}

void Thunder::Draw(Camera& camera)
{
	object_->Draw(camera);
}
