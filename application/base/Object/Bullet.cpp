#include "Bullet.h"
#include <string>

void BulletBase::Initialize(Camera* camera, const Vector3& position, const Vector3& velocity, int life, const std::string& modelName) {
	modelName_ = modelName;
	if (!model_) model_ = Model::CreateFromOBJ(modelName_.c_str(), true);
	velocity_ = velocity;
	worldTransform.Initialize();
	worldTransform.translation_ = position;
	worldTransform.UpdateMatrix();
	camera_ = camera;

	isDead_ = false;
	deathTimer_ = life;
}

void BulletBase::Reset() {
	isDead_ = false;
	deathTimer_ = 60;
}

void BulletBase::Move() {
	worldTransform.translation_.x += velocity_.x;
}

void BulletBase::LifeTime() {
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void BulletBase::Update() {
	Move();
	LifeTime();
	worldTransform.UpdateMatrix();
}

void BulletBase::Draw() {
	if (model_) model_->Draw(worldTransform, *camera_);
}

void BulletBase::OnCollision() {
	isDead_ = true;
}
