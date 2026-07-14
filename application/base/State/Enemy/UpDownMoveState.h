#pragma once
#include "../State/Enemy/State.h"
#include "../State/Enemy/InfiniteMoveState.h"

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
