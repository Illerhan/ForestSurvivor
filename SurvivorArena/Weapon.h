#pragma once
#include "Actor.h"

class Weapon : public Actor
{
	
public:
	Weapon(DmgType type);
	void update(float deltaTime) override;
	void display(sf::RenderWindow& window) override;
	void setPosition(sf::Vector2f position) {position_ = position;}

private:
	sf::RectangleShape border_;
	sf::Sprite weaponSprite_;
	DmgType type_;
	int8_t weaponLvl = 0;
};
