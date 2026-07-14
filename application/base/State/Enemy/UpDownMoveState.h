#pragma once
#include "State.h"
#include "InfiniteMoveState.h"

class UpDownMoveState : public IEnemyState {
public:
	void Update(Enemy& enemy) override {
		enemy.UpDownMove();

		// HP が 30 以下なら Infinite に遷移
		if (enemy.GetHp() <= 30) {
			enemy.SetState(std::make_unique<InfiniteMoveState>());
		}
	}
};
