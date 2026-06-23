#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>


// 初期化
void Player::Initialize(Camera* camera) {
	// プレイヤーモデルの生成
	model_ = Model::CreateFromOBJ("player", true);
	// 入力の取得
	input_ = Input::GetInstance();
	// ワールド変換の初期化
	worldTransform.Initialize();
	// カメラの設定
	camera_ = camera;              
}

// 移動
void Player::Move() {

	// WASDキーで移動
	if (input_->GetInstance()->PushKey(DIK_W)) {
		worldTransform.translation_.y += 1.0f;
	}
	if (input_->GetInstance()->PushKey(DIK_S)) {
		worldTransform.translation_.y -= 1.0f;
	}
	if (input_->GetInstance()->PushKey(DIK_A)) {
		worldTransform.translation_.x -= 1.0f;
	}
	if (input_->GetInstance()->PushKey(DIK_D)) {
		worldTransform.translation_.x += 1.0f;
	}

}

// 攻撃
void Player::Attack() {

	// スペースキーが押されたら弾を発射
	if (input_->GetInstance()->TriggerKey(DIK_SPACE)) {
		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(kBulletSpeed, 0, 0);
		
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(camera_,worldTransform.translation_,velocity);
		playerBullets_.push_back(newBullet);
	}
}

// 弾の管理
void Player::ManageBullets() {

	// 弾の更新
	for (PlayerBullet* bullet : playerBullets_) {
		bullet->Update();
	}

	// 死んだ弾の削除
	playerBullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
}

// 更新
void Player::Update() {

	// 移動処理
	Move(); 

	// 攻撃処理
	Attack();

	ManageBullets();

	// ワールド行列の更新
	worldTransform.UpdateMatrix();
}

// 描画
void Player::Draw() {
	// プレイヤーの描画
	model_->Draw(worldTransform, *camera_); 
	for (PlayerBullet* bullet : playerBullets_) {
		bullet->Draw();
	}
}

// 衝突を検出したら呼び出されるコールバック
void Player::OnCollision() {
	isDead_ = true; // 必要ならアニメーションやSEなど
}

// デストラクタ
Player::~Player() {
	// 弾の解放
	delete playerBullet_; 
}


