#pragma once
#include "engine/Object3DPlacer/Object3DPlacer.h"
#include "engine/TextureManager/TextureManager.h"
#include "engine/Input/Input.h"
#include "application/Player/Player.h"
#include "engine/Utility/CollisionManager/Collider/Collider.h"

class Thunder : public Collider {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera& camera);

#pragma region getter

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	const WorldTransform* GetTarget() { return target_; }

	bool GetIsFall() { return isFall_; }

	const Vector3& GetScale()override { return worldTransform_.scale; }

	Vector3 GetWorldPosition()override;

	bool GetIsHit() { return isHit_; }

#pragma endregion

#pragma region setter

	void SetTarget(const WorldTransform* target) { target_ = target; }

	void SetIsHit(bool isHit) { isHit_ = isHit; }

	void SetFallTimer(uint32_t fallTimer) { fallTimer_ = fallTimer, kFallInterval_ = fallTimer; }

#pragma endregion

private:
	/// <summary>
	/// 動き
	/// </summary>
	void Move();

	/// <summary>
	/// 落ちる
	/// </summary>
	void Fall();

	/// <summary>
	/// 衝突判定のとこ
	/// </summary>
	void OnCollision()override;

private:
	// 雷
	std::unique_ptr<Object3DPlacer> object_;
	WorldTransform worldTransform_{};
	uint32_t texHandle_ = 0;
	bool isFall_ = false;
	bool isHit_ = false;
	uint32_t fallTimer_ = 120;
	uint32_t kFallInterval_ = 180;

	std::unique_ptr<Object3DPlacer> preline_;
	WorldTransform worldTransformPreline_{};
	uint32_t texHandlePreline_ = 0;
	uint32_t blinkingTimer_ = 60;
	bool isBlinking_ = false;
	const WorldTransform* target_ = nullptr;
};