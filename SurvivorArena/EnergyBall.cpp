#include "EnergyBall.h"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

EnergyBall::EnergyBall(Player* player,sf::Vector2f position) : player_(player)
{
	if (!texture_.loadFromFile("src/sprites/energyBall.png")) {
		std::cerr << "Error loading player texture! \n";
	}
	spriteRectPostion_=sf::IntRect(0,0,64,128);
	sprite_ = sf::Sprite(texture_,spriteRectPostion_);
	position_ = position ;
	speed_ = 150.f;
	sprite_.setTexture(texture_);
	sprite_.setPosition(position);
	sprite_.rotate(0);
	sprite_.scale(sf::Vector2f(1.f,1.f));
	sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);

	sf::Vector2f targetPosition = player_->getPosition()  +sf::Vector2f(0,+20);
	direction_ = targetPosition - position_;
	float magnitude = std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y);
	if (magnitude != 0) {
		direction_ /= magnitude; 
	}
	float angle = std::atan2(direction_.y, direction_.x) * 180 / 3.14159f; // Convert radians to degrees
	sprite_.setRotation(angle);
}

EnergyBall::~EnergyBall()
{
}

void EnergyBall::update(float deltaTime)
{
	position_ += direction_ * speed_ * deltaTime;
	sprite_.setPosition(position_);
	lifeTime_-=deltaTime;
	
	if (clock_.getElapsedTime().asSeconds() > 0.1f)
	{
		if(spriteRectPostion_.left == 384-64)
		{
			spriteRectPostion_.left = 0;
			clock_.restart();
		}
		else
		{
			spriteRectPostion_.left += 64;
			clock_.restart();
		}
	}
	sprite_.setTextureRect(spriteRectPostion_);
	if(lifeTime_ <=0)
	{
		isDead_ = true;
	}
	Actor::update(deltaTime);
}

void EnergyBall::display(sf::RenderWindow& window)
{
	Actor::display(window);
}
