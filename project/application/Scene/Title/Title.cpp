#include "Title.h"
#include "engine/ModelManager/ModelManager.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::Initialize()
{
	texHandleTitle_ = TextureManager::Load("resources/title.png");
	spriteTitle_.reset(Sprite::Create(texHandleTitle_));
}

void Title::Update()
{
}

void Title::Draw()
{
	spriteTitle_->Draw();
}

void Title::PostProcessDraw()
{
}
