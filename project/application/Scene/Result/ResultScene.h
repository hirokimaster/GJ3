#pragma once
#include "application/Scene/IScene/IScene.h"
#include <vector>
#include <memory>
#include "engine/Sprite/Sprite.h"
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

	std::vector<uint32_t> timeScores_;

	std::vector<std::unique_ptr<Sprite>> timerSprites1_;
	std::vector<std::unique_ptr<Sprite>> timerSprites10_;
	std::vector<std::unique_ptr<Sprite>> timerSprites100_;
	uint32_t numberTexture[10];
};

