#include "Gimmick.h"

void Gimmick::Initialize()
{
	thunder_ = std::make_unique<Thunder>();
	thunder_->Initialize();
	thunder_->SetTarget(&player_->GetWorldTransform());
}

void Gimmick::Update()
{
	thunder_->Update();
	if (!thunder_->GetTarget() && !thunder_->GetIsFall()) {
		thunder_->SetTarget(&player_->GetWorldTransform());
		return;
	}

	Collision();
}

void Gimmick::Draw(Camera& camera)
{
	thunder_->Draw(camera);
}

void Gimmick::ColliderPush(CollisionManager* collisionManager)
{
	collisionManager->ColliderPush(thunder_.get());
}

void Gimmick::Collision()
{
	if (thunder_->GetIsHit()) {
		player_->SetBehavior(Behavior::kElectricShock);
	}

	if (player_->GetBehavior() == Behavior::kRoot ||
		player_->GetBehavior() == Behavior::kDeceleration) {

		thunder_->SetIsHit(false);
	}
}
