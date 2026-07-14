#include "Player.h"
#include <unordered_map>
#include "../../ect/Config/ConfigLoader.h"
#include "../../ect/Config/GameConfig.h"
#define _USE_MATH_DEFINES
#include <math.h>


// 初期化
void Player::Initialize(Camera* camera) {
	// プレイヤーモデルの生成
	model_ = Model::CreateFromOBJ(GameConfig::playerModelName.c_str(), true);
	// 入力の取得
	input_ = Input::GetInstance();
	// ワールド変換の初期化
	worldTransform.Initialize();
	// カメラの設定
	camera_ = camera;              

	// プレイヤー弾の設定を読み込む（データ駆動）
	std::unordered_map<std::string, BulletConfig> bullets;
	ConfigLoader::LoadBulletsConfig(GameConfig::bulletsConfigPath, bullets);
	auto it = bullets.find("player_small");
	if (it != bullets.end()) {
		playerBulletConfig_ = it->second;
	}
}

// 移動
void Player::Move() {

	// WASDキーで移動
	if (input_->GetInstance()->PushKey(DIK_W)) {
		worldTransform.translation_.y += GameConfig::playerMoveStep;
	}
	if (input_->GetInstance()->PushKey(DIK_S)) {
		worldTransform.translation_.y -= GameConfig::playerMoveStep;
	}
	if (input_->GetInstance()->PushKey(DIK_A)) {
		worldTransform.translation_.x -= GameConfig::playerMoveStep;
	}
	if (input_->GetInstance()->PushKey(DIK_D)) {
		worldTransform.translation_.x += GameConfig::playerMoveStep;
	}

}

// 攻撃
void Player::Attack() {

	// スペースキーが押されたら弾を発射
	if (input_->GetInstance()->TriggerKey(DIK_SPACE)) {
		// 弾の速度
		Vector3 velocity(playerBulletConfig_.speed, 0, 0);

		// プールから確保して初期化
		PlayerBullet* newBullet = bulletManager_.AllocateOne();
		if (newBullet) {
			newBullet->Initialize(camera_, worldTransform.translation_, velocity, playerBulletConfig_.life, playerBulletConfig_.model);
			newBullet->SetRadius(playerBulletConfig_.radius);
		}
	}
}

// 弾の管理
void Player::ManageBullets() {

	// BulletManager による一括更新と回収
	bulletManager_.UpdateAll();
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
	bulletManager_.DrawAll();
}

// 衝突を検出したら呼び出されるコールバック
void Player::OnCollision() {
	isDead_ = true; // 必要ならアニメーションやSEなど
}

// デストラクタ
Player::~Player() {
	// プールを使うため明示的な delete は不要。もし残弾があればプールへ返却する
	for (PlayerBullet* b : bulletManager_.GetActive()) {
		b->Reset();
		bulletPool_.Release(b);
	}
}


