#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class ClearScene {

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// 終了フラグ
	bool finished_ = false;
	// デスフラグのgetter
	bool IsFinished() const { return finished_; }
	// キーの入力
	Input* input_ = nullptr;
	


};