#pragma once
#include "Actor.h"
#include "Player.h"

class Bullet : public Actor
{
	

public:
	Bullet(sf::Vector2f playerPos, sf::Vector2f position);
	void update(float deltaTime) override;
	void display(sf::RenderWindow& window) override;
	sf::RectangleShape getHitBox() const {return hitBox_;}

private:
	DmgType dmg  = Simple;
	float lifeTime_;
	sf::Vector2f direction_;
};
