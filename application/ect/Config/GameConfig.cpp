#include "GameConfig.h"
#include <fstream>
#include <sstream>
#include <windows.h>
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

namespace GameConfig {
	std::string windowTitleUtf8 = "LE3D_18_フジワラ_リオ";

	std::string bulletsConfigPath = "Resources/config/bullets.json";
	std::string enemyConfigPath = "Resources/config/enemy.json";

	std::string playerModelName = "player";
	std::string enemyModelName = "enemy";
	std::string skyDomeModelName = "skyDome";

	float playerMoveStep = 1.0f;

	int enemyHp = 100;
	int enemyFireInterval = 30;
	float enemyRadius = 2.0f;
	float enemyAngleStep = 0.05f;
	float enemyCenterX = 20.0f;
	float enemyCenterY = 0.0f;
	float enemyMoveRadius = 10.0f;
	float enemyAmplitude = 10.0f;
	float enemyFrequency = 0.5f;
	float enemyA = 10.0f;
	float enemyBulletSpeed = -2.0f;

	static std::string ReadFile(const std::string& path) {
		std::ifstream ifs(path);
		if (!ifs) return {};
		std::ostringstream ss;
		ss << ifs.rdbuf();
		return ss.str();
	}

	void Load(const std::string& path) {
		std::string raw = ReadFile(path);
		if (raw.empty()) return; // 既定値を使う
		try {
			auto j = json::parse(raw);
			if (j.contains("windowTitle") && j["windowTitle"].is_string()) windowTitleUtf8 = j["windowTitle"].get<std::string>();
			if (j.contains("bulletsConfigPath") && j["bulletsConfigPath"].is_string()) bulletsConfigPath = j["bulletsConfigPath"].get<std::string>();
			if (j.contains("enemyConfigPath") && j["enemyConfigPath"].is_string()) enemyConfigPath = j["enemyConfigPath"].get<std::string>();

			if (j.contains("playerModelName") && j["playerModelName"].is_string()) playerModelName = j["playerModelName"].get<std::string>();
			if (j.contains("enemyModelName") && j["enemyModelName"].is_string()) enemyModelName = j["enemyModelName"].get<std::string>();
			if (j.contains("skyDomeModelName") && j["skyDomeModelName"].is_string()) skyDomeModelName = j["skyDomeModelName"].get<std::string>();

			if (j.contains("playerMoveStep") && j["playerMoveStep"].is_number()) playerMoveStep = j["playerMoveStep"].get<float>();

			if (j.contains("enemy")) {
				auto je = j["enemy"];
				if (je.contains("hp")) enemyHp = je["hp"].get<int>();
				if (je.contains("fireInterval")) enemyFireInterval = je["fireInterval"].get<int>();
				if (je.contains("radius")) enemyRadius = je["radius"].get<float>();
				if (je.contains("angleStep")) enemyAngleStep = je["angleStep"].get<float>();
				if (je.contains("centerX")) enemyCenterX = je["centerX"].get<float>();
				if (je.contains("centerY")) enemyCenterY = je["centerY"].get<float>();
				if (je.contains("moveRadius")) enemyMoveRadius = je["moveRadius"].get<float>();
				if (je.contains("amplitude")) enemyAmplitude = je["amplitude"].get<float>();
				if (je.contains("frequency")) enemyFrequency = je["frequency"].get<float>();
				if (je.contains("a")) enemyA = je["a"].get<float>();
				if (je.contains("bulletSpeed")) enemyBulletSpeed = je["bulletSpeed"].get<float>();
			}
		}
		catch (...) {
			// パース失敗したら既定値を使用
		}
	}

	std::wstring WindowTitleW() {
		if (windowTitleUtf8.empty()) return L"";
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, windowTitleUtf8.c_str(), (int)windowTitleUtf8.size(), NULL, 0);
		if (size_needed <= 0) return L"";
		std::wstring w;
		w.resize(size_needed);
		MultiByteToWideChar(CP_UTF8, 0, windowTitleUtf8.c_str(), (int)windowTitleUtf8.size(), &w[0], size_needed);
		return w;
	}
}
