// GameConfig.h
// 設定を JSON から読み込むための宣言
#pragma once

#include <string>

namespace GameConfig {
	// ロード (デフォルトの設定ファイルパス)
	void Load(const std::string& path = "Resources/config/game_config.json");

	// ウィンドウタイトル (UTF-8)
	extern std::string windowTitleUtf8;

	// 設定パス
	extern std::string bulletsConfigPath;
	extern std::string enemyConfigPath;

	// モデル名
	extern std::string playerModelName;
	extern std::string enemyModelName;
	extern std::string skyDomeModelName;

	// プレイヤー移動量
	extern float playerMoveStep;

	// 敵デフォルトパラメータ
	extern int enemyHp;
	extern int enemyFireInterval;
	extern float enemyRadius;
	extern float enemyAngleStep;
	extern float enemyCenterX;
	extern float enemyCenterY;
	extern float enemyMoveRadius;
	extern float enemyAmplitude;
	extern float enemyFrequency;
	extern float enemyA;
	extern float enemyBulletSpeed;

	// ヘルパー: UTF-8 -> wstring
	std::wstring WindowTitleW();
}
