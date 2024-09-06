#include "Obstacles.h"
#include "engine/TextureManager/TextureManager.h"
#include "application/Player/Player.h"

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

	SetCollosionAttribute(0b10);
	SetCollisionMask(0b01);
}

void Obstacles::Update()
{
	worldTransform_.UpdateMatrix();
}

void Obstacles::Draw(Camera& camera)
{
	object_->Draw(camera);
}

Vector3 Obstacles::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld.m[3][0];
	worldPos.y = worldTransform_.matWorld.m[3][1];
	worldPos.z = worldTransform_.matWorld.m[3][2];

	return worldPos;
}

void Obstacles::OnCollision()
{
	
	player_->SetBehavior(Behavior::kDeceleration);
}
