#include "ConfigLoader.h"
#include <fstream>
#include <sstream>
#include <cctype>

std::string ConfigLoader::ReadFile(const std::string& path) {
	std::ifstream ifs(path);
	if (!ifs) return {};
	std::ostringstream ss;
	ss << ifs.rdbuf();
	return ss.str();
}

bool GetStringField(const std::string& data, const std::string& key, std::string& out) {
	std::string token = '"' + key + '"';
	auto pos = data.find(token);
	if (pos == std::string::npos) return false;
	pos = data.find(':', pos);
	if (pos == std::string::npos) return false;
	pos++;
	while (pos < data.size() && std::isspace((unsigned char)data[pos])) pos++;
	if (pos >= data.size() || data[pos] != '"') return false;
	pos++;
	size_t end = data.find('"', pos);
	if (end == std::string::npos) return false;
	out = data.substr(pos, end - pos);
	return true;
}

bool GetNumberField(const std::string& data, const std::string& key, float& out) {
	std::string token = '"' + key + '"';
	auto pos = data.find(token);
	if (pos == std::string::npos) return false;
	pos = data.find(':', pos);
	if (pos == std::string::npos) return false;
	pos++;
	while (pos < data.size() && std::isspace((unsigned char)data[pos])) pos++;
	size_t end = pos;
	while (end < data.size() && (std::isdigit((unsigned char)data[end]) || data[end]=='.' || data[end]=='-' || data[end]=='+')) end++;
	if (end == pos) return false;
	try { out = std::stof(data.substr(pos, end - pos)); } catch(...) { return false; }
	return true;
}

bool ConfigLoader::LoadEnemyConfig(const std::string& path, EnemyConfig& out) {
	std::string raw = ReadFile(path);
	if (raw.empty()) return false;
	std::string s;
	if (GetStringField(raw, "model", s)) out.model = s;
	float fv;
	if (GetNumberField(raw, "hp", fv)) out.hp = static_cast<int>(fv);
	if (GetNumberField(raw, "fireInterval", fv)) out.fireInterval = static_cast<int>(fv);
	if (GetNumberField(raw, "radius", fv)) out.radius = fv;
	if (GetStringField(raw, "movementKind", s)) out.movementKind = s;
	if (GetNumberField(raw, "centerX", fv)) out.centerX = fv;
	if (GetNumberField(raw, "centerY", fv)) out.centerY = fv;
	if (GetNumberField(raw, "moveRadius", fv)) out.moveRadius = fv;
	if (GetNumberField(raw, "angleStep", fv)) out.angleStep = fv;
	if (GetNumberField(raw, "amplitude", fv)) out.amplitude = fv;
	if (GetNumberField(raw, "frequency", fv)) out.frequency = fv;
	if (GetNumberField(raw, "a", fv)) out.a = fv;
	if (GetStringField(raw, "bulletType", s)) out.bulletType = s;
	return true;
}

bool ConfigLoader::LoadBulletsConfig(const std::string& path, std::unordered_map<std::string, BulletConfig>& out) {
	std::string raw = ReadFile(path);
	if (raw.empty()) return false;
	size_t pos = 0;
	while (true) {
		size_t nameStart = raw.find('"', pos);
		if (nameStart == std::string::npos) break;
		size_t nameEnd = raw.find('"', nameStart + 1);
		if (nameEnd == std::string::npos) break;
		std::string name = raw.substr(nameStart + 1, nameEnd - nameStart - 1);
		size_t brace = raw.find('{', nameEnd);
		if (brace == std::string::npos) break;
		int depth = 1;
		size_t i = brace + 1;
		for (; i < raw.size(); ++i) {
			if (raw[i] == '{') depth++;
			else if (raw[i] == '}') { depth--; if (depth == 0) break; }
		}
		if (i >= raw.size()) break;
		std::string body = raw.substr(brace + 1, i - (brace + 1));
		BulletConfig bc;
		std::string s;
		float fv;
		if (GetStringField(body, "model", s)) bc.model = s;
		if (GetNumberField(body, "speed", fv)) bc.speed = fv;
		if (GetNumberField(body, "life", fv)) bc.life = static_cast<int>(fv);
		if (GetNumberField(body, "radius", fv)) bc.radius = fv;
		out[name] = bc;
		pos = i + 1;
	}
	return true;
}
