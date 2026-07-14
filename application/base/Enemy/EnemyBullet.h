#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include <string>
#include "../Object/Bullet.h"

/// <summary>
/// 敵の弾の動きを司るクラス
/// </summary>
class EnemyBullet : public BulletBase{

private:
	// 寿命（クラス固有）
	static const int32_t kLifeTime = 250;

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

	void SetRadius(float r) { BulletBase::SetRadius(r); }
	void SetModelName(const std::string& name) { BulletBase::SetModelName(name); }

	// ゲッター
	Vector3 GetVelocity() const { return BulletBase::GetVelocity(); }
	int32_t GetDeathTimer() const { return BulletBase::GetDeathTimer(); }
	bool GetIsDead() const { return BulletBase::GetIsDead(); }
	bool IsDead() const { return BulletBase::GetIsDead(); }
	float GetRadius() const { return BulletBase::GetRadius(); }


};
