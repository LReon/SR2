#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

#include "../Object/Bullet.h"

/// <summary>
/// プレイヤーの弾の動きを司るクラス
/// </summary>
class PlayerBullet : public BulletBase{

private:
	// キーボード入力
	Input* input_ = nullptr;

	// 寿命（クラス固有）
	static const int32_t kLifeTime = 60;

public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">ゲームシーンからカメラを受け取る</param>
	/// <param name="position">初期位置</param>
	/// <param name="velocity">速度</param>
	void Initialize(Camera* camera,const Vector3& position,const Vector3& velocity, int life = kLifeTime, const std::string& modelName = "playerBullet");

	// プールからの再利用時に呼ぶ
	void Reset();

	// 公開API
	void SetRadius(float r) { BulletBase::SetRadius(r); }
	void SetModelName(const std::string& name) { BulletBase::SetModelName(name); }

	// キーボード入力
	Input* GetInput() const { return input_; }

	// ゲッター（基底のメンバーを利用）
	Vector3 GetVelocity() const { return BulletBase::GetVelocity(); }
	bool GetIsDead() const { return BulletBase::GetIsDead(); }
	int32_t GetDeathTimer() const { return BulletBase::GetDeathTimer(); }
	bool IsDead() const { return BulletBase::GetIsDead(); }
	float GetRadius() const { return BulletBase::GetRadius(); }

};
