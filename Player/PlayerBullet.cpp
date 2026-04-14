#include "PlayerBullet.h"
#define _USE_MATH_DEFINES
#include <math.h>
void PlayerBullet::Initialize(Camera* camera, const Vector3& position, const Vector3& velocity) {
	// 弾モデルの生成
	model_ = Model::CreateFromOBJ("playerBullet",true);
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
}

void PlayerBullet::Update() { 
	 // 速度に基づいて位置を更新
	worldTransform.translation_.x += velocity_.x;
	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	worldTransform.UpdateMatrix(); // ワールド行列の更新
}

void PlayerBullet::Draw() { 
	model_->Draw(worldTransform, *camera_); // モデルの描画
}

void PlayerBullet::OnCollision() {
	isDead_ = true; // 衝突時に弾を消す
}

