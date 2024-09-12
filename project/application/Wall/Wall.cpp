#include "Wall.h"
#include "engine/TextureManager/TextureManager.h"
#include "engine/Lighting/Lighting.h"

void Wall::Init(Vector3 translate, Vector3 scale)
{
	worldTransform_.Initialize();
	//worldTransform_.scale = { 1.0f, 100.0f, 1.0f };
	worldTransform_.translate = translate;
	worldTransform_.scale = scale;
	skinTex_ = TextureManager::GetInstance()->Load("resources/white.png");
	ModelManager::GetInstance()->LoadObjModel("wall/wall.obj");
	object_ = std::make_unique<Object3DPlacer>();
	object_->Initialize();
	object_->SetModel("wall/wall.obj");
	object_->SetTexHandle(skinTex_);
	object_->SetWorldTransform(worldTransform_);

	light_ = Light::None;
	lighting_ = new Lighting();
	lighting_->Initialize(light_);

	object_->SetLight(lighting_);
	object_->SetEnableLight(true);
}

void Wall::Update()
{
	worldTransform_.UpdateMatrix();
}

void Wall::ResultUpdate()
{
	worldTransform_.translate.y += 0.25f;
	if (worldTransform_.translate.y >= 125.0f) {
		worldTransform_.translate.y = 62.8f;
	}
	worldTransform_.UpdateMatrix();
	object_->SetWorldTransform(worldTransform_);
}

void Wall::Draw(Camera& camera)
{
	object_->Draw(camera);
}