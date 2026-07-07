#pragma once
#include <string>
#include <unordered_map>

struct BulletConfig {
	std::string model;
	float speed = 0.0f;
	int life = 0;
	float radius = 0.0f;
};

struct EnemyConfig {
	std::string model = "enemy";
	int hp = 100;
	int fireInterval = 30;
	float radius = 2.0f;
	std::string movementKind = "circle";
	float centerX = 20.0f;
	float centerY = 0.0f;
	float moveRadius = 10.0f;
	float angleStep = 0.05f;
	float amplitude = 10.0f;
	float frequency = 0.5f;
	float a = 10.0f;
	std::string bulletType = "enemy_small";
};

class ConfigLoader {
public:
	static std::string ReadFile(const std::string& path);
	static bool LoadEnemyConfig(const std::string& path, EnemyConfig& out);
	static bool LoadBulletsConfig(const std::string& path, std::unordered_map<std::string, BulletConfig>& out);
};
