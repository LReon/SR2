#include "GameScene.h"
// 初期化
void GameScene::Initialize() {

	camera_ = new Camera();
	camera_->Initialize();
	
	worldTransform_.Initialize();

	player_ = new Player();
	player_->Initialize(camera_);

	enemy_ = new Enemy();
	enemy_->Initialize(camera_);

	skyDome_ = new SkyDome();
	skyDome_->Initialize(camera_);

	textureHandle_ = TextureManager::Load("number.png");
	model_ = Model::Create();

}

// 更新
void GameScene::Update() {
	
	player_->Update();
	if (enemy_->IsDead() == false) {
		enemy_->Update();
		PlayerBulletEnemyCollision();
		
	}
	
	skyDome_->Update();
	
	EnemyBulletPlayerCollision();
}

// 描画
void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Sprite::PreDraw(dxCommon->GetCommandList());
	Sprite::PostDraw();

	
	Model::PreDraw(dxCommon->GetCommandList());
	skyDome_->Draw();
	player_->Draw();
	if (enemy_->IsDead() == false) {
		enemy_->Draw();
	}

	model_->Draw(worldTransform_, *camera_, textureHandle_);
	Model::PostDraw();
}

// 衝突判定
bool GameScene::IsCircleCollision(const Vector3& posA, float radiusA, const Vector3& posB, float radiusB) { 
	Vector3 diff = {posA.x - posB.x, posA.y - posB.y,posA.z - posB.z};

	float distSq = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	float radiusSum = radiusA + radiusB;
	return distSq <= radiusSum * radiusSum;
}


// 衝突判定と応答(プレイヤーの弾と敵)
void GameScene::PlayerBulletEnemyCollision() {

	
	for (PlayerBullet* pb : player_->GetBullets()) {
		
			if (IsCircleCollision(pb->worldTransform.translation_, pb->GetRadius(), enemy_->GetPosition(), enemy_->GetRadius())) {
				pb->OnCollision();
				enemy_->OnCollision(); // HP制 or 即死
				
				
			}
		}

}

// 衝突判定と応答(敵の弾とプレイヤー)
void GameScene::EnemyBulletPlayerCollision() {

	for (EnemyBullet* eb : enemy_->GetBullets()) {
		
			if (IsCircleCollision(eb->worldTransform.translation_, eb->GetRadius(), player_->GetPosition(), player_->GetRadius())) {
				eb->OnCollision();
				player_->OnCollision(); // HP制 or 即死 
			} } 

}






