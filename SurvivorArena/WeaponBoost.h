#pragma once
#include "DropItem.h"

class WeaponBoost : public DropItem
{
public:
	
	WeaponBoost(sf::Vector2f position);
	void update(float deltaTime);
	void display(sf::RenderWindow& window);
	sf::RectangleShape getHitBox() const { return hitbox_;}

private:
	DmgType type_;
	sf::Sprite newSprite_;
	sf::Sprite boostSprite_;
	float newSpeed_;
	float newDmg;
	float lifetime_ = 20.f;
	sf::RectangleShape hitbox_;
};
