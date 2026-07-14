#include "TitleScene.h"

void TitleScene::Initialize() { 
	input_ = Input::GetInstance(); 
	
}

void TitleScene::Update() {

	// タイトルの終了条件
	if (input_->TriggerKey(DIK_SPACE)) {
		finished_ = true;
	}
}

void TitleScene::Draw() {

	//sprite_->Draw(); 
	
}

TitleScene::~TitleScene() {}


