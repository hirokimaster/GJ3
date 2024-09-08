#pragma once
#include "application/Gimmick/Thunder/Thunder.h"

class Gimmick {
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
	std::unique_ptr<Thunder> thunder_;

};
