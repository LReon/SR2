#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

/// <summary>
/// プレイヤーの弾の動きを司るクラス
/// </summary>
class PlayerBullet {

private:
	// キーボード入力
	Input* input_ = nullptr;

	// 速度
	Vector3 velocity_;

	// デスフラグ
	bool isDead_ = false;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;

	// 寿命
	static const int32_t kLifeTime = 60;

	float radius_ = 1.0f;

	// モデル
	Model* model_ = nullptr;

	// カメラ
	Camera* camera_;


public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">ゲームシーンからカメラを受け取る</param>
	/// <param name="position">初期位置</param>
	/// <param name="velocity">速度</param>
	void Initialize(Camera* camera,const Vector3& position,const Vector3& velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// キーボード入力
	Input* GetInput() const { return input_; }

	// 速度
	Vector3 GetVelocity() const { return velocity_; }
	
	
	bool GetIsDead() const { return isDead_; }
	int32_t GetDeathTimer() const { return deathTimer_; }

	/// <summary>
	/// 弾の死亡判定
	/// </summary>
	/// <returns>弾が死んだらtrueを返す</returns>
	bool IsDead() const { return isDead_; }

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック
	/// </summary>
	void OnCollision();

	float GetRadius() const { return radius_; }
	// ワールド変換データ
	WorldTransform worldTransform;

};
