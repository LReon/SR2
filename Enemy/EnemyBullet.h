#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include <string>
#include "../Object/IObject.h"

/// <summary>
/// 敵の弾の動きを司るクラス
/// </summary>
class EnemyBullet : public IObject{

private:
	Model* model_ = nullptr;

	// カメラ
	Camera* camera_;

	// 速度
	Vector3 velocity_;

	// 寿命
	static const int32_t kLifeTime = 250;

	// デスタイマー
	int32_t deathTimer_ = kLifeTime;

	// デスフラグ
	bool isDead_ = false;

	float radius_ = 1.0f;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">カメラをゲームシーンから受け取る </param>
	/// <param name="position">弾の初期位置 </param>
	/// <param name="velocity">弾の速度 </param>
	// modelName: リソース名（例: "enemyBullet"）
	void Initialize(Camera* camera, const Vector3& position, const Vector3& velocity, int life = kLifeTime, const std::string& modelName = "playerBullet");

	// プールから再利用される際に呼ぶリセット
	void Reset();

	void SetRadius(float r) { radius_ = r; }
	void SetModelName(const std::string& name) { modelName_ = name; }

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 時間経過で消滅
	/// </summary>
	void LifeTime();

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	// 速度
	Vector3 GetVelocity() const { return velocity_; }
	
	// デスタイマー
	int32_t GetDeathTimer() const { return deathTimer_; }
	
	// デスフラグ
	bool GetIsDead() const { return isDead_; }

	/// <summary>
	/// 弾の死亡判定
	/// </summary>
	/// <returns>死んだらtrueを返す</returns>
	bool IsDead() const { return isDead_; }

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック
	/// </summary>
	void OnCollision()override;

	float GetRadius() const { return radius_; }

	WorldTransform worldTransform;
	std::string modelName_ = "playerBullet";


};
