#include "Enemy.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <cmath>
#include "../State/Enemy/CircleMoveState.h"
#include "../../ect/Config/GameConfig.h"

// 初期化
void Enemy::Initialize(Camera* camera) {
	model_ = Model::CreateFromOBJ(GameConfig::enemyModelName.c_str(), true);
	
	worldTransform.Initialize();
	worldTransform.scale_.x += 2.0f;
	worldTransform.scale_.y += 2.0f;
	worldTransform.scale_.z += 2.0f;
	worldTransform.translation_.x = 20.0f;
	worldTransform.UpdateMatrix();
	camera_ = camera;
	// ★ 初期フェーズを設定（これが必須）
	SetState(std::make_unique<CircleMoveState>());
}

// 弾の発射
void Enemy::Fire() {
	// 弾の速度
	const float kBulletSpeed = GameConfig::enemyBulletSpeed;
	Vector3 velocity(kBulletSpeed, 0, 0);

	// プールから弾を取得して初期化
	EnemyBullet* newBullet = bulletPool_.Allocate();
	if (newBullet) {
		newBullet->Initialize(camera_, worldTransform.translation_, velocity);
		enemyBullets_.push_back(newBullet);
	}
}

// フェーズ管理
void Enemy::ManagePhase() {

	


}

// 弾の管理
void Enemy::ManageBullets() {
	fireTimer_++;
	if (fireTimer_ >= fireInterval_) {
		Fire();
		fireTimer_ = 0;
	}
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}
	// 死んだ弾はプールへ返却
	enemyBullets_.remove_if([this](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			bullet->Reset();
			this->bulletPool_.Release(bullet);
			return true;
		}
		return false;
	});
}

// 更新
void Enemy::Update() { 

	if (state_) {
		state_->Update(*this);
	}

	// 弾発射処理
	ManageBullets();

	worldTransform.UpdateMatrix();
}

// 描画
void Enemy::Draw() {
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw();
	}
	model_->Draw(worldTransform, *camera_);
}

// 円運動
void Enemy::CircleMove() {

	theta += angleStep; // 角度を更新

	if (theta > 2.0f * float(M_PI)) { 
		theta -= 2.0f * float(M_PI);
	}

	worldTransform.translation_.x = centerX + radius * cosf(theta); // X座標の計算
	worldTransform.translation_.y = centerY + radius * sinf(theta); // Y座標の計算

}

// 上下運動
void Enemy::UpDownMove() {

	worldTransform.translation_.x = 20.0f; // X座標は固定

	// 時間を加算
	moveTime += 1.0f / 60.0f;

	// Y座標を上下に変化させる
	worldTransform.translation_.y = amplitude * sinf(2.0f * static_cast<float>(M_PI) * frequency * moveTime);

}

// 無限運動
void Enemy::InfiniteMove() {

	// 初期化時の中心座標
	Vector3 center = {20.0f, 0.0f, 0.0f};
	
	infiniteTime += 0.05f; // 速度調整

	a = 15.0f; // 軌道のサイズ

	// 八の字運動の計算
	worldTransform.translation_.x = center.x + a * sin(infiniteTime);
	worldTransform.translation_.y = center.y + a * sin(infiniteTime) * cos(infiniteTime);
	worldTransform.translation_.z = 0.0f; // 平面上に固定

}

// 衝突を検出したら呼び出されるコールバック
void Enemy::OnCollision() {
	hp -= 10;
	if (hp <= 0) {
		isDead_ = true;
	}
}






