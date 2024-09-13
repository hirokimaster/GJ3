#pragma once
#include "application/Scene/IScene/IScene.h"
#include "engine/Sprite/Sprite.h"
#include "engine/Model/Model.h"
#include "engine/Input/Input.h"
#include "engine/PostProcess/PostProcess.h"
#include "engine/Model/Animation/ModelAnimation.h"
#include "engine/Object3DPlacer/Object3DPlacer.h"
#include "application/GameManager/GameManager.h"
#include "engine/Loader/Loader.h"

#include "application/Player/Player.h"
#include "application/Wall/Wall.h"
#include "application/GameCamera/GameCamera.h"
#include "application/Ground/Ground.h"
#include "application/Obstacles/Obstacles.h"
#include "application/Skydome/Skydome.h"
#include "application/Wall/Wall.h"
#include "application/GameAudio/GameAudio.h"


enum class Level {
	EASY,
	NORMAL,
	HARD
};

enum class Select {
	START,
	OPTION,
	END
};

class Title : public IScene {
public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	Title();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Title();

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

	void OptionMode();

	void SelectMode();

	void TextureResources();

	void Transition();

	void Transition2();

public:
	static Level GetLevel() { return level_; }

private:

private:
	std::unique_ptr<PostProcess> postProcess_;
	std::unique_ptr<Sprite> spriteTitle_ = nullptr;
	std::unique_ptr<Sprite> spriteTitle2_ = nullptr;
	std::unique_ptr<Sprite> spriteTitle3_ = nullptr;

	std::unique_ptr<Sprite> spriteTitlename_ = nullptr;

	std::unique_ptr<Sprite> spriteA_ = nullptr;

	uint32_t texHandleTitle_ = 0;
	uint32_t texHandleStart_ = 0;
	uint32_t texHandleOp_ = 0;
	uint32_t texHandleEnd_ = 0;
	uint32_t texHandleLevel_ = 0;
	uint32_t texHandleEasy_ = 0;
	uint32_t texHandleNormal_ = 0;
	uint32_t texHandleHard_ = 0;

	uint32_t texHandleStartR_ = 0;
	uint32_t texHandleOpR_ = 0;
	uint32_t texHandleEndR_ = 0;
	uint32_t texHandleEasyR_ = 0;
	uint32_t texHandleNormalR_ = 0;
	uint32_t texHandleHardR_ = 0;

	uint32_t texHandleA_ = 0;
	uint32_t texHandleSpace_ = 0;

	uint32_t selectNum_ = 0;
	static Level level_;
	Select select_ = Select::START;
	bool optionMode_ = false;
	float optionTimer_ = 5.0f;
	// postEffect用
	uint32_t texHandleMask_ = 0;
	BloomDissolveParam param_{};
	std::unique_ptr<Sprite> spriteMask_;
	uint32_t texHandleWhite_ = 0;
	// シーン遷移用
	bool isTransition_ = false;
	float sceneTimer_ = 130.0f;

	Camera camera_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Ground> ground_;

	WorldTransform worldTransform_;


	// 障害物
	std::list<std::unique_ptr<Obstacles>> obstacles_;
	// 雲
	std::list<std::unique_ptr<Wall>> walls_;

	std::unique_ptr<Skydome> skydoem_;
	std::vector<uint32_t> timeScores_;
	
	// 音楽
	GameAudio* gameAudio_ = nullptr;

};