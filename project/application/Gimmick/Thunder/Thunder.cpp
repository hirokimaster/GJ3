#include "Thunder.h"

void Thunder::Initialize()
{
	// 雷
	worldTransform_.Initialize();
	worldTransform_.translate.y = 140.0f;
	object_ = std::make_unique<Object3DPlacer>();
	object_->Initialize();
	object_->SetModel("cube.obj");
	texHandle_ = TextureManager::Load("resources/uvChecker.png");
	object_->SetTexHandle(texHandle_);
	object_->SetWorldTransform(worldTransform_);
	object_->SetColor({ 1.0f,1.0f,0.0f,0.8f });
	isFall_ = false;
	isBlinking_ = false;

	SetCollosionAttribute(0b10);
	SetCollisionMask(0b01);

	// 予測線
	worldTransformPreline_.Initialize();
	worldTransformPreline_.translate.y = 50.0f;
	worldTransformPreline_.scale.y = 50.0f;
	preline_ = std::make_unique<Object3DPlacer>();
	preline_->Initialize();
	preline_->SetModel("cube.obj");
	texHandlePreline_ = TextureManager::Load("resources/white.png");
	preline_->SetTexHandle(texHandlePreline_);
	preline_->SetWorldTransform(worldTransformPreline_);
	preline_->SetColor({ 1.0f,0.0f,0.0f,0.5f });

}

void Thunder::Update()
{
	Fall();
	worldTransform_.UpdateMatrix();
	worldTransformPreline_.UpdateMatrix();
}

void Thunder::Draw(Camera& camera)
{
	object_->Draw(camera);
	
	if (blinkingTimer_ % 40 >= 20 && isBlinking_) {						 
		preline_->Draw(camera);
	}
}

Vector3 Thunder::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld.m[3][0];
	worldPos.y = worldTransform_.matWorld.m[3][1];
	worldPos.z = worldTransform_.matWorld.m[3][2];

	return worldPos;
}

void Thunder::Move()
{
	// 雷
	object_->SetPosition(worldTransform_.translate);
	object_->SetScale(worldTransform_.scale);
	worldTransform_.scale.y += 1.0f;
}

void Thunder::Fall()
{
	// 落下タイマー
	if (!isFall_) {
		--fallTimer_;
	}
	
	if (fallTimer_ <= 0) {
		isBlinking_ = true;
		fallTimer_ = kFallInterval_;
	}

	// playerに追従する
	if (target_) {
		Vector3 offset = { 0.0f,30.0f,0.0f };
		preline_->SetPosition(worldTransformPreline_.translate);
		worldTransformPreline_.translate.x = target_->translate.x;
		worldTransform_.translate = target_->translate + offset;
	}

	// 点滅してるとき
	if (isBlinking_) {
		++blinkingTimer_;
	}

	if (blinkingTimer_ >= 120) {
		isBlinking_ = false;
		isFall_ = true;
		blinkingTimer_ = 0;
	}

	// 点滅が終わったら
	if (!isBlinking_ && isFall_) {
		target_ = nullptr;
		Move();
	}

	// 落下が終わったら
	if (worldTransform_.scale.y >= 150.0f) {
		isFall_ = false;
		worldTransform_.scale.y = 1.0f;
	}

	if (isBlinking_) {
		isFall_ = false;
		worldTransform_.scale.y = 1.0f;
	}

	// 当たったらすぐ戻す
	if (isHit_) {
		isFall_ = false;
		worldTransform_.scale.y = 1.0f;
	}
}

void Thunder::OnCollision()
{
	isHit_ = true;
}

