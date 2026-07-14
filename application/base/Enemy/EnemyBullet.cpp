#include "EnemyBullet.h"

// 初期化
void EnemyBullet::Initialize(Camera* camera, const Vector3& position, const Vector3& velocity, int life, const std::string& modelName) {
	// 基底の初期化
	BulletBase::Initialize(camera, position, velocity, life, modelName);
	// 敵弾固有: 180度回転
	worldTransform.rotation_.y = 3.141592654f;
	worldTransform.UpdateMatrix();
}

void EnemyBullet::Reset() {
	isDead_ = false;
	deathTimer_ = kLifeTime;
	// worldTransform は Initialize で設定されるためここでは触らない
}


