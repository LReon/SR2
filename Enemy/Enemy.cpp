#include "Enemy.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <cmath>

// 初期化
void Enemy::Initialize(Camera* camera) {
	model_ = Model::CreateFromOBJ("enemy", true);
	
	worldTransform.Initialize();
	worldTransform.scale_.x += 2.0f;
	worldTransform.scale_.y += 2.0f;
	worldTransform.scale_.z += 2.0f;
	worldTransform.translation_.x = 20.0f;
	worldTransform.UpdateMatrix();
	camera_ = camera;
	
}

void Enemy::Fire() {
	// 弾の速度
	const float kBulletSpeed = -1.0f;
	Vector3 velocity(kBulletSpeed, 0, 0);

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(camera_, worldTransform.translation_, velocity);
	enemyBullets_.push_back(newBullet);
}

// 更新
void Enemy::Update() { 

	// 敵のフェーズ
	switch (phase_) { 
		case Enemy::Phase::Circle:
		CircleMove();

		break;

		case Enemy::Phase::UpDown:
		UpDownMove();

		break;

		case Enemy::Phase::Infinite:
		InfiniteMove();

		break;

	}

	// フェーズ切り替え用カウント
	if (hp <= 70 && hp >= 40) {
		phase_ = Phase::UpDown;
	
	}
	else if (hp <= 30) {
		phase_ = Phase::Infinite;
		
	}


	// 弾発射処理
	fireTimer_++;
	if (fireTimer_ >= kFireInterval) {
		Fire();
		fireTimer_ = 0;
	}
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

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






