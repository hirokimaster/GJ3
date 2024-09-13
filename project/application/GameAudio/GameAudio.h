#pragma once
#include "engine/Audio/Audio.h"

class GameAudio {
public:

	/// <summary>
	/// シングルトン
	/// </summary>
	/// <returns></returns>
	static GameAudio* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// gameSceneのBGM
	/// </summary>
	void GameBGM(bool isLoop);

	/// <summary>
	/// クリックのSE
	/// </summary>
	void ClickSE();

	/// <summary>
	/// 雲に当たった時のSE
	/// </summary>
	void HitCloudSE();

	/// <summary>
	/// 障害物に当たった時のSE
	/// </summary>
	void HitObstaclesSE();

	/// <summary>
	/// TitleSceneのBGM
	/// </summary>
	void TitleBGM(bool isLoop);

	/// <summary>
	/// resultSceneのBGM
	/// </summary>
	void ResultBGM(bool isLoop);

	/// <summary>
	/// selectのSE
	/// </summary>
	void SelectSE();

	/// <summary>
	/// 着地時のSE
	/// </summary>
	void LandingSE();

private:
	GameAudio() = default;
	~GameAudio() = default;
	GameAudio(const GameAudio&) = default;
	const GameAudio& operator=(const GameAudio&) = delete;

private:

	uint32_t gameBGM_ = 0;
	uint32_t clickSE_ = 0;
	uint32_t hitCloudSE_ = 0;
	uint32_t hitObstaclesSE_ = 0;
	uint32_t titleBGM_ = 0;
	uint32_t resultBGM_ = 0;
	uint32_t landingSE_ = 0;
	uint32_t selectSE_ = 0;

};
