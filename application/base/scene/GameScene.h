#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Enemy.h"
#include "SkyDome.h"
#include "EnemyBullet.h"

using namespace KamataEngine;

/// <summary>
/// 各クラスをまとめて管理するクラス
/// </summary>
class GameScene {

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	
	bool IsCircleCollision(const Vector3& posA, float radiusA, const Vector3& posB, float radiusB);
	
	void PlayerBulletEnemyCollision();

	void EnemyBulletPlayerCollision();

	// 終了フラグ
	bool finished_ = false;
	// デスフラグのgetter
	bool IsFinished() const { return finished_; }

private:
	Player* player_;
	Enemy* enemy_;
	SkyDome* skyDome_;
	EnemyBullet* enemyBullet_;

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	uint32_t textureHandle_ = 0;

	Model* model_ = nullptr;

	// カメラ
	Camera* camera_;
};
