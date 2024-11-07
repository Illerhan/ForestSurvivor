#include "Follower.h"

#include <iostream>
#include <detail/type_vec2.hpp>

Follower::Follower(Player* player, sf::Vector2f position): player_(player)
{
	if (!texture_.loadFromFile("src/sprites/mageRun.png")) {
		std::cerr << "Error loading player texture! \n";
	}
	sprite_ = sf::Sprite(texture_,spriteRectPostion_);
	position_ = position ;
	speed_ = 50.f;
	sprite_.setTexture(texture_);
	sprite_.setPosition(position);
	sprite_.rotate(0);
	sprite_.scale(sf::Vector2f(1.f,1.f));
	sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
}

Follower::~Follower()
{
}

void Follower::update(float deltaTime)
{
	sf::Vector2f playerPos = player_->get_position();
	sf::Vector2f direction = playerPos - position_;

	// Normalize the direction vector
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (magnitude > 0) {
		direction /= magnitude; // Normalize
		direction *= speed_ * deltaTime;    // Scale by speed
	}
	if(direction.x < 0 )
	{
		sprite_.setScale(-1.0,1.0);
		hitBox_ = sf::RectangleShape{sf::Vector2f(36,64)};
	}
	if(direction.x >= 0 )
	{
		sprite_.setScale(1.0,1.0);
		hitBox_ = sf::RectangleShape{sf::Vector2f(-36,64)};
	}
	position_ += direction; // Update position towards player
	if (clock_.getElapsedTime().asSeconds() > 0.1f)
	{
		if(spriteRectPostion_.left == 1024-128)
		{
			spriteRectPostion_.left = 0;
			clock_.restart();
		}
		else
		{
			spriteRectPostion_.left += 128;
			clock_.restart();
		}
	}
	sprite_.setTextureRect(spriteRectPostion_);
	sprite_.setPosition(position_);
	Enemy::update(deltaTime);
}

void Follower::display(sf::RenderWindow& window)
{
	Enemy::display(window);
}
