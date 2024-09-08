#pragma once
#include "application/Gimmick/Thunder/Thunder.h"
#include "application/Player/Player.h"

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

#pragma region setter

	void SetPlayer(Player* player) { player_ = player; }

#pragma endregion

private:
	std::unique_ptr<Thunder> thunder_;
	Player* player_ = nullptr;

};
