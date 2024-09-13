#include "Obstacles.h"
#include "engine/TextureManager/TextureManager.h"
#include "application/Player/Player.h"

void Obstacles::Init(Vector3 translate, bool isMove)
{
	worldTransform_.Initialize();
	worldTransform_.scale = { 1.0f, 0.5f, 1.0f };
	worldTransform_.translate = translate;
	isMove_ = isMove;
	if (!isMove_) {
		skinTex_ = TextureManager::GetInstance()->Load("resources/obstacles/obstacles.png");
	}
	else if (isMove_) {
		skinTex_ = TextureManager::GetInstance()->Load("resources/obstacles/obstaclesMove.png");
	}

	object_ = std::make_unique<Object3DPlacer>();
	object_->Initialize();
	object_->SetModel("cube.obj");
	object_->SetTexHandle(skinTex_);
	object_->SetWorldTransform(worldTransform_);
	object_->SetEnableLight(true);
	SetCollosionAttribute(0b10);
	SetCollisionMask(0b01);
	SetRadious(0.5f);
	velo_ = 0.2f;
	bool isDead_ = false;
}

void Obstacles::Update()
{
	Move();
	worldTransform_.UpdateMatrix();
	object_->SetWorldTransform(worldTransform_);
	
}

void Obstacles::Draw(Camera& camera)
{
	object_->Draw(camera);
}

void Obstacles::Move()
{
	if (isMove_) {
		worldTransform_.translate.x += velo_;
	}
	if (worldTransform_.translate.x >= 10.0f) {
		worldTransform_.translate.x = 10.0f;
		velo_ *= -1.0f;
	}
	else if (worldTransform_.translate.x <= -10.0f) {
		worldTransform_.translate.x = -10.0f;
		velo_ *= -1.0f;
	}
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
	isDead_ = true;
	player_->SetBehavior(Behavior::kDeceleration);
	
}
