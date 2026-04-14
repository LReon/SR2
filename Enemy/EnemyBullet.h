#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

/// <summary>
/// 敵の弾の動きを司るクラス
/// </summary>
class EnemyBullet {

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">カメラをゲームシーンから受け取る </param>
	/// <param name="position">弾の初期位置 </param>
	/// <param name="velocity">弾の速度 </param>
	void Initialize(Camera* camera, const Vector3& position, const Vector3& velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// 速度
	Vector3 velocity_;

	// 寿命
	static const int32_t kLifeTime = 60;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;

	/// <summary>
	/// 弾の死亡判定
	/// </summary>
	/// <returns>死んだらtrueを返す</returns>
	bool IsDead() const { return isDead_; }

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック
	/// </summary>
	void OnCollision();

	float radius_ = 1.0f;

	WorldTransform worldTransform;
private:

	Model* model_ = nullptr;

	// カメラ
	Camera* camera_;

};
