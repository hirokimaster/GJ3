#include "GameAudio.h"

GameAudio* GameAudio::GetInstance() {
	static GameAudio instance;
	return &instance;
}

void GameAudio::Initialize()
{
	// "resources/switch.wav"  この部分だけ変えて
	gameBGM_ = Audio::GetInstance()->SoundLoadWave("resources/lovelyflower.wav");
	clickSE_ = Audio::GetInstance()->SoundLoadWave("resources/pushAudio.wav");
	hitCloudSE_ = Audio::GetInstance()->SoundLoadWave("resources/switch.wav");
	hitObstaclesSE_ = Audio::GetInstance()->SoundLoadWave("resources/switch.wav");
	titleBGM_ = Audio::GetInstance()->SoundLoadWave("resources/nagagutsudeodekake.wav");
	resultBGM_ = Audio::GetInstance()->SoundLoadWave("resources/otenbahime.wav");
	landingSE_ = Audio::GetInstance()->SoundLoadWave("resources/switch.wav");
	selectSE_ = Audio::GetInstance()->SoundLoadWave("resources/select.wav");
}

void GameAudio::GameBGM(bool isLoop)
{
	if (isLoop) {
		Audio::GetInstance()->SoundPlayLoop(gameBGM_);
	}
	else {
		Audio::GetInstance()->SoundPlayStop(gameBGM_);
	}
}

void GameAudio::ClickSE()
{
	Audio::GetInstance()->SoundPlayWave(clickSE_);
}

void GameAudio::HitCloudSE()
{
	Audio::GetInstance()->SoundPlayWave(hitCloudSE_);
}

void GameAudio::HitObstaclesSE()
{
	Audio::GetInstance()->SoundPlayWave(hitObstaclesSE_);
}

void GameAudio::TitleBGM(bool isLoop)
{
	if (isLoop) {
		Audio::GetInstance()->SoundPlayLoop(titleBGM_);
	}
	else {
		Audio::GetInstance()->SoundPlayStop(titleBGM_);
	}
}

void GameAudio::ResultBGM(bool isLoop)
{
	if (isLoop) {
		Audio::GetInstance()->SoundPlayLoop(resultBGM_);
	}
	else {
		Audio::GetInstance()->SoundPlayStop(resultBGM_);
	}
}

void GameAudio::SelectSE()
{
	Audio::GetInstance()->SoundPlayWave(selectSE_);
}

void GameAudio::LandingSE()
{
	Audio::GetInstance()->SoundPlayWave(landingSE_);
}
