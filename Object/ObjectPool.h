#pragma once
#include <vector>

// シンプルな固定サイズオブジェクトプール
template<typename T>
class ObjectPool {
public:
	explicit ObjectPool(size_t capacity = 128) : capacity_(capacity) {
		pool_.reserve(capacity_);
		active_.reserve(capacity_);
		for (size_t i = 0; i < capacity_; ++i) {
			pool_.push_back(new T());
			active_.push_back(false);
		}
	}

	~ObjectPool() {
		for (T* p : pool_) delete p;
	}

	// 利用可能なオブジェクトのポインタを返す。空きがなければ nullptr を返す。
	T* Allocate() {
		for (size_t i = 0; i < capacity_; ++i) {
			if (!active_[i]) {
				active_[i] = true;
				return pool_[i];
			}
		}
		return nullptr;
	}

	// プールに返却する。受け取ったポインタはプール内のものと一致する必要がある。
	void Release(T* obj) {
		if (!obj) return;
		for (size_t i = 0; i < capacity_; ++i) {
			if (pool_[i] == obj) {
				active_[i] = false;
				return;
			}
		}
	}

	// アクティブなオブジェクトのみ列挙するためのユーティリティ
	template<typename Func>
	void ForEachActive(Func f) {
		for (size_t i = 0; i < capacity_; ++i) {
			if (active_[i]) f(pool_[i]);
		}
	}

private:
	size_t capacity_;
	std::vector<T*> pool_;
	std::vector<bool> active_;
};
