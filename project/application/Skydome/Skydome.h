#pragma once
#include <memory>
#include "engine/Transform/WorldTransform.h"
#include "engine/Object3DPlacer/Object3DPlacer.h"
#include "engine/Camera/Camera.h"

class Skydome
{
public:
	void Init();
	void Update();
	void Draw(Camera* camera);

public: // Setter
private:
	Camera* camera_ = nullptr;
	WorldTransform worldTransform_;
	std::unique_ptr<Object3DPlacer> object_;
	uint32_t skinTex_;
};

