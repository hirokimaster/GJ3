#pragma once
#include "application/Scene/IScene/IScene.h"
#include "engine/Input/Input.h"
#include "application/GameManager/GameManager.h"
#include <vector>
#include <memory>
#include "engine/Sprite/Sprite.h"

#include "application/Player/Player.h"
#include "application/Wall/Wall.h"
#include "application/GameCamera/GameCamera.h"
#include "application/Ground/Ground.h"
#include "application/Obstacles/Obstacles.h"
#include "application/Skydome/Skydome.h"
#include "application/Wall/Wall.h"
#include "application/Object/Timer/Timer.h"
#include "application/Gimmick/Gimmick.h"
#include "application/GameAudio/GameAudio.h"

class ResultScene : public IScene
{

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	ResultScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ResultScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	/// <summary>
	/// ポストエフェクト描画
	/// </summary>
	void PostProcessDraw()override;

private:

	void Transition();

	void Transition2();

private:
	const char* groupName_ = nullptr;
	Camera camera_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Ground> ground_;
	// 障害物
	std::list<std::unique_ptr<Obstacles>> obstacles_;
	// 雲
	std::list<std::unique_ptr<Wall>> walls_;
	std::unique_ptr<Skydome> skydoem_;

	std::vector<uint32_t> timeScores_;

	std::vector<std::unique_ptr<Sprite>> timerSprites1_;
	std::vector<std::unique_ptr<Sprite>> timerSprites10_;
	std::vector<std::unique_ptr<Sprite>> timerSprites100_;

	std::unique_ptr<Sprite> spriteA_ = nullptr;

	uint32_t texHandleA_ = 0;
	uint32_t numberTexture[10];

	// BGM,SE
	GameAudio* gameAudio_ = nullptr;
	uint32_t playerTex;

	// postEffect用
	uint32_t texHandleMask_ = 0;
	BloomDissolveParam param_{};
	std::unique_ptr<Sprite> spriteMask_;
	uint32_t texHandleWhite_ = 0;
	std::unique_ptr<PostProcess> postProcess_;
	// シーン遷移用
	bool isTransition_ = false;
	bool isTransition2_ = false;
};

