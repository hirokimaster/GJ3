#pragma once
#include <memory>
#include "engine/Object3DPlacer/Object3DPlacer.h"
#include "engine/Transform/WorldTransform.h"
#include "engine/Camera/Camera.h"
class Player
{
public:

	void Init();
	void Update();
	void Draw(Camera& camera);

	void Move();
	void Fall();
public: // Setter
	void SetCamera(Camera* camera) { camera_ = camera; }

public: // Debug
	// 調整項目の適用
	void ApplyGlobalVariables();
private:
	Camera* camera_;
	std::unique_ptr<Object3DPlacer> object_;
	WorldTransform worldTransform_;
	// プレイヤー用テクスチャ
	uint32_t skinTex_;
	float aniTime_ = 0;
	float duration_ = 0; // アニメ―ション全体の尺（単位は秒）
};

