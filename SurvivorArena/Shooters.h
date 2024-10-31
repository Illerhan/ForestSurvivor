#pragma once
#include "Enemy.h"
#include "Player.h"

class Shooters : public Enemy
{
	~Shooters() override;

public:
	Shooters(Player* player,sf::Vector2f position);

	void shoot(sf::Vector2f position);
	void update(float deltaTime) override;
	void display(sf::RenderWindow& window) override;
	Player* player_;
	bool isFar;
};
