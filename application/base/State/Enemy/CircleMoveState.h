#pragma once

#include "..//State/Enemy/State.h"
#include "../State/Enemy/UpDownMoveState.h"


class CircleMoveState : public IEnemyState {
public:
	void Enter(Enemy& /* enemy*/) override {}
	void Update(Enemy& enemy) override {
		enemy.CircleMove();

		// HP が 70〜40 の間なら UpDown に遷移
		int hp = enemy.GetHp();
		if (hp <= 70 && hp >= 40) {
			enemy.SetState(std::make_unique<UpDownMoveState>());
		}
	}
	void Exit(Enemy& /* enemy*/) override {}
};