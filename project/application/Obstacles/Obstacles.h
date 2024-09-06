#pragma once
#include <memory>
#include "engine/Transform/WorldTransform.h"
#include "engine/Object3DPlacer/Object3DPlacer.h"
#include "engine/Camera/Camera.h"
#include "engine/Utility/CollisionManager/CollisionManager.h"

class Player;
class Obstacles : public Collider
{
public:
	void Init(Vector3 translate);
	void Update();
	void Draw(Camera& camera);
public: // Setter
	void SetCamera(Camera& camera) { camera_ = camera; }
	void SetPlayer(Player* player) { player_ = player; }

public: // Collider
	Vector3 GetWorldPosition() override;
	void OnCollision() override;
private:
	Camera camera_;
	WorldTransform worldTransform_;
	std::unique_ptr<Object3DPlacer> object_;
	uint32_t skinTex_;
	Player* player_ = nullptr;
};

