#pragma once
#include <KamataEngine.h>
#include "../../ect/Config/GameConfig.h"
#include "EnemyBullet.h"
#include "../Player/Player.h"
#include "../Object/IObject.h"
#include "../State/Enemy/State.h"
#include "../Object/ObjectPool.h"
#include "../Object/BulletManager.h"

using namespace KamataEngine;

class Player;
/// <summary>
/// 敵の動きを司るクラス
/// </summary>
class Enemy : public IObject {
private:
	Model* model_ = nullptr;

	// カメラ
	Camera* camera_;

	// 発射タイマー
	int32_t fireTimer_ = 0;

	EnemyBullet* enemyBullet_ = nullptr;
	// 弾プール
	ObjectPool<EnemyBullet> bulletPool_{128};
	// 弾マネージャ
	BulletManager<EnemyBullet> bulletManager_{bulletPool_};

	// 発射間隔
	int fireInterval_ = GameConfig::enemyFireInterval;

	WorldTransform worldTransform;

	int32_t hp = GameConfig::enemyHp;

	bool isDead_ = false;

	float radius_ = GameConfig::enemyRadius;

	// State Pattern
	std::unique_ptr<IEnemyState> state_;

public:

	void SetState(std::unique_ptr<IEnemyState> next) {
		if (state_)
			state_->Exit(*this);
		state_ = std::move(next);
		state_->Enter(*this);
	}

	/// <summary>
	// 初期化
	/// </summary>
	/// <param name="camera">カメラをゲームシーンから受け取る </param>
	void Initialize(Camera* camera);

	/// <summary>
	/// 弾の発射
	/// </summary>
	void Fire();

	
	EnemyBullet* GetEnemyBullet() const { return enemyBullet_; }
	const std::list<EnemyBullet*>& GetEnemyBullets() const { return bulletManager_.GetActive(); }

	/// <summary>
	/// ゲッター
	/// </summary>
	Vector3 GetPosition() const { return worldTransform.translation_; }

	/// <summary>
	/// フェーズ管理
	/// </summary>
	void ManagePhase();

	/// <summary>
	/// 弾の管理
	/// </summary>
	void ManageBullets();
	

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	/// <summary>
	/// 円運動
	/// </summary>
	void CircleMove();
	float theta = 0.0f;
	float radius = GameConfig::enemyMoveRadius;
	float angleStep = GameConfig::enemyAngleStep;
	float time = 0.0f;
	float centerX = GameConfig::enemyCenterX;
	float centerY = GameConfig::enemyCenterY;

	/// <summary>
	/// 上下運動
	/// </summary>
	void UpDownMove();
	float moveTime = 0.0f;// 時間経過を記録する変数
	float amplitude = GameConfig::enemyAmplitude;// 上下運動の振幅
	float frequency = GameConfig::enemyFrequency;// 周期

	void InfiniteMove();
	float infiniteTime = 0.0f;
	float a = GameConfig::enemyA; // 軌道のサイズ

	
		

	

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック
	/// </summary>
	
	// 弾リストを取得
	const std::list<EnemyBullet*>& GetBullets() const { return bulletManager_.GetActive(); }

	
	
	float GetRadius() const { return radius_; }

	int32_t GetHp() const { return hp; }

	
	bool IsDead() const { return isDead_; }
	

	void OnCollision()override;


};
