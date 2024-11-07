#include "Enemy.h"

#include <SFML/Graphics/RenderWindow.hpp>

Enemy::Enemy(): hp_(0), destroyed_(false)
{
	hitBox_ = sf::RectangleShape{sf::Vector2f(-36, 64)};
}

Enemy::~Enemy()
= default;

void Enemy::update(float deltaTime)
{
	Actor::update(deltaTime);
}

bool Enemy::isDestroyed()
{
	return destroyed_;
}

void Enemy::display(sf::RenderWindow& window)
{
	Actor::display(window);
}
