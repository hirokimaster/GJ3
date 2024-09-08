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

private:

	std::unique_ptr<Sprite> spriteTitle_ = nullptr;
	uint32_t texHandleTitle_ = 0;
	uint32_t texHandleStart_ = 0;
	uint32_t texHandleOp_ = 0;
	uint32_t texHandleEnd_ = 0;
	uint32_t texHandleLevel_ = 0;
	uint32_t texHandleEasy_ = 0;
	uint32_t texHandleNormal_ = 0;
	uint32_t texHandleHard_ = 0;
	uint32_t selectNum_ = 0;
	Level level_ = Level::EASY;
	Select select_ = Select::START;
	bool optionMode_ = false;
	float optionTimer_ = 5.0f;
};