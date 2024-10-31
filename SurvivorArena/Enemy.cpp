#include "Enemy.h"

#include <SFML/Graphics/RenderWindow.hpp>

Enemy::Enemy()
= default;

Enemy::~Enemy()
= default;

bool Enemy::isDestroyed()
{
	return destroyed_;
}

void Enemy::display(sf::RenderWindow& window)
{
	Actor::display(window);
	hitBox_.setFillColor(sf::Color::Red);
	sf::FloatRect bounds = sprite_.getGlobalBounds();
	float centerX = bounds.left + bounds.width / 2;
	float centerY = bounds.top + bounds.height / 2;
	hitBox_.setPosition(centerX, centerY);
	window.draw(hitBox_);
	
}
