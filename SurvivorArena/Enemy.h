#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy() override;
	uint8_t get_hp() const {return hp_;}
	void update(float deltaTime) override;
	void set_hp(uint8_t hp) {hp_ = hp;}
	bool isDestroyed();
	void display(sf::RenderWindow& window) override;
	sf::RectangleShape getHitBox() const { return hitBox_;}

protected:
	uint8_t hp_;
	bool destroyed_;
	
};
