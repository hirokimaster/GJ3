#pragma once
#include <memory>
#include <optional>
#include "engine/Object3DPlacer/Object3DPlacer.h"
#include "engine/Transform/WorldTransform.h"
#include "engine/Camera/Camera.h"
#include "engine/Utility/CollisionManager/Collider/Collider.h"

// ふるまい
enum class Behavior {
	kRoot, // 通常状態
	kDeceleration, // 減速中
	kElectricShock, // 感電中
	kWait,	//待機時間中
};

class Player : public Collider
{
public:

	void Init(Vector3 translate);
	void Update();
	void Draw(Camera& camera);

	void Move();
	void Fall();

public:	// getter
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	Behavior GetBehavior() { return behavior_; }

public: // Setter
	void SetCamera(Camera* camera) { camera_ = camera; }
	void SetIsFall(bool fall) { isFall_ = fall; };	//待機中かどうか（落ちない

public: // Debug
	// 調整項目の適用
	void ApplyGlobalVariables();

public: // Collider
	Vector3 GetWorldPosition() override;
	void OnCollision() override;
	const Vector3& GetScale()override { return worldTransform_.scale; }

public: // Behavior関数
	/*---Behavior用関数---*/
	// 通常行動
	void BehaviorRootInit();
	void BehaviorRootUpdate();
	// 減速中行動
	void BehaviorRootDecelerationInit();
	void BehaviorRootDecelerationUpdate();
	// 感電中行動
	void BehaviorRootElectricShockInit();
	void BehaviorRootElectricShockUpdate();
	// 待機中行動
	void BehaviorRootWaitInit();
	void BehaviorRootWaitUpdate();

public: //BehaviorSetter
	void SetBehavior(Behavior behavior) { behaviorRequest_ = behavior; }

private: // Behavior変数
	// 振る舞い
	Behavior behavior_ = Behavior::kWait;
	// 次の振る舞いリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

private:
	Camera* camera_;
	std::unique_ptr<Object3DPlacer> object_;
	WorldTransform worldTransform_;
	// プレイヤー用テクスチャ
	uint32_t skinTex_;
	float aniTime_ = 0;
	float duration_ = 0.6f; // アニメ―ション全体の尺（単位は秒）

	float fallVelo_ = 0.0f;
	float gravity_ = 0.00098f;

	// Decelerationtimer
	float decelerationTimer_= 0.0f;

	// ElectricShockTimer
	float electricShockTimer_ = 0.0f;
	bool inoperable_ = false;

	bool isFall_ = false;	//落ちるかどうか	true:落ちる
};

