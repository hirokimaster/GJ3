#pragma once
#include "application/Scene/IScene/IScene.h"
#include "engine/Sprite/Sprite.h"
#include "engine/Model/Model.h"
#include "engine/Input/Input.h"
#include "engine/PostProcess/PostProcess.h"
#include "engine/Model/Animation/ModelAnimation.h"
#include "engine/Object3DPlacer/Object3DPlacer.h"
#include "application/GameManager/GameManager.h"
#include "engine/Utility/CollisionManager/CollisionManager.h"

#include "application/Player/Player.h"
#include "application/Wall/Wall.h"
#include "application/GameCamera/GameCamera.h"
#include "application/Ground/Ground.h"
#include "application/Obstacles/Obstacles.h"
#include "application/Skydome/Skydome.h"
#include "application/Wall/Wall.h"
#include "application/Object/Timer/Timer.h"
#include "application/Gimmick/Gimmick.h"

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

	enum class Phase
	{
		kWait,
		kPlay,
		kAfterPlay,
	};

	void ChangePhase(Phase phase) { phase_ = phase; };

private:

	void Transition();

	void Transition2();

	//待ち
	void WaitPhase();
	//プレイフェーズ
	void PlayPhase();
	//プレイ後のフェーズ
	void AfterPlayPhase();

public:
	void Collision();
	
private:
	std::unique_ptr<CollisionManager> collisionManager_;
	Camera camera_;
	std::unique_ptr<Skydome> skydoem_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<GameCamera> gameCamera_;
	std::unique_ptr<Ground> ground_;
	//std::unique_ptr<Obstacles> obstacles;
	// 障害物
	std::list<std::unique_ptr<Obstacles>> obstacles_;
	// 雲
	std::list<std::unique_ptr<Wall>> walls_;

	//タイマー用
	std::unique_ptr<Timer>timer;
	std::unique_ptr<Sprite>timerSprite1;
	std::unique_ptr<Sprite>timerSprite10;
	std::unique_ptr<Sprite>timerSprite100;
	std::unique_ptr<Sprite>countdownSprite;
	uint32_t numberTexture[10];




	std::unique_ptr<Wall>leftWall_;
	std::unique_ptr<Wall>rightWall_;
	
	// ギミック
	std::unique_ptr<Gimmick> gimmick_;

	// postEffect用
	uint32_t texHandleMask_ = 0;
	BloomDissolveParam param_{};
	std::unique_ptr<Sprite> spriteMask_;
	uint32_t texHandleWhite_ = 0;
	std::unique_ptr<PostProcess> postProcess_;
	// シーン遷移用
	bool isTransition_ = false;
	float sceneTimer_ = 130.0f;
	const char* groupName_ = nullptr;

	//フェーズ用
	Phase phase_;

};
