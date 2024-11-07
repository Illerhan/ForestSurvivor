#pragma once
#include "DropItem.h"
#include "Player.h"

class HealItem : public DropItem
{
public:
	void heal(Player* player);
private:
	float healAmount_ = 15.f;
};
