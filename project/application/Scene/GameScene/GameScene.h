#pragma once
#include "application/Scene/IScene/IScene.h"
#include "engine/Sprite/Sprite.h"
#include "engine/Model/Model.h"
#include "engine/Input/Input.h"
#include "engine/PostProcess/PostProcess.h"
#include "engine/Model/Animation/ModelAnimation.h"
#include "engine/Object3DPlacer/Object3DPlacer.h"
#include "application/GameManager/GameManager.h"

#include "application/Player/Player.h"
#include "application/GameCamera/GameCamera.h"
#include "application/Ground/Ground.h"

class GameScene : public IScene {
public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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
	Camera camera_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<GameCamera> gameCamera_;
	std::unique_ptr<Ground> ground_;
};
