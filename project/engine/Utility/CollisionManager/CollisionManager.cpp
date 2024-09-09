#include "CollisionManager.h"

void CollisionManager::CheckAllCollision() {

	std::list<Collider*>::iterator itrA = colliders_.begin();

	for (; itrA != colliders_.end(); ++itrA) {

		Collider* colliderA = *itrA;

		std::list<Collider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != colliders_.end(); ++itrB) {
			Collider* colliderB = *itrB;
			//当たり判定処理
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

void CollisionManager::CheckCollisionPair(Collider* cA, Collider* cB) {

	//フィルタリング
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0) {
		return;
	}
	//当たり判定の計算開始
	Vector3 cApos = cA->GetWorldPosition();
	Vector3 cBpos = cB->GetWorldPosition();

	Vector3 cAScale = cA->GetScale();
	Vector3 cBScale = cB->GetScale();

	AABB cAaabb{};
	cAaabb.min = cApos - cAScale;
	cAaabb.max = cApos + cAScale;

	AABB cBaabb{};
	cBaabb.min = cBpos - cBScale;
	cBaabb.max = cBpos + cBScale;

	if (CheckAABBColision(cAaabb, cBaabb)) {
		cA->OnCollision();
		cB->OnCollision();
	}

}

bool CollisionManager::CheckBallCollision(Vector3 v1, float v1Radious, Vector3 v2, float v2Radious)
{
	float x = (v2.x - v1.x);
	float y = (v2.y - v1.y);
	float z = (v2.z - v1.z);

	float position = (x * x) + (y * y) + (z * z);

	float radious = v1Radious + v2Radious;


	if (position <= (radious * radious)) {
		return true;
	}
	else {
		return false;
	}


}

bool CollisionManager::CheckAABBColision(const AABB& a, const AABB& b)
{
	if ((a.min.x <= b.max.x && a.max.x >= b.min.x) && (a.min.y <= b.max.y && a.max.y >= b.min.y) &&
		(a.min.z <= b.max.z && a.max.z >= b.min.z)) {

		return true;
	}

	return false;
}
