#pragma once
#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy() override;
	uint8_t get_hp() const {return hp_;}

	void set_hp(uint8_t hp) {hp_ = hp;}
	bool isDestroyed();

protected:
	uint8_t hp_;
	bool destroyed_;
};
