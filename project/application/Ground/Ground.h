#pragma once
#include <memory>
#include "engine/Transform/WorldTransform.h"
#include "engine/Object3DPlacer/Object3DPlacer.h"
#include "engine/Camera/Camera.h"

class Ground
{
public:
	void Init();
	void Update();
	void Draw(Camera& camera);
public: // Setter
	void SetCamera(Camera& camera) { camera_ = camera; }
private:
	Camera camera_;
	WorldTransform worldTransform_;
	std::unique_ptr<Object3DPlacer> object_;
	uint32_t skinTex_;
};
