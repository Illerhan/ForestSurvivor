#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy() override;
	uint8_t get_hp() const {return hp_;}

	void set_hp(uint8_t hp) {hp_ = hp;}
	bool isDestroyed();
	void display(sf::RenderWindow& window) override;
	sf::FloatRect getHitBox() const { return hitBox_.getGlobalBounds();}

protected:
	uint8_t hp_;
	bool destroyed_;
	
	sf::RectangleShape hitBox_{sf::Vector2f(-36,64)};
};
