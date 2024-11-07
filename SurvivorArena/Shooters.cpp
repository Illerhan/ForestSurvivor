#include "Shooters.h"

#include <iostream>

#include "EnergyBall.h"
#include "Game.h"

Shooters::~Shooters()
{
}

Shooters::Shooters(Player* player,sf::Vector2f position) : player_(player), isFar(true)
{
	if (!texture_.loadFromFile("src/sprites/Attack_2.png"))
	{
		std::cerr << "Error loading player texture! \n";
	}
	sprite_ = sf::Sprite(texture_, spriteRectPostion_);
	position_ = position;
	speed_ = 50.f;
	sprite_.setTexture(texture_);
	sprite_.setPosition(position);
	sprite_.rotate(0);
	sprite_.scale(sf::Vector2f(1.f, 1.f));
	sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
}

void Shooters::shoot(sf::Vector2f position)
{
	Game::addEnergyBall(new EnergyBall(player_,position));
}

void Shooters::update(float deltaTime)
{

	sf::Vector2f playerPos = player_->get_position();
	sf::Vector2f direction = playerPos - position_;
	sf::Vector2f pos = sprite_.getPosition()+ sf::Vector2f(10,20);
	
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (magnitude > 0) {
		direction /= magnitude; // Normalize
		direction *= speed_ * deltaTime;    // Scale by speed
	}
	if (magnitude <= 150)
	{
		position_ -= direction;
	}

	if (magnitude > 500)
	{
		position_ += direction;
	}
	
	if(direction.x < 0 )
	{
		hitBox_ = sf::RectangleShape{sf::Vector2f(36,64)};
		sprite_.setScale(-1.0,1.0);
	}
	
	if(direction.x >= 0 )
	{
		sprite_.setScale(1.0,1.0);
		hitBox_ = sf::RectangleShape{sf::Vector2f(-36,64)};
		pos = sprite_.getPosition()+ sf::Vector2f(-50,20);
	}
		
	if (clock_.getElapsedTime().asSeconds() > 0.1f && magnitude > 150)
	{
		if(spriteRectPostion_.left == 1152-128)
		{
			shoot(pos);
			spriteRectPostion_.left = 0;
			clock_.restart();
		}
		else
		{
			spriteRectPostion_.left += 128;
			clock_.restart();
		}
	}
	sprite_.setPosition(position_);
	sprite_.setTextureRect(spriteRectPostion_);
	Enemy::update(deltaTime);
}

void Shooters::display(sf::RenderWindow& window)
{
	
	Enemy::display(window);
}
