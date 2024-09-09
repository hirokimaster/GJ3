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

public: // Setter
	void SetCamera(Camera* camera) { camera_ = camera; }

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

public: //BehaviorSetter
	void SetBehavior(Behavior behavior) { behaviorRequest_ = behavior; }

private: // Behavior変数
	// 振る舞い
	Behavior behavior_ = Behavior::kRoot;
	// 次の振る舞いリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

private:
	Camera* camera_;
	std::unique_ptr<Object3DPlacer> object_;
	WorldTransform worldTransform_;
	// プレイヤー用テクスチャ
	uint32_t skinTex_;
	float aniTime_ = 0;
	float duration_ = 0; // アニメ―ション全体の尺（単位は秒）

	float fallVelo_ = 0.0f;
	float gravity_ = 0.00098f;

	// Decelerationtimer
	float decelerationTimer_= 0.0f;
};

