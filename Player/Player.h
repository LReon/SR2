#pragma once

#include <list>
#include "PlayerBullet.h"



/// <summary>
/// プレイヤーの動きを司るクラス
/// </summary>
class Player {

private:
	// モデル
	Model* model_ = nullptr;

	// カメラ
	Camera* camera_;

	float radius_ = 0;
	

	// キーボード入力
	Input* input_ = nullptr;

	PlayerBullet* playerBullet_ = nullptr;
	std::list<PlayerBullet*> playerBullets_;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">カメラをゲームシーンから受け取る </param>
	void Initialize(Camera* camera);

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();
	PlayerBullet* GetPlayerBullet() const { return playerBullet_; }

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	Input* GetInput() const { 
		return input_; 
	}

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック
	/// </summary>
	

	/// <summary>
	/// 弾のリストを取得
	/// </summary>
	/// <returns>弾のリスト</returns>
	const std::list<PlayerBullet*>& GetBullets() const { return playerBullets_; }

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();
	
	float GetRadius() const { 
		return radius_;
	}

	void setRadius(float radius) {
		radius_ = radius;
	}

	bool isDead_ = false;
	bool IsDead() const { return isDead_; }
	void OnCollision() {
		isDead_ = true; // 必要ならアニメーションやSEなど 
	}

	// ワールド変換データ
	WorldTransform worldTransform;

};
