#include "Bullet.h"

#include <iostream>
#include <GL/glew.h>
#include <SFML/Window/Mouse.hpp>

#include "Player.h"

Bullet::Bullet(sf::Vector2f playerPos, sf::Vector2f position) : lifeTime_(5.0f)
{
	hitBox_ = sf::RectangleShape {sf::Vector2f(18,18)};
	if (!texture_.loadFromFile("src/sprites/blueBullet.png")) {
		std::cerr << "Error loading player texture! \n";
	}
	position_ = playerPos ;
	speed_ = 250.f;
	sprite_.setTexture(texture_);
	sprite_.setPosition(position_);
	sprite_.rotate(0);
	sprite_.scale(sf::Vector2f(0.3f,0.3f));
	sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);

	sf::Vector2f targetPosition = position;
	direction_ = targetPosition - playerPos;
	float magnitude = std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y);
	if (magnitude != 0) {
		direction_ /= magnitude; 
	}
	float angle = std::atan2(direction_.y, direction_.x) * 180 / 3.14159f; // Convert radians to degrees
	sprite_.setRotation(angle);

}

void Bullet::update(float deltaTime)
{
	position_ += direction_ * speed_ * deltaTime;
	sprite_.setPosition(position_);
	lifeTime_-=deltaTime;
	
	if(lifeTime_ <=0)
	{
		isDead_ = true;
	}
	sf::FloatRect bounds = sprite_.getGlobalBounds();
	float centerX = bounds.left + bounds.width / 2;
	float centerY = bounds.top + bounds.height / 2;
	hitBoxPosition_ = sf::Vector2f(centerX,centerY);
	hitBox_.setPosition(hitBoxPosition_);
	
	Actor::update(deltaTime);
}

void Bullet::display(sf::RenderWindow& window)
{
	Actor::display(window);
}

