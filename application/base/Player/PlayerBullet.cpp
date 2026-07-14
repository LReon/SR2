#include "PlayerBullet.h"
#define _USE_MATH_DEFINES
#include <math.h>

// 初期化
void PlayerBullet::Initialize(Camera* camera, const Vector3& position, const Vector3& velocity, int life, const std::string& modelName) {
	// 基底の初期化を使う
	BulletBase::Initialize(camera, position, velocity, life, modelName);
	// プレイヤー弾固有: 入力取得
	input_ = Input::GetInstance();
}

void PlayerBullet::Reset() {
	isDead_ = false;
	deathTimer_ = kLifeTime;
}

