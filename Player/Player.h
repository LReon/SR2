#pragma once

#include <list>
#include "PlayerBullet.h"
#include "../Object/IObject.h"


/// <summary>
/// プレイヤーの動きを司るクラス
/// </summary>
class Player : IObject{

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

	// ワールド変換データ
	WorldTransform worldTransform;

	bool isDead_ = false;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">カメラをゲームシーンから受け取る </param>
	void Initialize(Camera* camera);

	/// <summary>	
	/// 移動
	/// </summary>
	void Move();
	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();
	PlayerBullet* GetPlayerBullet() const { return playerBullet_; }

	/// <summary>
	/// 弾の管理
	/// </summary>
	void ManageBullets();

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// キーボード入力
	/// </summary>
	Input* GetInput() const { 
		return input_; 
	}
	

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

	
	bool IsDead() const { return isDead_; }
	void OnCollision() override;
		

	Vector3 GetPosition() const { return worldTransform.translation_; }

};
