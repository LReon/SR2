#include "EnemyBullet.h"

void EnemyBullet::Initialize(Camera* camera, const Vector3& position, const Vector3& velocity) {
	model_ = Model::CreateFromOBJ("playerBullet", true);
	velocity_ = velocity;
	worldTransform.Initialize();
	worldTransform.translation_ = position;
	worldTransform.rotation_.y = 3.141592654f; // 弾を180度回転させる
	worldTransform.UpdateMatrix();
	camera_ = camera;
}

void EnemyBullet::Update() {
	// 速度に基づいて位置を更新
	worldTransform.translation_.x += velocity_.x;
	// 時間経過でデス
	if (--deathTimer_ <= -100) {
		isDead_ = true;
	}
	worldTransform.UpdateMatrix(); // ワールド行列の更新
}

void EnemyBullet::Draw() {
	model_->Draw(worldTransform, *camera_); 
}

void EnemyBullet::OnCollision() {
	isDead_ = true; 
}


