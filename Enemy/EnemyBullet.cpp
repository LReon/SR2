#include "EnemyBullet.h"

// 初期化
void EnemyBullet::Initialize(Camera* camera, const Vector3& position, const Vector3& velocity, int life, const std::string& modelName) {
	// モデル名を保持
	modelName_ = modelName;
	// モデルは既に生成済みかもしれないので重複生成を避ける
	if (!model_) model_ = Model::CreateFromOBJ(modelName_.c_str(), true);
	velocity_ = velocity;
	worldTransform.Initialize();
	worldTransform.translation_ = position;
	worldTransform.rotation_.y = 3.141592654f; // 弾を180度回転させる
	worldTransform.UpdateMatrix();
	camera_ = camera;

	// 再利用時の状態をリセット
	isDead_ = false;
	deathTimer_ = life;
}

// 移動
void EnemyBullet::Move() {
	// 速度に基づいて位置を更新
	worldTransform.translation_.x += velocity_.x;
}

// 時間経過で消滅
void EnemyBullet::LifeTime() {
	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

// 更新
void EnemyBullet::Update() {
	// 速度に基づいて位置を更新
	Move();
	// 時間経過でデス
	LifeTime();

	worldTransform.UpdateMatrix(); // ワールド行列の更新
}

// 描画
void EnemyBullet::Draw() {
	model_->Draw(worldTransform, *camera_); 
}

// 衝突を検出したら呼び出されるコールバック
void EnemyBullet::OnCollision() {
	isDead_ = true; 
}

void EnemyBullet::Reset() {
	isDead_ = false;
	deathTimer_ = kLifeTime;
	// worldTransform は Initialize で設定されるためここでは触らない
}


