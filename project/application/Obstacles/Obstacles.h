#pragma once
#include <memory>
#include "engine/Transform/WorldTransform.h"
#include "engine/Object3DPlacer/Object3DPlacer.h"
#include "engine/Camera/Camera.h"
#include "engine/Utility/CollisionManager/Collider/Collider.h"

class Player;
class Obstacles : public Collider
{
public:
	void Init(Vector3 translate,bool isMove);
	void Update();
	void Draw(Camera& camera);

public:
	void Move();

public: // Setter
	void SetCamera(Camera& camera) { camera_ = camera; }
	void SetPlayer(Player* player) { player_ = player; }

public: // Collider
	Vector3 GetWorldPosition() override;
	void OnCollision() override;
	const Vector3& GetScale()override { return worldTransform_.scale; }

private:
	Camera camera_;
	WorldTransform worldTransform_;
	std::unique_ptr<Object3DPlacer> object_;
	uint32_t skinTex_;
	Player* player_ = nullptr;

	bool isMove_ = false;
	float velo_ = 0.2f;
};

