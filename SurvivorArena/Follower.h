#pragma once
#include "Enemy.h"
#include "Player.h"

class Follower final : public Enemy
{
public:
	Follower(Player* player, sf::Vector2f position);
	~Follower() override;
	void update(float deltaTime) override;
	void display(sf::RenderWindow& window) override;
private:
	Player* player_;
};
