#include "ResultScene.h"
#include "application/GlovalVariables/GlobalVariables.h"
#include "application/Scene/Title/Title.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{

	switch (Title::GetLevel()) {
	case Level::EASY: {
		//GlobalVariables::GetInstance()->LoadFiles();
		break;
	}
	case Level::NORMAL: {
		break;
	}
	case Level::HARD: {
		break;
	}


	}
	timeScores_ = GlobalVariables::GetInstance()->GetTimes();

	//テクスチャの初期化
	for (int i = 0; i < 10; i++)
	{
		numberTexture[i] = TextureManager::Load("resources/Timer/num_" + std::to_string(i) + ".png");
	}
	uint32_t index1;	//一桁目の取得
	uint32_t index10;   //二桁目の取得
	uint32_t index100;  //二桁目の取得

	uint32_t indexNum = 0;
	std::sort(timeScores_.begin(), timeScores_.end());
	if (timeScores_.size() > 5) {
		timeScores_.erase(timeScores_.begin() + 5, timeScores_.end());
	}
	for (auto itr = timeScores_.begin(); itr != timeScores_.end(); itr++, ++indexNum) {
		index1 = (*itr) % 10;
		index10 = ((*itr) / 10) % 10;
		index100 = ((*itr) / 100) % 10;
		std::unique_ptr<Sprite> timerSprite1;// = std::make_unique<Sprite>();
		timerSprite1.reset(Sprite::Create(numberTexture[0], { 704.0f,indexNum * 64.0f }));
		timerSprite1->SetTexHandle(numberTexture[index1]);
		timerSprites1_.push_back(std::move(timerSprite1));

		std::unique_ptr<Sprite> timerSprite10;// = std::make_unique<Sprite>();
		timerSprite10.reset(Sprite::Create(numberTexture[0], { 640,indexNum * 64.0f }));
		timerSprite10->SetTexHandle(numberTexture[index10]);
		timerSprites10_.push_back(std::move(timerSprite10));

		std::unique_ptr<Sprite> timerSprite100;// = std::make_unique<Sprite>();
		timerSprite100.reset(Sprite::Create(numberTexture[0], { 572.0f,indexNum * 64.0f }));
		timerSprite100->SetTexHandle(numberTexture[index100]);
		timerSprites100_.push_back(std::move(timerSprite100));

	}
	
}

void ResultScene::Update()
{


	if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {

		GameManager::GetInstance()->ChangeScene("TITLE");
	}
}
void ResultScene::Draw()
{
	for (auto itr = timerSprites1_.begin(); itr != timerSprites1_.end(); itr++) {
		(*itr)->Draw();
	}
	for (auto itr = timerSprites10_.begin(); itr != timerSprites10_.end(); itr++) {
		(*itr)->Draw();
	}
	for (auto itr = timerSprites100_.begin(); itr != timerSprites100_.end(); itr++) {
		(*itr)->Draw();
	}
}

void ResultScene::PostProcessDraw()
{
}
