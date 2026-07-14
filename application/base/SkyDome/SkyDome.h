#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class SkyDome {

public:
	// 初期化
	void Initialize(Camera* camera);
	// 更新
	void Update();
	// 描画
	void Draw();

private:
	// モデル
	Model* model_ = nullptr;
	// ワールド変換情報
	WorldTransform worldTransform_;
	
	Camera* camera_ = nullptr;

};
