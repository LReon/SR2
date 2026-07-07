#include "PlayerBullet.h"
#define _USE_MATH_DEFINES
#include <math.h>

// 初期化
void PlayerBullet::Initialize(Camera* camera, const Vector3& position, const Vector3& velocity, int life, const std::string& modelName) {
	// モデル名を保存
	modelName_ = modelName;
	// モデルは重複生成を避ける
	if (!model_) model_ = Model::CreateFromOBJ(modelName_.c_str(), true);
	// 入力の取得
	input_ = Input::GetInstance();
	// ワールド変換の初期化
	worldTransform.Initialize();
	// 速度の設定
	velocity_ = velocity;
	// 初期位置の設定
	worldTransform.translation_ = position;
	// ワールド行列の更新
	worldTransform.UpdateMatrix(); 
	// カメラの設定
	camera_ = camera;                       

	// 再利用時の状態リセット
	isDead_ = false;
	deathTimer_ = life;
}

// 移動
void PlayerBullet::Move() {
	// 速度に基づいて位置を更新
	worldTransform.translation_.x += velocity_.x;
}

// 時間経過で消滅
void PlayerBullet::LifeTime() {
	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

// 更新
void PlayerBullet::Update() { 
	 // 速度に基づいて位置を更新
	Move();
	// 時間経過でデス
	LifeTime();
	worldTransform.UpdateMatrix(); // ワールド行列の更新
}

// 描画
void PlayerBullet::Draw() { 
	model_->Draw(worldTransform, *camera_); // モデルの描画
}

// 衝突を検出したら呼び出されるコールバック
void PlayerBullet::OnCollision() {
	isDead_ = true; // 衝突時に弾を消す
}

void PlayerBullet::Reset() {
	isDead_ = false;
	deathTimer_ = kLifeTime;
}

