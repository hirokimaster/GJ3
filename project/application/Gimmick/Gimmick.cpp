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
}

void Gimmick::Draw(Camera& camera)
{
	thunder_->Draw(camera);
}
