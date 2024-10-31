#pragma once
#include "Actor.h"
#include "Player.h"

class EnergyBall : public Actor
{
public:

	EnergyBall(Player* player,sf::Vector2f position);
	~EnergyBall();
	
	void update(float deltaTime);
	void display(sf::RenderWindow& window);

	Player* player_;
	sf::Vector2f direction_;
	float lifeTime_ = 2.f;
};
