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

public:

private:
	const char* groupName_ = nullptr;
	Camera camera_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Ground> ground_;
	// 障害物
	std::list<std::unique_ptr<Obstacles>> obstacles_;
	// 雲
	std::list<std::unique_ptr<Wall>> walls_;


	std::vector<uint32_t> timeScores_;

	std::vector<std::unique_ptr<Sprite>> timerSprites1_;
	std::vector<std::unique_ptr<Sprite>> timerSprites10_;
	std::vector<std::unique_ptr<Sprite>> timerSprites100_;
	uint32_t numberTexture[10];
	uint32_t playerTex;
};

