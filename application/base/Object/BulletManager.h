#pragma once
#include "ObjectPool.h"
#include <list>

// 弾の生成・更新・描画・回収を共通化するユーティリティ
template<typename T>
class BulletManager {
public:
	explicit BulletManager(ObjectPool<T>& pool) : pool_(pool) {}

	// 弾を生成してリストに追加
	// Allocate だけ行い、初期化は呼び出し側で行う（柔軟性確保）
	T* AllocateOne() {
		T* b = pool_.Allocate();
		if (!b) return nullptr;
		active_.push_back(b);
		return b;
	}

	// 全弾を更新し、死んだ弾をプールへ返却
	void UpdateAll() {
		for (T* b : active_) b->Update();
		active_.remove_if([this](T* b) {
			if (b->IsDead()) {
				b->Reset();
				pool_.Release(b);
				return true;
			}
			return false;
		});
	}

	// 全弾を描画
	void DrawAll() {
		for (T* b : active_) b->Draw();
	}

	const std::list<T*>& GetActive() const { return active_; }

private:
	ObjectPool<T>& pool_;
	std::list<T*> active_;
};
