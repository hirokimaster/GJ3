#pragma once
#include "application/Gimmick/Thunder/Thunder.h"
#include "application/Player/Player.h"
#include "engine/Utility/CollisionManager/CollisionManager.h"

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

	/// <summary>
	/// コリジョンマネージャに登録する
	/// </summary>
	void ColliderPush(CollisionManager* collisionManager);

#pragma region getter


#pragma endregion

#pragma region setter

	void SetPlayer(Player* player) { player_ = player; }

#pragma endregion

private:

	/// <summary>
	/// ギミックに当たったら
	/// </summary>
	void Collision();

private:
	std::unique_ptr<Thunder> thunder_;
	Player* player_ = nullptr;

};
