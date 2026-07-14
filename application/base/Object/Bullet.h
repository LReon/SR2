#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

#include "IObject.h"

class BulletBase : public IObject {

protected:
	// モデル
	Model* model_ = nullptr;
	// カメラ
	Camera* camera_ = nullptr;
	// 速度
	Vector3 velocity_;
	// デスタイマー
	int32_t deathTimer_ = 0;
	// デスフラグ
	bool isDead_ = false;
	// 半径
	float radius_ = 1.0f;

public:
	// ワールド変換データ
	WorldTransform worldTransform;
	std::string modelName_ = "bullet";

	// 初期化（デフォルト実装）
	virtual void Initialize(Camera* camera, const Vector3& position, const Vector3& velocity, int life = 60, const std::string& modelName = "bullet");

	// プールから再利用時に呼ぶ（派生でオーバーライド可）
	virtual void Reset();

	// 移動
	virtual void Move();

	// 時間経過で消滅
	virtual void LifeTime();

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

	// 衝突
	void OnCollision() override;

	// 各種ゲッター
	Vector3 GetVelocity() const { return velocity_; }
	bool GetIsDead() const { return isDead_; }
	int32_t GetDeathTimer() const { return deathTimer_; }
	float GetRadius() const { return radius_; }
	void SetRadius(float r) { radius_ = r; }
	void SetModelName(const std::string& name) { modelName_ = name; }
};
