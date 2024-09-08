#pragma once
#include "engine/Object3DPlacer/Object3DPlacer.h"

class Thunder {
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

private:
	std::unique_ptr<Object3DPlacer> object_;
	WorldTransform worldTransform_{};


};
