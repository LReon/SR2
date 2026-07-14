#pragma once
#include "../State/Enemy/State.h"

class InfiniteMoveState : public IEnemyState {
public:

	void Update(Enemy& enemy) override { enemy.InfiniteMove(); }
};