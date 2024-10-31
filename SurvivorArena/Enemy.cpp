#include "Enemy.h"

Enemy::Enemy()
= default;

Enemy::~Enemy()
= default;

bool Enemy::isDestroyed()
{
	return destroyed_;
}
