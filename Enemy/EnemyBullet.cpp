#include "EnemyBullet.h"

void EnemyBullet::Initialize(Camera* camera, const Vector3& position, const Vector3& velocity) {
	model_ = Model::CreateFromOBJ("enemyBullet", true);
	velocity_ = velocity;
	worldTransform.Initialize();
	worldTransform.translation_ = position;
	worldTransform.UpdateMatrix();
	camera_ = camera;
}

void EnemyBullet::Update() {
	worldTransform.translation_.x += velocity_.x;
	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	worldTransform.UpdateMatrix();
}

void EnemyBullet::Draw() {
	model_->Draw(worldTransform, *camera_); 
}

void EnemyBullet::OnCollision() {
	isDead_ = true; }


