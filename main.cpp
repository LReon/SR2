#include <Windows.h>
#include "KamataEngine.h"
#include "GameScene.h"
#include "TitleScene.h"

using namespace KamataEngine;

GameScene* gameScene = nullptr;
TitleScene* titleScene = nullptr;

// シーン（型）
enum class Scene {
	kTitle,
	kGame,
};

// シーン（現在のシーン）
Scene scene;


void ChangeScene() {
	switch (scene) {
	case Scene::kTitle:
		if (titleScene->IsFinished()) {
			scene = Scene::kGame;
			// 旧シーンの解放
			delete titleScene;
			titleScene = nullptr;
			// 新シーンの生成と初期化
			gameScene = new GameScene();
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		if (gameScene->IsFinished()) {
			scene = Scene::kTitle;
			// 旧シーンの解放
			delete gameScene;
			gameScene = nullptr;
			// 新シーンの生成と初期化
			titleScene = new TitleScene();
			titleScene->Initialize();
		}
		break;
	
	}
}

void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();
		break;
	case Scene::kGame:
		gameScene->Update();
		break;
	}
}

void DrawScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
	// エンジンの初期化
	KamataEngine::Initialize(L"LE3D_18_フジワラ_リオ");

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 最初のシーンの初期化
	scene = Scene::kTitle;

	// タイトルシーンのインスタンスの生成
	titleScene = new TitleScene();
	// タイトルシーンの初期化
	titleScene->Initialize();

	

	// メインループ
	while (true) {
	
	//エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		ChangeScene();

		// 更新
		UpdateScene();
		

		// 描画開始
		dxCommon->PreDraw();

		// シーンごとの描画
		DrawScene();

		// 描画終了
		dxCommon->PostDraw();
	
		if (Input::GetInstance()->TriggerKey(DIK_ESCAPE)) {
			break;
		}
	}

		// ゲームシーンの解放
		delete gameScene;
		// nullptrの代入
		gameScene = nullptr;
	
		// エンジンの終了処理
		KamataEngine::Finalize();
	return 0;
	
}


