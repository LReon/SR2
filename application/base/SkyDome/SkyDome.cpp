#include "SkyDome.h"
#include "../../ect/Config/GameConfig.h"

// 初期化
void SkyDome::Initialize(Camera* camera) {
	model_ = Model::CreateFromOBJ(GameConfig::skyDomeModelName.c_str(),true);
	worldTransform_.Initialize();
	worldTransform_.scale_.x += 10.0f;
	worldTransform_.scale_.y += 10.0f;
	worldTransform_.scale_.z += 10.0f;
	worldTransform_.translation_.z -= 50.0f;
	worldTransform_.UpdateMatrix();
	camera_ = camera;
}

// 更新
void SkyDome::Update() {
	
	worldTransform_.UpdateMatrix();
}
// 描画
void SkyDome::Draw() {
	model_->Draw(worldTransform_, *camera_);
}
