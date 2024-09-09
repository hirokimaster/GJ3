#include "Thunder.h"

void Thunder::Initialize()
{
	// 雷
	worldTransform_.Initialize();
	worldTransform_.translate.y = 100.0f;
	object_ = std::make_unique<Object3DPlacer>();
	object_->Initialize();
	object_->SetModel("cube.obj");
	texHandle_ = TextureManager::Load("resources/uvChecker.png");
	object_->SetTexHandle(texHandle_);
	object_->SetWorldTransform(worldTransform_);

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
	if (Input::GetInstance()->PressedKey(DIK_SPACE)) {
		isBlinking_ = true;
	}
	
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
	worldTransform_.translate.y -= 1.0f;
}

void Thunder::Fall()
{
	// playerに追従する
	if (target_) {
		preline_->SetPosition(worldTransformPreline_.translate);
		worldTransformPreline_.translate.x = target_->translate.x;
		worldTransform_.translate.x = target_->translate.x;
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
	if (worldTransform_.translate.y <= 0.0f) {
		isFall_ = false;
		worldTransform_.translate.y = 100.0f;
	}
}

void Thunder::OnCollision()
{
	object_->SetColor({ 1.0f,0.0f,0.0f,1.0f });
}

