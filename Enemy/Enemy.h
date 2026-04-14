#pragma once
#include <KamataEngine.h>
#include "EnemyBullet.h"
#include "Player.h"

using namespace KamataEngine;

class Player;

/// <summary>
/// 敵の動きを司るクラス
/// </summary>
class Enemy {


public:

	// 行動フェーズ
	enum class Phase {
		Circle,
		UpDown,
		Infinite
	};

	// 初期フェーズ
	Phase phase_ = Phase::Circle;

	/// <summary>
	// 初期化
	/// </summary>
	/// <param name="camera">カメラをゲームシーンから受け取る </param>
	void Initialize(Camera* camera);

	/// <summary>
	/// 弾の発射
	/// </summary>
	void Fire();
	EnemyBullet* enemyBullet_ = nullptr;
	std::list<EnemyBullet*> enemyBullets_;

	// 発射間隔
	static const int kFireInterval = 30;

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 円運動
	/// </summary>
	void CircleMove();
	float theta = 0.0f;
	float radius = 10.0f;
	float angleStep = 0.05f;
	float time = 0.0f;
	float centerX = 20.0f;
	float centerY = 0.0f;

	/// <summary>
	/// 上下運動
	/// </summary>
	void UpDownMove();
	float moveTime = 0.0f;// 時間経過を記録する変数
	float amplitude = 10.0f;// 上下運動の振幅
	float frequency = 0.5f;// 周期

	void InfiniteMove();
	float infiniteTime = 0.0f;
	float a = 10.0f; // 軌道のサイズ

	
		

	

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック
	/// </summary>
	
	// 弾リストを取得
	const std::list<EnemyBullet*>& GetBullets() const { return enemyBullets_; }

	float radius_ = 2.0f;
	int32_t hp = 100;

	bool isDead_ = false;
	bool IsDead() const { return isDead_; }
	void OnCollision() { 
		hp -= 10;
		if (hp <= 0) {
			isDead_ = true;
			
		}
	}

	WorldTransform worldTransform;
private:

	Model* model_ = nullptr;

	// カメラ
	Camera* camera_;

	// 発射タイマー
	int32_t fireTimer_ = 0;

};
