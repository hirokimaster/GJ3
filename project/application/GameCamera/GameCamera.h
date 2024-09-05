#pragma once
#include "engine/Camera/Camera.h"
class GameCamera
{
public:
	void Init();
	void Update();
public: // Getter
	Camera &GetCamera() { return camera_; }

public: // Debug
	// 調整項目の適用
	void ApplyGlobalVariables();

private:
	Camera camera_;
};

