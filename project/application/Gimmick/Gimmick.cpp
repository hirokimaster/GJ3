#include "Gimmick.h"

void Gimmick::Initialize()
{
	thunder_ = std::make_unique<Thunder>();
	thunder_->Initialize();
}

void Gimmick::Update()
{
	thunder_->Update();
}

void Gimmick::Draw(Camera& camera)
{
	thunder_->Draw(camera);
}
